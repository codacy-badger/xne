/**
 * @file    basic_connector.h
 * @author  isnullxbh
 * @date    2019-02-12 00:19
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_BASIC_CONNECTOR_H
#define XNE_SOCKETS_BASIC_CONNECTOR_H

#include <utility>
#include <system_error>

#include "xne/sockets/socket_syscalls.h"

namespace xne {
namespace net {

template<typename Protocol>
class basic_connector {
public:
    using protocol_type = Protocol;
    using socket_type = typename Protocol::socket_type;

public:
    basic_connector(const protocol_type& protocol, socket_type&& socket);
    virtual ~basic_connector() = default;

    basic_connector(const basic_connector&) = delete;
    basic_connector(basic_connector&&) = delete;
    basic_connector& operator=(const basic_connector&) = delete;
    basic_connector& operator=(basic_connector&&) = delete;

public:
    bool connect(std::error_code& ec);
    socket_type& socket();

protected:
    protocol_type   protocol_;
    socket_type     socket_;
};

template<typename Protocol>
inline basic_connector<Protocol>::basic_connector(const protocol_type& protocol, socket_type&& socket)
    : protocol_(protocol)
    , socket_(std::move(socket))
{}

template<typename Protocol>
inline bool basic_connector<Protocol>::connect(std::error_code& ec) {
    return syscall::connect(socket_.native_handle(), ec);
}

template<typename Protocol>
inline typename basic_connector<Protocol>::socket_type& basic_connector<Protocol>::socket() {
    return socket_;
}

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_CONNECTOR_H
