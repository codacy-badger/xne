/**
 * @file    address.h
 * @author  isnullxbh
 * @date    2019-02-12 01:23
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_ADDRESS_H
#define XNE_DOMAINS_INET_ADDRESS_H

#include "xne/domains/inet/address_v4.h"
#include "xne/domains/inet/address_v6.h"

namespace  xne {
namespace  net {
namespace inet {

template<typename InetProtocol>
class address : protected address_v4<InetProtocol>, protected address_v6<InetProtocol> {
public:
    using protocol_type = InetProtocol;

public:
    explicit address(const protocol_type& protocol);
    virtual ~address();

public:
    const address_v4<protocol_type>& to_v4() const noexcept;
    const address_v6<protocol_type>& to_v6() const noexcept;

protected:
    void allocate() override;

protected:
    protocol_type protocol_;
};

template<typename InetProtocol>
inline address<InetProtocol>::address(const protocol_type& protocol)
    : basic_address<protocol_type>(protocol)
    , address_v4<protocol_type>(protocol)
    , address_v6<protocol_type>(protocol)
    , protocol_(protocol)

    {
    allocate();
}

template<typename InetProtocol>
inline address<InetProtocol>::~address() {
    delete[] this->address_bytes_;
    this->address_bytes_ = nullptr;
}

template<typename InetProtocol>
inline const address_v4<InetProtocol>& address<InetProtocol>::to_v4() const noexcept {
    return *this;
}

template<typename InetProtocol>
inline const address_v6<InetProtocol>& address<InetProtocol>::to_v6() const noexcept {
    return *this;
}

template<typename InetProtocol>
inline void address<InetProtocol>::allocate() {
    if (protocol_version::v4 == protocol_.version())
        address_v4<protocol_type>::allocate();
    else
        address_v6<protocol_type>::allocate();
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_H
