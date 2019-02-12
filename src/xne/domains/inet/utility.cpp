/**
 * @file    utility.cpp
 * @author  isnullxbh
 * @date    2019-02-12 15:39
 * @version 0.0.1
 */

#include "xne/domains/inet/utility.h"

#include <stdexcept>
#include <memory>

#include <arpa/inet.h>

#ifndef in6_addr_t
using in6_addr_t = in6_addr;
#endif  // in6_addr_t

#define INET4_ADDRSTRLEN (INET_ADDRSTRLEN)

namespace  xne {
namespace  net {
namespace inet {

void utility::presentation_to_network_address(const basic_protocol& protocol, const std::string& str, address_base& address) {
    if (::inet_pton(protocol.family(), str.c_str(), address.address_bytes_) <= 0) {
        throw std::runtime_error("invalid IP address");
    }
}

void utility::network_address_to_presentation(const basic_protocol& protocol, std::string& str, const address_base& address) {
    const socklen_t buf_sz =
        (protocol.family() == AF_INET)
            ? INET4_ADDRSTRLEN
            : INET6_ADDRSTRLEN;

    std::unique_ptr<char[]> buf { new char[buf_sz] };
    if (!::inet_ntop(protocol.family(), address.to_bytes(), buf.get(), buf_sz)) {
        throw std::runtime_error("invalid IP address");
    }

    str = std::string(buf.get());
}

} // namespace inet
} // namespace net
} // namespace xne
