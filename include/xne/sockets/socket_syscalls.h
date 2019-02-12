/**
 * @file    socket_syscalls.h
 * @author  isnullxbh
 * @date    2019-01-16 12:02
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_SOCKET_SYSCALLS_H
#define XNE_SOCKETS_SOCKET_SYSCALLS_H

#include <system_error>
#include <iostream>

#include "xne/core/basic_protocol.h"
#include "xne/sockets/socket_base.h"

namespace xne {
namespace net {
namespace syscall {

using flags_t = socket_base::flags_type;
using handle_t = socket_base::handle_type;

socket_base::handle_type    socket(const basic_protocol& protocol, std::error_code* ec);
void                        close(handle_t& handle, std::error_code* ec);
size_t                      send(handle_t handle, const char* data, size_t size, std::error_code& ec, flags_t flags = 0);
size_t                      receive(handle_t handle, char* data, size_t size, std::error_code& ec, flags_t flags = 0);
bool                        bind(handle_t handle, std::error_code& ec);
socket_base::handle_type    accept(handle_t handle, std::error_code& ec);
bool                        listen(handle_t handle, size_t, std::error_code& ec);
bool                        connect(handle_t handle, std::error_code& ec);

} // namespace syscall
} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_SOCKET_SYSCALLS_H
