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
    EXPECT_DOUBLE_EQ(integerResult.value().value, 5.0);
    ASSERT_TRUE(decimalResult.has_value());
    EXPECT_DOUBLE_EQ(decimalResult.value().value, 3.14);
}

TEST(ParsingTest, ParseX) {
    auto var = lexy::zstring_input("x");
    auto result = lexy::parse<az::grammar::x>(var, lexy_ext::report_error);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().value, 0);
}
