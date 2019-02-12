/**
 * @file    address_v4.cpp
 * @author  isnullxbh
 * @date    2019-02-12 01:43
 * @version 0.0.1
 */

#include "xne/domains/inet/address_v4.h"

#include <stdexcept>

#include <arpa/inet.h>

namespace  xne {
namespace  net {
namespace inet {

address_v4::address_v4()
    : address_bytes_()
{
    address_bytes_.fill(0);
}

address_v4::address_v4(const bytes_type& address_bytes)
    : address_bytes_(address_bytes)
{}

address_v4 address_v4::make_address(const char* str) {
    char buf[sizeof(in_addr_t)];
    if (::inet_pton(AF_INET, str, buf) <= 0) {
        throw std::invalid_argument("invalid IPv4 address");
    }

    address_v4 address;
    for (auto i = 0; i < 4; ++i) {
        address.address_bytes_[i] = static_cast<byte_t>(buf[i]);
    }

    return address;
}

const address_v4::bytes_type& address_v4::to_bytes() const noexcept {
    return address_bytes_;
}

} // namespace inet
} // namespace net
} // namespace xne
