//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/input/string_input.hpp>
#include "../src/library.hpp"

TEST(GrammarTest, MatchingAtom) {
    auto single = lexy::zstring_input("x");
    auto multiply = lexy::zstring_input("2x");
    auto power = lexy::zstring_input("x^5");
    auto combined = lexy::zstring_input("2x^3");
    auto number = lexy::zstring_input("3.14159");
    EXPECT_EQ(lexy::match<az::grammar::atom>(single), true);
    EXPECT_EQ(lexy::match<az::grammar::atom>(multiply), true);
    EXPECT_EQ(lexy::match<az::grammar::atom>(power), true);
    EXPECT_EQ(lexy::match<az::grammar::atom>(combined), true);
    EXPECT_EQ(lexy::match<az::grammar::atom>(number), true);
}

TEST(GrammarTest, MatchingPolynomial) {
    auto single = lexy::zstring_input("x");
    auto plus = lexy::zstring_input("x+x^2");
    auto minus = lexy::zstring_input("2x+3x^3");

    EXPECT_TRUE(lexy::match<az::grammar::polynomial>(single));
    EXPECT_TRUE(lexy::match<az::grammar::polynomial>(plus));
    EXPECT_TRUE(lexy::match<az::grammar::polynomial>(minus));
}
