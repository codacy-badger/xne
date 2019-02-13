/**
 * @file    tcp_connector.cpp
 * @author  isnullxbh
 * @date    2019-02-13 01:36
 * @version 0.0.1
 */

#include "xne/domains/inet/tcp_connector.h"

#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

namespace  xne {
namespace  net {
namespace inet {

tcp_connector::tcp_connector(const protocol_type& protocol, socket_type&& socket)
    : basic_connector(protocol, std::move(socket))
{}

bool tcp_connector::connect(const endpoint_type& endpoint, std::error_code& ec) {
    const auto& protocol = endpoint.ip_address().protocol();
    switch (protocol.version()) {
        case protocol_version::v4: {
            sockaddr_in sa {};
            std::memset(&sa, '\0', sizeof(sa));
            sa.sin_family = static_cast<decltype(sa.sin_family)>(protocol.family());
            sa.sin_port = endpoint.port();
            std::memcpy(&sa.sin_addr.s_addr
                , endpoint.ip_address().to_v4().to_bytes()
                , endpoint.ip_address().to_v4().ipv4_size);
            std::string ip(::inet_ntoa(sa.sin_addr));
            std::cout << "IP: " << ip << std::endl;
            if (::connect(socket_.native_handle(), reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) < 0) {
                ec.assign(errno, std::system_category());
                return false;
            }
        }
        break;

        case protocol_version::v6: {
            sockaddr_in6 sa {};
            std::memset(&sa, '\0', sizeof(sa));
            sa.sin6_family = static_cast<decltype(sa.sin6_family)>(protocol.family());
            sa.sin6_port = endpoint.port();
            std::memcpy(&sa.sin6_addr
                , endpoint.ip_address().to_v6().to_bytes()
                , endpoint.ip_address().to_v6().ipv6_size);
            if (::connect(socket_.native_handle(), reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) < 0) {
                ec.assign(errno, std::system_category());
                return false;
            }
        }
        break;
    }
    return true;
}

} // namespace inet
} // namespace net
} // namespace xne
