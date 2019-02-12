/**
 * @file    address_v6.cpp
 * @author  isnullxbh
 * @date    2019-02-12 01:52
 * @version 0.0.1
 */

#include "xne/domains/inet/address_v6.h"

#include <stdexcept>

#include <arpa/inet.h>

namespace  xne {
namespace  net {
namespace inet {

#ifndef in6_addr_t
using in6_addr_t = in6_addr;
#endif  // in6_addr_t

address_v6::address_v6()
    : address_bytes_()
{
    address_bytes_.fill(0);
}

address_v6::address_v6(const bytes_type& address_bytes)
    : address_bytes_(address_bytes)
{}

address_v6 address_v6::make_address(const char* str) {
    char buf[sizeof(in6_addr_t)];
    if (::inet_pton(AF_INET6, str, buf) <= 0) {
        throw std::invalid_argument("invalid IPv6 address");
    }

    address_v6 address;
    for (size_t i = 0; i < sizeof(in6_addr_t); ++i)
        address.address_bytes_[i] = static_cast<byte_t>(buf[i]);

    return address;
}

const address_v6::bytes_type& address_v6::to_bytes() const noexcept {
    return address_bytes_;
}

} // namespace inet
} // namespace net
} // namespace xne
