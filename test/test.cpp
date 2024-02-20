//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/input/string_input.hpp>
#include "../src/library.hpp"

TEST(HelloTest, BasicAssertions) {
    auto input = lexy::zstring_input("x+x^2");
    EXPECT_EQ(lexy::match<az::grammar::atom>(input), true);
}

