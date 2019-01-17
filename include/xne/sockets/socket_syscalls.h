/**
 * @file    socket_syscalls.h
 * @author  isnullxbh
 * @date    2019-01-16 12:02
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_SOCKET_SYSCALLS_H
#define XNE_SOCKETS_SOCKET_SYSCALLS_H

#include <system_error>

#include "xne/core/basic_protocol.h"
#include "xne/sockets/socket_base.h"

namespace xne {
namespace net {
namespace syscall {

socket_base::handle_type    socket(const basic_protocol& protocol, std::error_code* ec);
void                        close(socket_base::handle_type& handle, std::error_code* ec);

} // namespace syscall
} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_SOCKET_SYSCALLS_H
