/**
 * @file    tcp.cpp
 * @author  isnullxbh
 * @date    2019-02-08 13:38
 * @version 0.0.1
 */

#include "xne/domains/inet/tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define AF_INET4 (AF_INET)

namespace  xne {
namespace  net {
namespace inet {

int tcp::family() const noexcept {
    return (protocol_version::v6 == version_)
        ? AF_INET6
        : AF_INET4;
}

int tcp::type() const noexcept {
    return SOCK_STREAM;
}

int tcp::protocol() const noexcept {
    return (default_protocol_)
        ? 0
        : IPPROTO_TCP;
}

} // namespace inet
} // namespace net
} // namespace xne
