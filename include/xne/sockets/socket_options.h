/**
 * @file    socket_options.h
 * @author  isnullxbh
 * @date    2019-02-13 11:28
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_SOCKET_OPTIONS_H
#define XNE_SOCKETS_SOCKET_OPTIONS_H

#include "xne/sockets/basic_socket_option.h"

namespace xne {
namespace net {

class so_nosigpipe : public basic_socket_option {
public:
    explicit so_nosigpipe(bool enable);

public:
    bool set(socket_base& socket, std::error_code& ec) override;
    bool get(socket_base& socket, std::error_code& ec) override;

protected:
    bool enable_;
};

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_SOCKET_OPTIONS_H
