/**
 * @file    test.cpp
 * @author  isnullxbh
 * @date    2019-01-16 12:37
 * @version 0.0.1
 */

#include <system_error>
#include <iostream>
#include <functional>

#include "xne/protocols/local/tcp.h"
#include "xne/sockets/basic_socket.h"

#include "test.h"

namespace net = xne::net;

template<typename Protocol>
class socket_with_hooks : public net::basic_socket<Protocol> {
public:
    using base_class = net::basic_socket<Protocol>;
    using typename base_class::handle_type;
    using close_hook = std::function<void(handle_type)>;

public:
    socket_with_hooks()
        : net::basic_socket<Protocol>()
        , on_close(nullptr)
    {
        // there isn't closing in a base class - this was delegated
        // to the derived class
        this->releaser_ = [self = this](net::basic_socket<Protocol>*) {
            self->try_autoclose();
            self->on_close(self->native_handle());
        };
    }

public:
    close_hook on_close;
};

bool case_basic_socket_operations();
bool case_autoclose_property();

int main() {
    xne::testing::test test;
    test.add_case({ "basic socket operations", case_basic_socket_operations });
    test.add_case({ "autoclose property", case_autoclose_property });
    test.perform();

    return test.passed();
}

bool case_basic_socket_operations() {
    const auto protocol = net::local::tcp();
    using socket_type = net::basic_socket<decltype(protocol)>;
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

bool case_autoclose_property() {
    const auto protocol = net::local::tcp();
    using socket_type = socket_with_hooks<decltype(protocol)>;
    std::error_code ec;
    bool success = false;
    {
        socket_type socket;
        socket.autoclose = true;
        socket.on_close = [&success](socket_type::handle_type handle) {
            if (socket_type::invalid_handle == handle)
                success = true;
        };
        socket.open(protocol, ec);
        if (ec) {
            std::cerr << ec.message() << std::endl;
            return false;
        }
    }
    return success;
}
