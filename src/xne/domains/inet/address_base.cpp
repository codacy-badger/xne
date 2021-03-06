/**
 * @file    address_base.cpp
 * @author  isnullxbh
 * @date    2019-02-12 15:12
 * @version 0.0.1
 */

#include "xne/domains/inet/address_base.h"

namespace  xne {
namespace  net {
namespace inet {

address_base::address_base()
    : address_bytes_(nullptr)
{}

const byte* address_base::to_bytes() const noexcept {
    return address_bytes_;
}

} // namespace inet
} // namespace net
} // namespace xne
