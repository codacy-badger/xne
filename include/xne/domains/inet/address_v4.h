/**
 * @file    address_v4.h
 * @author  isnullxbh
 * @date    2019-02-12 01:25
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_ADDRESS_V4_H
#define XNE_DOMAINS_INET_ADDRESS_V4_H

#include <array>
#include <cstring>

#include "xne/domains/inet/basic_address.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   address_v4 address_v4.h "include/xne/domains/inet/address_v4.h"
 * @brief   IP address version 4.
 */

template<typename InetProtocol>
class address_v4 : public virtual basic_address<InetProtocol> {
private:
    enum { ipv4_size = 4 };

private:
    using super = basic_address<InetProtocol>;
    using protocol_type = InetProtocol;

protected:
    using bytes_type = std::array<byte, ipv4_size>;

public:
    explicit address_v4(const protocol_type& protocol);

protected:
    ~address_v4() = default;

protected:
    void init(const byte* data) override;

private:
    static constexpr bytes_type any_address = { 0, 0, 0, 0 };
    static constexpr bytes_type loopback_address = { 127, 0, 0, 1 };
};

template<typename InetProtocol>
inline address_v4<InetProtocol>::address_v4(const protocol_type& protocol)
    : super(protocol)
{}

template<typename InetProtocol>
inline void address_v4<InetProtocol>::init(const byte* data) {
    this->address_bytes_ = new byte[ipv4_size];
    const byte* src_data = (data)
        ? data
        : any_address.data();
    std::memcpy(this->address_bytes_, src_data, ipv4_size);
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_V4_H
