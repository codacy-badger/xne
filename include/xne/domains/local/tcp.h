/**
 * @file    tcp.h
 * @author  isnullxbh
 * @date    2019-01-16 14:04
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_LOCAL_TCP_H
#define XNE_DOMAINS_LOCAL_TCP_H

#include "xne/core/basic_protocol.h"

namespace xne {
namespace net {
namespace local {

class tcp : public basic_protocol {
public:
    tcp() = default;

public:
    int family() const noexcept override;
    int type() const noexcept override;
    int protocol() const noexcept override;
};

} // namespace local
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_LOCAL_TCP_H
