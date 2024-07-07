//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include "../src/library.hpp"

TEST(GrammarTest, Addition) {
    auto addition = lexy::zstring_input("x+5");

    EXPECT_TRUE(lexy::match<az::grammar::production>(addition));
}
