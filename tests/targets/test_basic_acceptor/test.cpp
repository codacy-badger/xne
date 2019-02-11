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

#include "xne/sockets/basic_acceptor.h"
#include "xne/sockets/basic_connector.h"
#include "xne/domains/inet/tcp.h"
#include "xne/io/basic_buffer_view.h"

#include "test.h"

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
    char data[] = "You in Matrix...";
    buffer_view view { data, std::strlen(data) };
    const auto protocol = net::inet::tcp();
    using socket_t = decltype(protocol)::socket_type;
    socket_t socket {};
    std::error_code ec;
    socket.open(protocol, ec);
    auto acceptor = net::basic_acceptor(protocol, &socket);
    acceptor.bind(ec);
    acceptor.listen(100, ec);

    std::thread sender_thread { [&protocol, &view](){
        using connector_t = net::basic_connector<decltype(protocol)>;
        std::error_code cli_err;
        socket_t cli_socket;
        cli_socket.open(protocol, cli_err);
        connector_t connector { protocol, std::move(cli_socket) };
        connector.connect(cli_err);
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
            cli_socket.send(view, ec);
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
