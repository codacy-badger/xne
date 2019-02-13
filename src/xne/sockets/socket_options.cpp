/**
 * @file    socket_options.cpp
 * @author  isnullxbh
 * @date    2019-02-13 11:39
 * @version 0.0.1
 */

#include "xne/sockets/socket_options.h"
#include "xne/sockets/socket_base.h"

#include <sys/socket.h>

namespace xne {
namespace net {

so_nosigpipe::so_nosigpipe(bool enable)
    : enable_(enable)
{}

bool so_nosigpipe::set(socket_base& socket, std::error_code& ec) {
    int opt_val = (enable_) ? 1 : 0;
    if (::setsockopt(socket.native_handle(), SOL_SOCKET, SO_NOSIGPIPE, &opt_val, sizeof(opt_val))) {
        ec.assign(errno, std::system_category());
        return false;
    }
    return true;
}

bool so_nosigpipe::get(socket_base& socket, std::error_code& ec) {
    int opt_val = 0;
    socklen_t opt_len = 0;
    if (::getsockopt(socket.native_handle(), SOL_SOCKET, SO_NOSIGPIPE, &opt_val, &opt_len)) {
        ec.assign(errno, std::system_category());
        return false;
    }
    return true;
}

} // namespace net
} // namespace xne
