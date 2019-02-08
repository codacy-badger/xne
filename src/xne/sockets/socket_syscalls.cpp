/**
 * @file    socket_syscalls.cpp
 * @author  isnullxbh
 * @date    2019-01-16 12:05
 * @version 0.0.1
 */

#include "xne/sockets/socket_syscalls.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace xne {
namespace net {
namespace syscall {

socket_base::handle_type socket(const basic_protocol& protocol, std::error_code* ec) {
    auto handle = ::socket(protocol.family(), protocol.type(), protocol.protocol());
    if (handle < 0 && ec )
        ec->assign(errno, std::system_category());
    return handle;
}

void close(socket_base::handle_type& handle, std::error_code* ec) {
    auto err = ::close(handle);
    if (!err)
        handle = socket_base::invalid_handle;
    else if (ec) {
        ec->assign(errno, std::system_category());
    }
}

size_t send(socket_base::handle_type handle, const char* data, size_t size, std::error_code& ec, socket_base::cflags flags) {
    ssize_t bytes_sent = 0;
    if ((bytes_sent = ::send(handle, data ,size, static_cast<int>(flags))) < 0) {
        ec.assign(errno, std::system_category());
        return 0;
    }
    return static_cast<size_t>(bytes_sent);
}

size_t receive(socket_base::handle_type handle, char* data, size_t size, std::error_code& ec, socket_base::cflags flags) {
    ssize_t bytes_recv = 0;
    if ((bytes_recv = ::recv(handle, data, size, static_cast<int>(flags))) < 0) {
        ec.assign(errno, std::system_category());
        return 0;
    }
    return static_cast<size_t>(bytes_recv);
}

bool bind(socket_base::handle_type handle, std::error_code& ec) {
    sockaddr_in sa {};
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(8891);
    sa.sin_family = AF_INET;

    if (::bind(handle, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) < 0) {
        ec.assign(errno, std::system_category());
        return false;
    }

    return true;
}

socket_base::handle_type accept(socket_base::handle_type handle, std::error_code& ec) {
    const auto client_handle = ::accept(handle, nullptr, nullptr);
    if (handle < 0) {
        ec.assign(errno, std::system_category());
    }
    return client_handle;
}

bool listen(socket_base::handle_type handle, size_t maxconns, std::error_code& ec) {
    if (::listen(handle, (int)maxconns) < 0) {
        ec.assign(errno, std::system_category());
        return false;
    }
    return true;
}

} // namespace syscall
} // namespace net
} // namespace xne