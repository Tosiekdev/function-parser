//
// Created by tosiek on 19.07.24.
//

#include <gtest/gtest.h>

#include <lexy/action/parse.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>

#include "../include/az_math/function_parser.hpp"

TEST(ParsingTest, ParseNumber) {
    auto integer = lexy::zstring_input("5");
    auto decimal = lexy::zstring_input("3.14");
    auto integerResult = lexy::parse<az::grammar::number>(integer, lexy_ext::report_error);
    auto decimalResult = lexy::parse<az::grammar::number>(decimal, lexy_ext::report_error);
    ASSERT_TRUE(integerResult.has_value());
    EXPECT_DOUBLE_EQ(integerResult.value()->evaluate(0), 5.0);
    ASSERT_TRUE(decimalResult.has_value());
    EXPECT_DOUBLE_EQ(decimalResult.value()->evaluate(0), 3.14);
}

TEST(ParsingTest, ParseX) {
    auto var = lexy::zstring_input("x");
    auto result = lexy::parse<az::grammar::x>(var, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    auto value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14);
}

TEST(ParsingTest, ParseProduction) {
    auto var = lexy::zstring_input("x");
    auto result = lexy::parse<az::grammar::expression>(var, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Expression>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14);
}

TEST(ParsingTest, Functions) {
    auto sin = lexy::zstring_input("sin(x)");
    auto cos = lexy::zstring_input("cos(x)");
    auto tan = lexy::zstring_input("tan(x)");
    auto cot = lexy::zstring_input("cot(x)");
    auto sqrt = lexy::zstring_input("sqrt(x)");
    auto cbrt = lexy::zstring_input("cbrt(x)");
    auto result = lexy::parse<az::grammar::expression>(sin, lexy_ext::report_error);
    auto result1 = lexy::parse<az::grammar::expression>(cos, lexy_ext::report_error);
    auto result2 = lexy::parse<az::grammar::expression>(tan, lexy_ext::report_error);
    auto result3 = lexy::parse<az::grammar::expression>(cot, lexy_ext::report_error);
    auto result4 = lexy::parse<az::grammar::expression>(sqrt, lexy_ext::report_error);
    auto result5 = lexy::parse<az::grammar::expression>(cbrt, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(result1.has_value());
    ASSERT_TRUE(result2.has_value());
    ASSERT_TRUE(result3.has_value());
    ASSERT_TRUE(result4.has_value());
    ASSERT_TRUE(result5.has_value());
    EXPECT_DOUBLE_EQ(result.value()->evaluate(3.14), std::sin(3.14));
    EXPECT_DOUBLE_EQ(result1.value()->evaluate(3.14), std::cos(3.14));
    EXPECT_DOUBLE_EQ(result2.value()->evaluate(3.14), std::tan(3.14));
    EXPECT_DOUBLE_EQ(result3.value()->evaluate(3.14), std::cos(3.14) / std::sin(3.14));
    EXPECT_DOUBLE_EQ(result4.value()->evaluate(3.14), std::sqrt(3.14));
    EXPECT_DOUBLE_EQ(result5.value()->evaluate(3.14), std::cbrt(3.14));
}

TEST(ParsingTest, Exponentitation) {
    auto exp = lexy::zstring_input("x^5");
    auto result = lexy::parse<az::grammar::expression>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Expression>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), std::pow(3.14, 5));
}

TEST(ParsingTest, Multiplication) {
    auto exp = lexy::zstring_input("x*5");
    auto result = lexy::parse<az::grammar::expression>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Expression>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14*5);
}

TEST(ParsingTest, Division) {
    auto exp = lexy::zstring_input("x/5");
    auto result = lexy::parse<az::grammar::expression>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Expression>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14/5);
}

TEST(ParsingTest, Addition) {
    auto exp = lexy::zstring_input("x+5");
    auto result = lexy::parse<az::grammar::expression>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Expression>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14+5);
}

TEST(ParsingTest, Subtraction) {
    auto exp = lexy::zstring_input("x-5");
    auto result = lexy::parse<az::grammar::expression>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Expression>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14-5);
}

TEST(ParsingTest, OperatorPrecedence) {
    auto exp = lexy::zstring_input("(2+5)*2+3*5^2");
    auto expWithX = lexy::zstring_input("(2+x)*2+3*x^x");
    auto result = lexy::parse<az::grammar::expression>(exp, lexy_ext::report_error);
    auto result2 = lexy::parse<az::grammar::expression>(expWithX, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(result2.has_value());
    EXPECT_EQ(result.value()->evaluate(3.14), (2+5)*2+3*std::pow(5,2));
    EXPECT_EQ(result2.value()->evaluate(3.14), (2+3.14)*2+3*std::pow(3.14,3.14));
}
