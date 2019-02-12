/**
 * @file    basic_buffer_view.h
 * @author  isnullxbh
 * @date    2019-02-08 17:12
 * @version 0.0.1
 */

#ifndef XNE_IO_BASIC_BUFFER_VIEW_H
#define XNE_IO_BASIC_BUFFER_VIEW_H

#include <cstddef>

namespace xne {
namespace net {

/**
 * @class   basic_buffer_view
 */

class basic_buffer_view {
public:
    using char_type = char;

public:
    basic_buffer_view(void* data, size_t size);
    virtual ~basic_buffer_view() = default;

    basic_buffer_view(const basic_buffer_view&) = delete;
    basic_buffer_view& operator=(const basic_buffer_view&) = delete;
    basic_buffer_view& operator=(basic_buffer_view&&) = delete;

public:
    virtual void*   data() const noexcept;
    virtual size_t  size() const noexcept;
    virtual void    resize(size_t new_size) = 0;

protected:
    void*   data_;
    size_t  size_;
};

} // namespace net
} // namespace xne

#endif  // XNE_IO_BASIC_BUFFER_VIEW_H
