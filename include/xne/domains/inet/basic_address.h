/**
 * @file    basic_address.h
 * @author  isnullxbh
 * @date    2019-02-12 13:32
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_BASIC_ADDRESS_H
#define XNE_DOMAINS_INET_BASIC_ADDRESS_H

#include "xne/domains/inet/address_base.h"
#include "xne/domains/inet/utility.h"

namespace  xne {
namespace  net {
namespace inet {

using inet_utils = utility;

template<typename InetProtocol>
class basic_address : public address_base {
public:
    using super = address_base;
    using protocol_type = InetProtocol;

public:
    basic_address(const basic_address&) = delete;
    basic_address(basic_address&&) = delete;
    basic_address& operator=(basic_address&&) = delete;

protected:
    explicit basic_address(const protocol_type& protocol);
    basic_address& operator=(const basic_address&);
    ~basic_address() override = default;

public:
    virtual const protocol_type& protocol() const noexcept;
    std::string as_string() const noexcept;

protected:
    virtual void init(const byte* data) = 0;

protected:
    protocol_type protocol_;
};

template<typename InetProtocol>
inline basic_address<InetProtocol>::basic_address(const protocol_type& protocol)
    : super()
    , protocol_(protocol)
{}

template<typename InetProtocol>
inline const InetProtocol& basic_address<InetProtocol>::protocol() const noexcept {
    return protocol_;
}

template<typename InetProtocol>
inline std::string basic_address<InetProtocol>::as_string() const noexcept {
    std::string ip_address;
    inet_utils::network_address_to_presentation(protocol_, ip_address, *this);
    return ip_address;
}

template<typename InetProtocol>
inline basic_address<InetProtocol>& basic_address<InetProtocol>::operator=(const basic_address& other_address) {
    this->protocol_ = other_address.protocol_;
    return *this;
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_BASIC_ADDRESS_H
