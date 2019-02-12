/**
 * @file    address_v6.h
 * @author  isnullxbh
 * @date    2019-02-12 01:27
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_ADDRESS_V6_H
#define XNE_DOMAINS_INET_ADDRESS_V6_H

#include <array>

#include "xne/core/types.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   address_v6 address_v6.h "include/xne/domains/inet/address_v6.h"
 * @brief   IP address version 6.
 */

class address_v6 {
public:
    using bytes_type = std::array<byte_t, 16>;

public:
    address_v6();
    explicit address_v6(const bytes_type& address_bytes);
    address_v6& operator=(const address_v6&) = default;

public:
    static address_v6 make_address(const char* str);
    const bytes_type& to_bytes() const noexcept;

protected:
    bytes_type address_bytes_;
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_V6_H
