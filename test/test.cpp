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

TEST(GrammarTest, Sine) {
    auto sine = lexy::zstring_input("sin(x)");

    EXPECT_TRUE(lexy::match<az::grammar::production>(sine));
}
