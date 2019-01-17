/**
 * @file    socket_syscalls.cpp
 * @author  isnullxbh
 * @date    2019-01-16 12:05
 * @version 0.0.1
 */

#include "xne/sockets/socket_syscalls.h"

#include <sys/types.h>
#include <sys/socket.h>
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

} // namespace syscall
} // namespace net
} // namespace xne