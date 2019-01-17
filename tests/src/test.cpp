/**
 * @file    test.cpp
 * @author  isnullxbh
 * @date    2019-01-17 10:34
 * @version 0.0.1
 */

#include "test.h"
#include <iostream>

namespace xne {
namespace testing {

test::testcase::testcase(std::string_view name, test::testcase::function_type function)
    : name_(name)
    , function_(std::move(function))
{}

const std::string& test::testcase::name() const noexcept {
    return name_;
}

const test::testcase::function_type& test::testcase::function() const noexcept {
    return function_;
}

test::test()
    : testcases_()
    , passed_(true)
{}

void test::perform() {
    for (const auto& test_case : testcases_) {
        std::cout << "test case: " << test_case.name() << std::endl;
        bool res;
        try {
            std::cout << "result: " << (res = test_case.function()()) << std::endl;
            passed_ &= res;
        } catch (...){
            std::cout << "result: got exception, failed" << std::endl;
            passed_ = false;
            break;
        }
    }
}

int test::passed() const noexcept {
    return passed_ ? 0 : 1;
}

} // namespace testing
} // namespace xne