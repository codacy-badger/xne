/**
 * @file    test.cpp
 * @author  isnullxbh
 * @date    2019-02-12 16:18
 * @version 0.0.1
 */

#include "xne/domains/inet/tcp.h"
#include "xne/domains/inet/address.h"

#include "test.h"

namespace net = xne::net;

bool case_basic_address_operations();

int main() {
    xne::testing::test test;
    test.add_case({ "basic address operations", case_basic_address_operations });
    test.perform();

    return test.passed();
}

bool case_basic_address_operations() {
    using protocol_t = net::inet::tcp;
    const protocol_t protocol = net::inet::tcp(net::inet::protocol_version::v4);
//    using address_t = net::inet::address<protocol_t>;
//    address_t address { protocol };
//    std::cout << "bytes: " << address.to_v6().as_string() << std::endl;
//    return address.to_v4().as_string() == "0.0.0.0";

    std::string ip_str { "192.168.0.1" };
    using address_t = net::inet::address<protocol_t>;
    address_t::make_address(protocol, ip_str);
    return true;
}
