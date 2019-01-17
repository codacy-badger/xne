/**
 * @file    case.h
 * @author  isnullxbh
 * @date    2019-01-17 02:33
 * @version 0.0.1
 */

#ifndef XNE_TESTS_TEST_H
#define XNE_TESTS_TEST_H

#include <functional>
#include <vector>
#include <string>

namespace xne {
namespace testing {

class test {
public:
    class testcase {
    public:
        using function_type = std::function<bool()>;

    public:
        testcase(std::string_view name, function_type function);

    public:
        const std::string&      name()      const noexcept;
        const function_type&    function()  const noexcept;

    protected:
        std::string     name_;
        function_type   function_;
    };

protected:
    using testcase_type = testcase;
    using testcase_list_type = std::vector<testcase_type>;

public:
    void add_case(testcase test_case) {
        testcases_.emplace_back(test_case);
    }

    void perform();
    int  passed() const noexcept;

public:
    test();

protected:
    testcase_list_type  testcases_;
    bool                passed_;
};

} // namespace testing
} // namespace xne

#endif  // XNE_TESTS_TEST_H
