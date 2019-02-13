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

namespace xne {
namespace net {

/**
 * @class   basic_connector basic_connector.h "include/xne/sockets/basic_connector.h"
 * @tparam  Protocol    Specifies a particular network protocol to be used
 *                      with socket.
 * @brief   A class that forms a base for any class designed to make network
 *          connections. Requires to implement method "connect" according to
 *          type of the endpoint that defines by selected protocol.
 */

template<typename Protocol>
class basic_connector {
public:
    using protocol_type = Protocol;
    using socket_type = typename protocol_type::socket_type;
    using endpoint_type = typename protocol_type::endpoint_type;

public:
    basic_connector(const protocol_type& protocol, socket_type&& socket);
    virtual ~basic_connector() = default;

    basic_connector(const basic_connector&) = delete;
    basic_connector(basic_connector&&) = delete;
    basic_connector& operator=(const basic_connector&) = delete;
    basic_connector& operator=(basic_connector&&) = delete;

public:
    virtual bool connect(const endpoint_type& endpoint, std::error_code& ec) = 0;
    socket_type& socket();

protected:
    protocol_type protocol_;
    socket_type   socket_;
};

template<typename Protocol>
inline basic_connector<Protocol>::basic_connector(const protocol_type& protocol, socket_type&& socket)
    : protocol_(protocol)
    , socket_(std::move(socket))
{}

template<typename Protocol>
inline typename basic_connector<Protocol>::socket_type& basic_connector<Protocol>::socket() {
    return socket_;
}

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_CONNECTOR_H
