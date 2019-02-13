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
    address(const address& other_address);
    virtual ~address();

    address(address&&) = delete;
    address& operator=(const address&) = delete;
    address& operator=(address&&) = delete;

protected:
    address(const protocol_type& protocol, const typename address_v4<protocol_type>::bytes_type& address_bytes);
    address(const protocol_type& protocol, const typename address_v6<protocol_type>::bytes_type& address_bytes);

public:
    const address_v4<protocol_type>& to_v4() const noexcept;
    const address_v6<protocol_type>& to_v6() const noexcept;

    const protocol_type& protocol() const noexcept override;

    static address make_address(const protocol_type& protocol, const std::string& str);

protected:
    void init(const byte* data) override;
};

template<typename InetProtocol>
inline address<InetProtocol>::address(const protocol_type& protocol)
    : basic_address<protocol_type>(protocol)
    , address_v4<protocol_type>(protocol)
    , address_v6<protocol_type>(protocol)

{
    init(nullptr);
}

template<typename InetProtocol>
address<InetProtocol>::address(const address& other_address)
    : basic_address<protocol_type>(other_address.protocol_)
    , address_v4<protocol_type>(other_address.protocol_)
    , address_v6<protocol_type>(other_address.protocol_)
{
    this->init(other_address.address_bytes_);
}

template<typename InetProtocol>
inline address<InetProtocol>::address(const protocol_type& protocol, const typename address_v4<InetProtocol>::bytes_type& address_bytes)
    : basic_address<protocol_type>(protocol)
    , address_v4<protocol_type>(protocol)
    , address_v6<protocol_type>(protocol)
{
    init(address_bytes.data());
}

template<typename InetProtocol>
inline address<InetProtocol>::address(const protocol_type& protocol, const typename address_v6<InetProtocol>::bytes_type& address_bytes)
    : basic_address<protocol_type>(protocol)
    , address_v4<protocol_type>(protocol)
    , address_v6<protocol_type>(protocol)
{
    allocate(address_bytes.data());
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
inline void address<InetProtocol>::init(const byte* data) {
    if (protocol_version::v4 == this->protocol_.version())
        address_v4<protocol_type>::init(data);
    else
        address_v6<protocol_type>::init(data);
}

template<typename InetProtocol>
inline address<InetProtocol> address<InetProtocol>::make_address(const protocol_type& protocol, const std::string& str) {
    address new_address { protocol };
    inet_utils::presentation_to_network_address(protocol, str, new_address);
    return new_address;
}

template<typename InetProtocol>
inline const InetProtocol& address<InetProtocol>::protocol() const noexcept {
    return basic_address<protocol_type>::protocol();
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_H
