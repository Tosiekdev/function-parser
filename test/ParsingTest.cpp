//
// Created by tosiek on 19.07.24.
//

#include <gtest/gtest.h>

#include <lexy/action/parse.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>

#include "../src/library.hpp"

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
    auto result = lexy::parse<az::grammar::production>(var, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14);
}

TEST(ParsingTest, Sine) {
    auto exp = lexy::zstring_input("sin(x)");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), std::sin(3.14));
}

TEST(ParsingTest, Exponentitation) {
    auto exp = lexy::zstring_input("x^5");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), std::pow(3.14, 5));
}

TEST(ParsingTest, Multiplication) {
    auto exp = lexy::zstring_input("x*5");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14*5);
}

TEST(ParsingTest, Division) {
    auto exp = lexy::zstring_input("x/5");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14/5);
}

TEST(ParsingTest, Addition) {
    auto exp = lexy::zstring_input("x+5");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14+5);
}

TEST(ParsingTest, Subtraction) {
    auto exp = lexy::zstring_input("x-5");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 3.14-5);
}

TEST(ParsingTest, OperatorPrecedence) {
    auto exp = lexy::zstring_input("(2+5)*2+3*5^2");
    auto result = lexy::parse<az::grammar::production>(exp, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    const std::shared_ptr<az::Production>& value = result.value();
    EXPECT_EQ(value->evaluate(3.14), 89);
}
