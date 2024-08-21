#include <az_math/function_parser.hpp>
#include <gtest/gtest.h>

#include <numbers>

#include "lexy/dsl.hpp"
#include "lexy_ext/report_error.hpp"

TEST(OutOfDomainTest, CotangentTest) {
    const auto result = az::parse_expression("cot(x)");
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::isnan(result->evaluate(0)));
    EXPECT_TRUE(std::isnan(result->evaluate(std::numbers::pi)));
}

TEST(OutOfDomainTest, SquareRootTest) {
    const auto result = az::parse_expression("sqrt(x)");
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::isnan(result->evaluate(-1)));
    EXPECT_TRUE(std::isnan(result->evaluate(-std::numbers::pi)));
}

TEST(OutOfDomainTest, DivisionTest) {
    auto result = az::parse_expression("1/x");
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::isnan(result->evaluate(0)));
    result = az::parse_expression("1/sin(x)");
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::isnan(result->evaluate(std::numbers::pi)));
}