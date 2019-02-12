/**
 * @file    utility.h
 * @author  isnullxbh
 * @date    2019-02-12 15:26
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_UTILITY_H
#define XNE_DOMAINS_INET_UTILITY_H

#include <string>

#include "xne/core/basic_protocol.h"
#include "xne/domains/inet/address_base.h"

namespace  xne {
namespace  net {
namespace inet {

class utility {
public:
    static void presentation_to_network_address(const basic_protocol& protocol, const std::string& str, address_base& address);
    static void network_address_to_presentation(const basic_protocol& protocol, std::string& buf, const address_base& address);
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_UTILITY_H
