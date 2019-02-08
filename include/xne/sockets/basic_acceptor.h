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
    using socket_type = typename Protocol::socket_type;

public:
    basic_acceptor(const protocol_type& proto, socket_type* socket);
    virtual ~basic_acceptor() = default;

public:
    bool bind(std::error_code& ec);
    socket_base::handle_type accept(std::error_code& ec);
    bool listen(size_t maxconns, std::error_code& ec);

protected:
    protocol_type   proto_;
    socket_type*    socket_;
};

template<typename Protocol>
inline basic_acceptor<Protocol>::basic_acceptor(const protocol_type& proto, socket_type* socket)
    : proto_(proto)
    , socket_(socket)
{}

template<typename Protocol>
inline bool basic_acceptor<Protocol>::bind(std::error_code& ec) {
    return syscall::bind(socket_->native_handle(), ec);
}

template<typename Protocol>
inline bool basic_acceptor<Protocol>::listen(size_t maxconns, std::error_code& ec) {
    return syscall::listen(socket_->native_handle(), maxconns, ec);
}

template<typename Protocol>
inline socket_base::handle_type basic_acceptor<Protocol>::accept(std::error_code& ec) {
    return syscall::accept(socket_->native_handle(), ec);
}

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_ACCEPTOR_H
