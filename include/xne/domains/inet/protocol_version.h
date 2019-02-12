/**
 * @file    protocol_version.h
 * @author  isnullxbh
 * @date    2019-02-12 13:51
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_PROTOCOL_VERSION_H
#define XNE_DOMAINS_INET_PROTOCOL_VERSION_H

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   protocol_version protocol_version.h "include/xne/domains/inet/protocol_version.h"
 * @brief   Specifies the version of the uses Internet protocol.
 */

enum class protocol_version {
    v4,     ///< InterNetwork version 4.
    v6      ///< InterNetwork version 6.
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_PROTOCOL_VERSION_H
