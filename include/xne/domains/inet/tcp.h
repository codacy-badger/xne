/**
 * @file    tcp.h
 * @author  isnullxbh
 * @date    2019-02-08 13:03
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_TCP_H
#define XNE_DOMAINS_INET_TCP_H

#include "xne/core/basic_protocol.h"
#include "xne/sockets/basic_stream_socket.h"
#include "xne/domains/inet/protocol_version.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   tcp tcp.h "include/xne/domains/inet/tcp.h"
 * @brief   This class provides details of TCP protocol in scope of
 *          Internet network domain.
 */

class tcp : public basic_protocol {
public:
    using socket_type = basic_stream_socket<tcp>;

public:
    explicit tcp(protocol_version version = protocol_version::v4);

public:
    // interface: basic_protocol
    int family() const noexcept override;
    int type() const noexcept override;
    int protocol() const noexcept override;

    protocol_version version() const noexcept;

protected:
    protocol_version version_;
};

inline tcp::tcp(protocol_version version)
    : version_(version)
{}

inline protocol_version tcp::version() const noexcept {
    return version_;
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_TCP_H
