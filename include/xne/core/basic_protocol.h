/**
 * @file    basic_protocol.h
 * @author  isnullxbh
 * @date    2019-01-16 10:44
 * @version 0.0.1
 */

#ifndef XNE_CORE_BASIC_PROTOCOL_H
#define XNE_CORE_BASIC_PROTOCOL_H

namespace xne {
namespace net {

class basic_protocol {
public:
    virtual ~basic_protocol() = default;

public:
    virtual int family() const noexcept = 0;
    virtual int type() const noexcept = 0;
    virtual int protocol() const noexcept = 0;
};

} // namespace net
} // namespace xne

#endif  // XNE_CORE_BASIC_PROTOCOL_H
