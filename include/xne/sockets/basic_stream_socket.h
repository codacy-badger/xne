/**
 * @file    basic_stream_socket.h
 * @author  isnullxbh
 * @date    2019-01-16 19:31
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_BASIC_STREAM_SOCKET_H
#define XNE_SOCKETS_BASIC_STREAM_SOCKET_H

#include "xne/sockets/basic_socket.h"

namespace xne {
namespace net {

template<typename Protocol>
class basic_stream_socket : public basic_socket<Protocol> {
public:
    basic_stream_socket() = default;
};

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_STREAM_SOCKET_H
