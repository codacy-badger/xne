/**
 * @file    tcp_connector.h
 * @author  isnullxbh
 * @date    2019-02-13 01:29
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_TCP_CONNECTOR_H
#define XNE_DOMAINS_INET_TCP_CONNECTOR_H

#include "xne/sockets/basic_connector.h"
#include "xne/domains/inet/tcp.h"

namespace  xne {
namespace  net {
namespace inet {

class tcp_connector : public basic_connector<tcp> {
public:
    tcp_connector(const protocol_type& protocol, socket_type&& socket);

public:
    bool connect(const endpoint_type& endpoint, std::error_code& ec) override;
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_TCP_CONNECTOR_H
