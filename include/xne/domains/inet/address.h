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
    address();
    explicit address(const protocol_type& protocol);
    address(const address& other_address);
    address& operator=(const address& other_address);
    virtual ~address();

    address(address&&) = delete;
    address& operator=(address&&) = delete;

public:
    const address_v4<protocol_type>& to_v4() const noexcept;
    const address_v6<protocol_type>& to_v6() const noexcept;

    const protocol_type& protocol() const noexcept override;

    static address make_address(const protocol_type& protocol, const std::string& str);

protected:
    void init(const byte* address_bytes, size_t size) noexcept override;
    void release() noexcept override;
};

template<typename InetProtocol>
inline address<InetProtocol>::address()
    : basic_address<protocol_type>()
    , address_v4<protocol_type>()
    , address_v6<protocol_type>()
{}

template<typename InetProtocol>
inline address<InetProtocol>::address(const protocol_type& protocol)
    : basic_address<protocol_type>(protocol)
    , address_v4<protocol_type>()
    , address_v6<protocol_type>()
{}

template<typename InetProtocol>
inline address<InetProtocol>::address(const address& other_address)
    : basic_address<protocol_type>(other_address.protocol_)
    , address_v4<protocol_type>(other_address.protocol_)
    , address_v6<protocol_type>(other_address.protocol_)
{
    const auto nbytes = (protocol_version::v4 == other_address.protocol().version())
        ? address_v4<protocol_type>::length
        : address_v6<protocol_type>::length;

    this->init(other_address.address_bytes_, static_cast<size_t>(nbytes));
}

template<typename InetProtocol>
inline address<InetProtocol>& address<InetProtocol>::operator=(const address& other_address) {
    const auto nbytes = (protocol_version::v4 == other_address.protocol().version())
        ? address_v4<protocol_type>::length
        : address_v6<protocol_type>::length;

    if (this->address_bytes_)
        release();

    this->init(other_address.address_bytes_, static_cast<size_t>(nbytes));
    return *this;
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
inline void address<InetProtocol>::init(const byte* address_bytes, size_t size) noexcept {
    if (protocol_version::v4 == this->protocol_.version())
        address_v4<protocol_type>::init(address_bytes, size);
    else
        address_v6<protocol_type>::init(address_bytes, size);
}

template<typename InetProtocol>
inline void address<InetProtocol>::release() noexcept {
    delete[] this->address_bytes_;
    this->address_bytes_ = nullptr;
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
