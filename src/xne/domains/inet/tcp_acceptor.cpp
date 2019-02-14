/**
 * @file    tcp_acceptor.cpp
 * @author  isnullxbh
 * @date    2019-02-13 15:48
 * @version 0.0.1
 */

#include "xne/domains/inet/tcp_acceptor.h"

#include <cstring>
#include <memory>

#include <netinet/in.h>
#include <arpa/inet.h>

namespace  xne {
namespace  net {
namespace inet {

tcp_acceptor::tcp_acceptor(const protocol_type& protocol, socket_type&& socket)
    : basic_acceptor(protocol, std::move(socket))
{}

bool tcp_acceptor::bind(const endpoint_type& endpoint, std::error_code& ec) {
    const auto& protocol = endpoint.ip_address().protocol();
    switch (protocol.version()) {
        case protocol_version::v4: {
            sockaddr_in sa {};
            std::memset(&sa, '\0', sizeof(sa));
            sa.sin_family = static_cast<decltype(sa.sin_family)>(protocol.family());
            sa.sin_port = htons(endpoint.port());
            std::memcpy(&sa.sin_addr
                , endpoint.ip_address().to_v4().to_bytes()
                , address_v4<protocol_type>::length);
            if (::bind(socket_.native_handle(), reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) < 0) {
                ec.assign(errno, std::system_category());
                return false;
            }
        }
        break;
        case protocol_version::v6: {
            sockaddr_in6 sa {};
            std::memset(&sa, '\0', sizeof(sa));
            sa.sin6_family = static_cast<decltype(sa.sin6_family)>(protocol.family());
            sa.sin6_port = htons(endpoint.port());
            std::memcpy(&sa.sin6_addr
                , endpoint.ip_address().to_v6().to_bytes()
                , address_v6<protocol_type>::length);
            if (::bind(socket_.native_handle(), reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) < 0) {
                ec.assign(errno, std::system_category());
                return false;
            }
        }
        break;
    }
    return true;
}

tcp_acceptor::handle_type tcp_acceptor::accept(endpoint_type& endpoint, std::error_code& ec) {
    sockaddr_storage sa {};
    auto sa_len = static_cast<socklen_t>((protocol_version::v4 == this->proto_.version())
        ? sizeof(sockaddr_in)
        : sizeof(sockaddr_in6));
    std::memset(&sa, '\0', sizeof(sa));
    socket_base::handle_type cli_handle;
    if ((cli_handle = ::accept(socket_.native_handle(), reinterpret_cast<sockaddr*>(&sa), &sa_len)) < 0) {
        ec.assign(errno, std::system_category());
        return socket_base::invalid_handle;
    }

    auto domain = (sa_len == sizeof(sockaddr_in))
        ? AF_INET
        : AF_INET6;

    auto buf_sz = (AF_INET == domain)
        ? INET_ADDRSTRLEN
        : INET6_ADDRSTRLEN;

    auto addr = (AF_INET == domain)
        ? (void*)&(reinterpret_cast<sockaddr_in*>(&sa)->sin_addr)
        : (void*)&(reinterpret_cast<sockaddr_in6*>(&sa)->sin6_addr);

    std::unique_ptr<char[]> buf { new char[buf_sz] };
    if (!::inet_ntop(domain, addr, buf.get(), static_cast<socklen_t>(buf_sz))) {
        ec.assign(errno, std::system_category());
        return socket_base::invalid_handle;
    }

    std::string ip { buf.get() };

    std::cout << "\nip: " << ip << std::endl;

    auto port = (AF_INET == domain)
            ? reinterpret_cast<sockaddr_in*>(&sa)->sin_port
            : reinterpret_cast<sockaddr_in6*>(&sa)->sin6_port;

    endpoint = endpoint_type::make_endpoint(buf.get(), ntohs(port));

    return cli_handle;
}

bool tcp_acceptor::listen(int backlog, std::error_code& ec) {
    if (::listen(socket_.native_handle(), backlog) < 0) {
        ec.assign(errno, std::system_category());
        return false;
    }
    return true;
}

} // namespace inet
} // namespace net
} // namespace xne
