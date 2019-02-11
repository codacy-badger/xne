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

using socket_flags_t = socket_base::flags_type;

socket_base::handle_type    socket(const basic_protocol& protocol, std::error_code* ec);
void                        close(socket_base::handle_type& handle, std::error_code* ec);
size_t                      send(socket_base::handle_type handle, const char* data, size_t size, std::error_code& ec, socket_flags_t flags = 0);
size_t                      receive(socket_base::handle_type handle, char* data, size_t size, std::error_code& ec, socket_flags_t flags = 0);
bool                        bind(socket_base::handle_type handle, std::error_code& ec);
socket_base::handle_type    accept(socket_base::handle_type handle, std::error_code& ec);
bool                        listen(socket_base::handle_type handle, size_t, std::error_code& ec);

} // namespace syscall
} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_SOCKET_SYSCALLS_H
