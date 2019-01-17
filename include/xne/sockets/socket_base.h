/**
 * @file    socket_base.h
 * @author  isnullxbh
 * @date    2019-01-16 07:08
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_SOCKET_BASE_H
#define XNE_SOCKETS_SOCKET_BASE_H

namespace xne {
namespace net {

class socket_base {
public:
    using handle_type = int;

protected:
    socket_base() = default;
    ~socket_base() = default;

public:
    static const handle_type invalid_handle;
};

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_SOCKET_BASE_H
