/**
 * @file    socket_base.cpp
 * @author  isnullxbh
 * @date    2019-01-16 11:27
 * @version 0.0.1
 */

#include "xne/sockets/socket_base.h"

namespace xne {
namespace net {

const socket_base::handle_type socket_base::invalid_handle = -1;

bool socket_base::set_option(basic_socket_option& option, std::error_code& ec) {
    return option.set(*this, ec);
}

bool socket_base::get_option(basic_socket_option& option, std::error_code& ec) {
    return option.get(*this, ec);
}

} // namespace net
} // namespace xne
