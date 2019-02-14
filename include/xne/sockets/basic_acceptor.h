/**
 * @file    basic_acceptor.h
 * @author  isnullxbh
 * @date    2019-02-08 18:01
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_BASIC_ACCEPTOR_H
#define XNE_SOCKETS_BASIC_ACCEPTOR_H

#include <system_error>

#include "xne/sockets/socket_syscalls.h"

namespace xne {
namespace net {

template<typename Protocol>
class basic_acceptor {
public:
    using protocol_type = Protocol;
    using socket_type = typename protocol_type::socket_type;
    using endpoint_type = typename protocol_type::endpoint_type;
    using handle_type = socket_base::handle_type;

public:
    basic_acceptor(const protocol_type& proto, socket_type&& socket);
    virtual ~basic_acceptor() = default;

    basic_acceptor(const basic_acceptor&) = delete;
    basic_acceptor(basic_acceptor&&) = delete;
    basic_acceptor& operator=(const basic_acceptor&) = delete;
    basic_acceptor& operator=(basic_acceptor&&) = delete;

public:
    virtual bool bind(const endpoint_type& endpoint, std::error_code& ec) = 0;
    virtual handle_type accept(endpoint_type& remote_endpoint, std::error_code& ec) = 0;
    virtual bool listen(int backlog, std::error_code& ec) = 0;

protected:
    protocol_type   proto_;
    socket_type     socket_;
};

template<typename Protocol>
inline basic_acceptor<Protocol>::basic_acceptor(const protocol_type& proto, socket_type&& socket)
    : proto_(proto)
    , socket_(std::move(socket))
{}

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_ACCEPTOR_H
