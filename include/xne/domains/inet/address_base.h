/**
 * @file    address_base.h
 * @author  isnullxbh
 * @date    2019-02-12 15:09
 * @version 0.0.1
 */

#ifndef XNE_DOMAINS_INET_ADDRESS_BASE_H
#define XNE_DOMAINS_INET_ADDRESS_BASE_H

#include <string>

#include "xne/core/types.h"

namespace  xne {
namespace  net {
namespace inet {

/**
 * @class   address_base address_base.h "include/xne/domains/inet/address_base.h"
 * @brief   A class that forms a base for the other classes that represents IP
 *          addresses. This class allows to use helping functions (such as
 *          inet_pton) more simply comparing to class template parametrized by
 *          particular protocol.
 */

class address_base {
public:
    virtual ~address_base() = default;

    address_base(const address_base&) = delete;
    address_base(address_base&&) = delete;
    address_base& operator=(address_base&&) = delete;

protected:
    address_base();
    address_base& operator=(const address_base&);

public:
    const byte* to_bytes() const noexcept;

protected:
    virtual void init(const byte* address_bytes, size_t size) noexcept = 0;
    virtual void release() noexcept = 0;

protected:
    byte* address_bytes_;

    friend class utility;
};

} // namespace inet
} // namespace net
} // namespace xne

#endif  // XNE_DOMAINS_INET_ADDRESS_BASE_H
