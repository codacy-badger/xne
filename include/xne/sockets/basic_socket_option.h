/**
 * @file    basic_socket_option.h
 * @author  isnullxbh
 * @date    2019-02-13 10:59
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_BASIC_SOCKET_OPTION_H
#define XNE_SOCKETS_BASIC_SOCKET_OPTION_H

#include <system_error>

namespace xne {
namespace net {

class socket_base;

/**
 * @class   basic_socket_option basic_socket_option.h "include/xne/sockets/basic_socket_option.h"
 * @brief   A class that forms a base for any class that represent
 *          a socket option.
 */

class basic_socket_option {
public:
    virtual ~basic_socket_option() = default;

public:
    virtual bool set(socket_base& socket, std::error_code& ec) = 0;
    virtual bool get(socket_base& socket, std::error_code& ec) = 0;
};

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_SOCKET_OPTION_H
