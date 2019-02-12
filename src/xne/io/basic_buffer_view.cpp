/**
 * @file    basic_buffer_view.cpp
 * @author  isnullxbh
 * @date    2019-02-08 17:17
 * @version 0.0.1
 */

#include "xne/io/basic_buffer_view.h"

namespace xne {
namespace net {

basic_buffer_view::basic_buffer_view(void* data, size_t size)
    : data_(data)
    , size_(size)
{}

void* basic_buffer_view::data() const noexcept {
    return data_;
}

size_t basic_buffer_view::size() const noexcept {
    return size_;
}

} // namespace net
} // namespace xne