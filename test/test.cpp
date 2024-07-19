//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/action/parse.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>

#include "../src/library.hpp"

TEST(GrammarTest, Addition) {
    auto addition = lexy::zstring_input("x+5");
    auto additionOfNums = lexy::zstring_input("0.34+5+6.34");
    auto additionOfXes = lexy::zstring_input("x+x+x+x+x+x+x");

    EXPECT_TRUE(lexy::match<az::grammar::production>(addition));
    EXPECT_TRUE(lexy::match<az::grammar::production>(additionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::production>(additionOfXes));
}

TEST(GrammarTest, Subtraction) {
    auto subtraction = lexy::zstring_input("x-5");
    auto subtractionOfNums = lexy::zstring_input("0.34-5-6.34");
    auto subtractionOfXes = lexy::zstring_input("x-x-x-x-x-x-x");

    EXPECT_TRUE(lexy::match<az::grammar::production>(subtraction));
    EXPECT_TRUE(lexy::match<az::grammar::production>(subtractionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::production>(subtractionOfXes));
}

TEST(GrammarTest, Multiplication) {
    auto multiplication = lexy::zstring_input("x*5");
    auto multiplicationOfNums = lexy::zstring_input("0.34*5*6.34");
    auto multiplicationOfXes = lexy::zstring_input("x*x*x*x*x*x*x");

    EXPECT_TRUE(lexy::match<az::grammar::production>(multiplication));
    EXPECT_TRUE(lexy::match<az::grammar::production>(multiplicationOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::production>(multiplicationOfXes));
}

TEST(GrammarTest, Division) {
    auto division = lexy::zstring_input("x/5");
    auto divisionOfNums = lexy::zstring_input("0.34/5/6.34");
    auto divisionOfXes = lexy::zstring_input("x/x/x/x/x/x/x");

    EXPECT_TRUE(lexy::match<az::grammar::production>(division));
    EXPECT_TRUE(lexy::match<az::grammar::production>(divisionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::production>(divisionOfXes));
}

TEST(GrammarTest, Exponentiation) {
    auto exponentiation = lexy::zstring_input("x^5");
    auto exponentiationOfNums = lexy::zstring_input("0.34^5^6.34");
    auto exponentiationOfXes = lexy::zstring_input("x^x^x^x^x^x^x");

    EXPECT_TRUE(lexy::match<az::grammar::production>(exponentiation));
    EXPECT_TRUE(lexy::match<az::grammar::production>(exponentiationOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::production>(exponentiationOfXes));
}

TEST(GrammarTest, FunctionKeywords) {
    auto sine = lexy::zstring_input("sin(x)");
    auto cosine = lexy::zstring_input("cos(x)");
    auto tangent = lexy::zstring_input("tan(x)");
    auto cotangent = lexy::zstring_input("cot(x)");
    auto squareRoot = lexy::zstring_input("sqrt(x)");
    auto cubeRoot = lexy::zstring_input("cbrt(x)");

    EXPECT_TRUE(lexy::match<az::grammar::production>(sine));
    EXPECT_TRUE(lexy::match<az::grammar::production>(cosine));
    EXPECT_TRUE(lexy::match<az::grammar::production>(tangent));
    EXPECT_TRUE(lexy::match<az::grammar::production>(cotangent));
    EXPECT_TRUE(lexy::match<az::grammar::production>(squareRoot));
    EXPECT_TRUE(lexy::match<az::grammar::production>(cubeRoot));
}

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
