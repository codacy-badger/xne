/**
 * @file    address_v4.h
 * @author  isnullxbh
 * @date    2019-02-12 01:25
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_ADDRESS_V4_H
#define XNE_DOMAINS_INET_ADDRESS_V4_H

#include <array>

#include "xne/core/types.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   address_v4 address_v4.h "include/xne/domains/inet/address_v4.h"
 * @brief   IP address version 4.
 */

class address_v4 {
public:
    using bytes_type = std::array<byte_t, 4>;

public:
    address_v4();
    explicit address_v4(const bytes_type& address_bytes);
    address_v4& operator=(const address_v4& address) = default;

public:
    static address_v4 make_address(const char* str);
    const bytes_type& to_bytes() const noexcept;

protected:
    bytes_type address_bytes_;
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_V4_H
