//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>

#include <lexy/input/string_input.hpp>

#include "../include/az_math/function_parser.hpp"

TEST(GrammarTest, Addition) {
    auto addition = lexy::zstring_input("x+5");
    auto additionOfNums = lexy::zstring_input("0.34+5+6.34");
    auto additionOfXes = lexy::zstring_input("x+x+x+x+x+x+x");

    EXPECT_TRUE(lexy::match<az::grammar::expression>(addition));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(additionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(additionOfXes));
}

TEST(GrammarTest, Subtraction) {
    auto subtraction = lexy::zstring_input("x-5");
    auto subtractionOfNums = lexy::zstring_input("0.34-5-6.34");
    auto subtractionOfXes = lexy::zstring_input("x-x-x-x-x-x-x");

    EXPECT_TRUE(lexy::match<az::grammar::expression>(subtraction));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(subtractionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(subtractionOfXes));
}

TEST(GrammarTest, Multiplication) {
    auto multiplication = lexy::zstring_input("x*5");
    auto multiplicationOfNums = lexy::zstring_input("0.34*5*6.34");
    auto multiplicationOfXes = lexy::zstring_input("x*x*x*x*x*x*x");

    EXPECT_TRUE(lexy::match<az::grammar::expression>(multiplication));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(multiplicationOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(multiplicationOfXes));
}

TEST(GrammarTest, Division) {
    auto division = lexy::zstring_input("x/5");
    auto divisionOfNums = lexy::zstring_input("0.34/5/6.34");
    auto divisionOfXes = lexy::zstring_input("x/x/x/x/x/x/x");

    EXPECT_TRUE(lexy::match<az::grammar::expression>(division));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(divisionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(divisionOfXes));
}

TEST(GrammarTest, Exponentiation) {
    auto exponentiation = lexy::zstring_input("x^5");
    auto exponentiationOfNums = lexy::zstring_input("0.34^5^6.34");
    auto exponentiationOfXes = lexy::zstring_input("x^x^x^x^x^x^x");

    EXPECT_TRUE(lexy::match<az::grammar::expression>(exponentiation));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(exponentiationOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(exponentiationOfXes));
}

TEST(GrammarTest, FunctionKeywords) {
    auto sine = lexy::zstring_input("sin(x)");
    auto cosine = lexy::zstring_input("cos(x)");
    auto tangent = lexy::zstring_input("tan(x)");
    auto cotangent = lexy::zstring_input("cot(x)");
    auto squareRoot = lexy::zstring_input("sqrt(x)");
    auto cubeRoot = lexy::zstring_input("cbrt(x)");

    EXPECT_TRUE(lexy::match<az::grammar::expression>(sine));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(cosine));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(tangent));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(cotangent));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(squareRoot));
    EXPECT_TRUE(lexy::match<az::grammar::expression>(cubeRoot));
}
