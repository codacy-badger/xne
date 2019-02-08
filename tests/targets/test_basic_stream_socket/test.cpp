/**
 * @file    test.cpp
 * @author  isnullxbh
 * @date    2019-02-08 14:08
 * @version 0.0.1
 */

#include <iostream>

#include "xne/domains/inet/tcp.h"

#include "test.h"

namespace net = xne::net;

bool case_basic_stream_socket_operations();

int main() {
    xne::testing::test test;
    test.add_case({ "basic stream socket operations", case_basic_stream_socket_operations });
    test.perform();

    return test.passed();
}

bool case_basic_stream_socket_operations() {
    const auto protocol = net::inet::tcp(true);
    using socket_type = decltype(protocol)::socket_type;
    std::error_code ec;
    socket_type socket;
    socket.open(protocol, ec);
    if (ec) {
        std::cerr << ec.message() << std::endl;
        return false;
    }
    socket.close(ec);
    if (ec) {
        std::cerr << ec.message() << std::endl;
        return false;
    }
    return socket.native_handle() == socket_type::invalid_handle;
}
