/**
 * @file    basic_socket.h
 * @author  isnullxbh
 * @date    2019-01-16 07:14
 * @version 0.0.1
 */

#ifndef XNE_SOCKETS_BASIC_SOCKET_H
#define XNE_SOCKETS_BASIC_SOCKET_H

#include <system_error>

#include "xne/sockets/socket_base.h"
#include "xne/sockets/socket_syscalls.h"

namespace xne {
namespace net {

/**
 * @class   basic_socket basic_socket.h "include/xne/sockets/basic_socket.h"
 * @brief   A class that forms a base for all sockets.
 * @tparam  Protocol    Specifies a particular network protocol to be used
 *                      with socket.
 */

template<typename Protocol>
class basic_socket : public socket_base {
public:
    using protocol_type = Protocol;
    using releaser_type = std::function<void(basic_socket<Protocol>*)>;

public:
    basic_socket();
    virtual ~basic_socket();

    basic_socket(const basic_socket&) = delete;
    basic_socket& operator=(const basic_socket&) = delete;
    basic_socket& operator=(basic_socket&&) = delete;

public:
    void            open(const protocol_type& protocol, std::error_code& ec);
    void            close(std::error_code& ec);
    void            close();
    handle_type     native_handle() const noexcept;
    bool            is_open() const noexcept;

protected:
    void            try_autoclose();

public:
    bool autoclose;

protected:
    releaser_type   releaser_;

private:
    handle_type     handle_;

protected:
    static void default_releaser(basic_socket<Protocol>* self);
};

template<typename Protocol>
inline basic_socket<Protocol>::basic_socket()
    : autoclose(false)
    , releaser_(basic_socket<Protocol>::default_releaser)
    , handle_(invalid_handle)
{}

template<typename Protocol>
inline basic_socket<Protocol>::~basic_socket() {
    if (releaser_)
        releaser_(this);
}

template<typename Protocol>
inline void basic_socket<Protocol>::open(const protocol_type& protocol, std::error_code& ec) {
    if (invalid_handle != handle_)
        throw std::logic_error("socket already open");
    handle_ = syscall::socket(protocol, &ec);
}

template<typename Protocol>
inline void basic_socket<Protocol>::close(std::error_code& ec) {
    syscall::close(handle_, &ec);
}

template<typename Protocol>
inline void basic_socket<Protocol>::close() {
    syscall::close(handle_, nullptr);
}

template<typename Protocol>
inline socket_base::handle_type basic_socket<Protocol>::native_handle() const noexcept {
    return handle_;
}

template<typename Protocol>
inline bool basic_socket<Protocol>::is_open() const noexcept {
    return invalid_handle != handle_;
}

template<typename Protocol>
inline void basic_socket<Protocol>::default_releaser(basic_socket<Protocol>* self) {
    self->try_autoclose();
}

template<typename Protocol>
inline void basic_socket<Protocol>::try_autoclose() {
    if (autoclose && is_open()) {
        close();
    }
}

} // namespace net
} // namespace xne

#endif  // XNE_SOCKETS_BASIC_SOCKET_H
