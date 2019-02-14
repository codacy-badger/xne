/**
 * @file    tcp_acceptor.h
 * @author  isnullxbh
 * @date    2019-02-13 15:38
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_TCP_ACCEPTOR_H
#define XNE_DOMAINS_INET_TCP_ACCEPTOR_H

#include "xne/sockets/basic_acceptor.h"
#include "xne/domains/inet/tcp.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   tcp_acceptor tcp_acceptor.h "include/xne/domains/inet/tcp_acceptor.h"
 */

class tcp_acceptor : public basic_acceptor<tcp> {
public:
    tcp_acceptor(const protocol_type& protocol, socket_type&& socket);

public:
    bool bind(const endpoint_type& endpoint, std::error_code& ec) override;
    handle_type accept(endpoint_type& endpoint, std::error_code& ec) override;
    bool listen(int backlog, std::error_code& ec) override;
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_TCP_ACCEPTOR_H
