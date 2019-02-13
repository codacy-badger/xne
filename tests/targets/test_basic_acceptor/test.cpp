/**
 * @file    test.cpp
 * @author  isnullxbh
 * @date    2019-02-08 18:37
 * @version 0.0.1
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <csignal>

#include "xne/sockets/basic_acceptor.h"
#include "xne/sockets/socket_options.h"
#include "xne/domains/inet/tcp.h"
#include "xne/io/basic_buffer_view.h"
#include "xne/domains/inet/tcp_connector.h"

#include "test.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace net = xne::net;
using namespace std::chrono_literals;

bool case_basic_acceptor_operations();

template<typename Protocol = net::inet::tcp>
class client_socket : public net::basic_stream_socket<Protocol> {
public:
    explicit client_socket(net::socket_base::handle_type handle)
        : net::basic_stream_socket<Protocol>(handle)
    {}
};

class buffer_view : public net::basic_buffer_view {
public:
    explicit buffer_view(char* str, size_t size)
        : net::basic_buffer_view(str, size)
    {}

public:
    void resize(size_t) override {}
};

int main() {
    xne::testing::test test;
    test.add_case({ "basic acceptor operations", case_basic_acceptor_operations });
    test.perform();

    return test.passed();
}

bool case_basic_acceptor_operations() {

    std::signal(SIGPIPE, SIG_IGN);

    char data[] = "You in Matrix...";
    buffer_view view { data, std::strlen(data) };
    const auto protocol = net::inet::tcp();
    using socket_t = decltype(protocol)::socket_type;
    socket_t socket {};
    std::error_code ec;
    socket.open(protocol, ec);
    if (ec) {
        std::cerr << "[err] " << ec.message() << std::endl;
        ec.clear();
    }
    auto acceptor = net::basic_acceptor(protocol, &socket);
    acceptor.bind(ec);
    if (ec) {
        std::cerr << "[err] " << ec.message() << std::endl;
        ec.clear();
    }
    acceptor.listen(100, ec);
    if (ec) {
        std::cerr << "[err] " << ec.message() << std::endl;
        ec.clear();
    }

    std::thread sender_thread { [&protocol, &view](){
        using connector_t = net::inet::tcp_connector;
        using address_t = net::inet::address<net::inet::tcp>;
        using endpoint_t = net::inet::tcp::endpoint_type;
        std::error_code cli_err;
        socket_t cli_socket;

        cli_socket.open(protocol, cli_err);
        if (cli_err) {
            std::cerr << "[err] " << cli_err.message() << std::endl;
            cli_err.clear();
        }

        net::so_nosigpipe so_opt { true };
        cli_socket.set_option(so_opt, cli_err);
        if (cli_err) {
            std::cerr << "[err] " << cli_err.message() << std::endl;
            cli_err.clear();
        }

        address_t srv_address = address_t::make_address(protocol, "127.0.0.1");

        connector_t connector { protocol, std::move(cli_socket) };
        endpoint_t ep { srv_address, 8891 };
        connector.connect(ep, cli_err);
        if (cli_err) {
            std::cerr << "[err] " << cli_err.message() << std::endl;
            cli_err.clear();
        }
        connector.socket().send(view, cli_err);
        std::this_thread::sleep_for(5s);
        char buf[256];
        buffer_view rcv_buf { buf, 256 };
        connector.socket().receive(rcv_buf, cli_err);
        std::cout << "[client] recv_data: " << (char*)rcv_buf.data() << std::endl;
    }};

    while (true) {
        const auto client_handle = acceptor.accept(ec);
        if (client_handle > 0) {
            client_socket cli_socket { client_handle };
            cli_socket.send(view, ec, 0);
            cli_socket.close();
            break;
        }
        std::cout << "sleep for 3 seconds..." << std::endl;
        std::this_thread::sleep_for(3s);
    }

    if (sender_thread.joinable())
        sender_thread.join();

    socket.close();
    return true;
}
