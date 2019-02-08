/**
 * @file    basic_stream_socket.h
 * @author  isnullxbh
 * @date    2019-01-16 19:31
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_BASIC_STREAM_SOCKET_H
#define XNE_SOCKETS_BASIC_STREAM_SOCKET_H

#include "xne/sockets/basic_socket.h"
#include "xne/sockets/socket_syscalls.h"
#include "xne/io/basic_buffer_view.h"

namespace xne {
namespace net {

/**
 * @class   basic_stream_socket basic_stream_socket.h "include/xne/sockets/basic_stream_socket.h"
 * @brief   A class that forms a base for all stream sockets.
 * @tparam  Protocol    Specifies a particular network protocol to be used
 *                      with socket.
 */

template<typename Protocol>
class basic_stream_socket : public basic_socket<Protocol> {
public:
    using cflags = socket_base::cflags;

public:
    basic_stream_socket() = default;

    basic_stream_socket(const basic_stream_socket&) = delete;
    basic_stream_socket& operator==(const basic_stream_socket&) = delete;
    basic_stream_socket& operator==(basic_stream_socket&&) = delete;

protected:
    explicit basic_stream_socket(socket_base::handle_type handle);

public:
    size_t send(basic_buffer_view& buf, std::error_code& ec, cflags flags = 0);
    size_t receive(basic_buffer_view& buf, std::error_code& ec, cflags flags = 0);
};

template<typename Protocol>
basic_stream_socket<Protocol>::basic_stream_socket(socket_base::handle_type handle)
    : basic_socket<Protocol>(handle)
{}

template<typename Protocol>
inline size_t basic_stream_socket<Protocol>::send(basic_buffer_view& buf, std::error_code& ec, cflags flags) {
    return syscall::send(this->native_handle()
        , static_cast<const char*>(buf.data())
        , buf.size()
        , ec
        , flags);
}

template<typename Protocol>
inline size_t basic_stream_socket<Protocol>::receive(basic_buffer_view& buf, std::error_code& ec, cflags flags) {
    return syscall::receive(this->native_handle()
        , static_cast<char*>(buf.data())
        , buf.size()
        , ec
        , flags);
}

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_STREAM_SOCKET_H
