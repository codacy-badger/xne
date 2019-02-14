/**
 * @file    server.cpp
 * @author  isnullxbh
 * @date    2019-02-14 13:46
 * @version 0.0.1
 */

#include <iostream>
#include <system_error>
#include <thread>
#include <chrono>

#include "xne/domains/inet/tcp_acceptor.h"

namespace net = xne::net;
using namespace std::chrono_literals;

using tcp = net::inet::tcp;

constexpr int max_conns = 10;

class client_socket : public net::basic_stream_socket<tcp> {
public:
    explicit client_socket(net::socket_base::handle_type handle)
        : net::basic_stream_socket<tcp>(handle)
    {}
};

class buffer_view : public xne::net::basic_buffer_view {
public:
    buffer_view(char* buf, size_t size)
        : basic_buffer_view(buf, size)
    {}

public:
    void resize(size_t) override {}
};

using endpoint_t = net::inet::basic_endpoint<tcp>;

int main() {
    std::error_code ec;
    const auto host_endpoint = endpoint_t::make_endpoint("192.168.0.102", 8182);
    const auto protocol = tcp();

    tcp::socket_type srv_socket;
    srv_socket.open(protocol, ec);
    srv_socket.autoclose = true;

    if (ec) {
        std::clog << "[err] " << ec.message() << std::endl;
        return ec.value();
    }

    net::inet::tcp_acceptor acceptor { protocol, std::move(srv_socket) };
    acceptor.bind(host_endpoint, ec);
    acceptor.listen(max_conns, ec);

    if (ec) {
        std::clog << "[err] " << ec.message() << std::endl;
        return ec.value();
    }

    char buf[256] {0};
    buffer_view buf_view { buf, 256 };

    while (true) {
        endpoint_t peer_endpoint;
        const auto peer_handle = acceptor.accept(peer_endpoint, ec);
        if (peer_handle > 0) {
            std::cout << "peer: ip=" << peer_endpoint.ip_address().as_string() << ", port=" << peer_endpoint.port() << std::endl;
            client_socket socket { peer_handle };
            if (auto bytes_read = socket.receive(buf_view, ec)) {
                auto bytes_sent = socket.send(buf_view, ec);
                std::clog << "bytes read: " << bytes_read << ", bytes sent: " << bytes_sent << std::endl;
                socket.close(ec);
            }
        }
        std::this_thread::sleep_for(1s);
        if (ec) {
            break;
        }
    }
}