/**
 * @file    address_v6.h
 * @author  isnullxbh
 * @date    2019-02-12 01:27
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_ADDRESS_V6_H
#define XNE_DOMAINS_INET_ADDRESS_V6_H

#include <array>
#include <cstring>

#include "xne/domains/inet/basic_address.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   address_v6 address_v6.h "include/xne/domains/inet/address_v6.h"
 * @brief   IP address version 6.
 */

template<typename InetProtocol>
class address_v6 : public virtual basic_address<InetProtocol> {
private:
    enum { ipv6_size = 16 };

private:
    using super = basic_address<InetProtocol>;
    using protocol_type = InetProtocol;

protected:
    using bytes_type = std::array<byte, ipv6_size>;

public:
    explicit address_v6(const protocol_type& protocol);

protected:
    ~address_v6() = default;

protected:
    void init(const byte* data) override;

private:
    static constexpr bytes_type any_address = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};

template<typename InetProtocol>
inline address_v6<InetProtocol>::address_v6(const protocol_type& protocol)
    : super(protocol)
{}

template<typename InetProtocol>
void address_v6<InetProtocol>::init(const byte* data) {
    this->address_bytes_ = new byte[ipv6_size];
    const byte* src_data = (data)
        ? data
        : any_address.data();
    std::memcpy(this->address_bytes_, src_data, ipv6_size);
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_V6_H
