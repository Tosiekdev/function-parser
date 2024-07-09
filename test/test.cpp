//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include "../src/library.hpp"

TEST(GrammarTest, Addition) {
    auto addition = lexy::zstring_input("x+5");
    auto additionOfNums = lexy::zstring_input("0.34+5+6.34");
    auto additionOfXes = lexy::zstring_input("x+x+x+x+x+x+x");

    EXPECT_TRUE(lexy::match<az::grammar::production>(addition));
    EXPECT_TRUE(lexy::match<az::grammar::production>(additionOfNums));
    EXPECT_TRUE(lexy::match<az::grammar::production>(additionOfXes));
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
