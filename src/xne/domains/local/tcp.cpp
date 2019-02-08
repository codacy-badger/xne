/**
 * @file    tcp.cpp
 * @author  isnullxbh
 * @date    2019-01-16 14:08
 * @version 0.0.1
 */

#include "xne/domains/local/tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace xne {
namespace net {
namespace local {

int tcp::family() const noexcept {
    return AF_LOCAL;
}

int tcp::type() const noexcept {
    return SOCK_STREAM;
}

int tcp::protocol() const noexcept {
    return 0;
}

} // namespace local
} // namespace net
} // namespace xne
