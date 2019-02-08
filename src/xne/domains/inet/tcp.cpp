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

namespace xne {
namespace net {
namespace inet {

tcp::tcp(bool v6)
    : is_v6_(v6)
{}

int tcp::family() const noexcept {
    return (is_v6_)
        ? AF_INET6
        : AF_INET;
}

int tcp::type() const noexcept {
    return SOCK_STREAM;
}

int tcp::protocol() const noexcept {
    return IPPROTO_TCP;
}

} // inet
} // net
} // xne
