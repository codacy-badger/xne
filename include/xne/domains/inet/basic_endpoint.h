/**
 * @file    basic_endpoint.h
 * @author  isnullxbh
 * @date    2019-02-13 00:45
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_BASIC_ENDPOINT_H
#define XNE_DOMAINS_INET_BASIC_ENDPOINT_H

#include "xne/domains/inet/address.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   basic_endpoint basic_endpoint.h "include/xne/domains/inet/basic_endpoint.h"
 * @tparam  InetProtocol    An Internet protocol which specifies type of the
 *                          address that uses in endpoint.
 */

template<typename InetProtocol>
class basic_endpoint {
public:
    using protocol_type = InetProtocol;
    using port_type = unsigned short;
    using address_type = address<protocol_type>;

public:
    basic_endpoint(const address_type& address, port_type port);
    virtual ~basic_endpoint() = default;

public:
    const address_type& ip_address() const noexcept;
    port_type port() const noexcept;

protected:
    address_type address_;
    port_type    port_;
};

template<typename InetProtocol>
inline basic_endpoint<InetProtocol>::basic_endpoint(const address_type& address, basic_endpoint::port_type port)
    : address_(address)
    , port_(port)
{}

template<typename InetProtocol>
inline const typename basic_endpoint<InetProtocol>::address_type& basic_endpoint<InetProtocol>::ip_address() const noexcept {
    return address_;
}

template<typename InetProtocol>
inline typename basic_endpoint<InetProtocol>::port_type basic_endpoint<InetProtocol>::port() const noexcept {
    return port_;
}

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_BASIC_ENDPOINT_H
