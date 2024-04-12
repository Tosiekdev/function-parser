//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include "../src/library.hpp"

namespace test{
    struct atom {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::atom> >> lexy::dsl::eof;
    };

    struct polynomial {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::polynomial> >> lexy::dsl::eof;
    };

    struct basic_function {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::basic_function> >> lexy::dsl::eof;
    };

    struct basic_functions_chain {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::basic_functions_chain> >> lexy::dsl::eof;
    };

    struct intermediate_function {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::intermediate_function> >> lexy::dsl::eof;
    };

    struct intermediate_functions_chain {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::intermediate_functions_chain> >> lexy::dsl::eof;
    };

    struct advanced_function {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::advanced_function> >> lexy::dsl::eof;
    };

    struct advanced_functions_chain {
        static constexpr auto rule =
                lexy::dsl::p<az::grammar::advanced_functions_chain> >> lexy::dsl::eof;
    };
}

TEST(GrammarTest, Atom) {
    auto single = lexy::zstring_input("x");
    auto multiply = lexy::zstring_input("2x");
    auto power = lexy::zstring_input("x^5");
    auto combined = lexy::zstring_input("2x^3");
    auto number = lexy::zstring_input("3.14159");
    EXPECT_EQ(lexy::match<test::atom>(single), true);
    EXPECT_EQ(lexy::match<test::atom>(multiply), true);
    EXPECT_EQ(lexy::match<test::atom>(power), true);
    EXPECT_EQ(lexy::match<test::atom>(combined), true);
    EXPECT_EQ(lexy::match<test::atom>(number), true);
}

TEST(GrammarTest, Polynomial) {
    auto single = lexy::zstring_input("x");
    auto plus = lexy::zstring_input("x+x^2");
    auto minus = lexy::zstring_input("2x+3x^3");

    EXPECT_TRUE(lexy::match<test::polynomial>(single));
    EXPECT_TRUE(lexy::match<test::polynomial>(plus));
    EXPECT_TRUE(lexy::match<test::polynomial>(minus));
}

TEST(GrammarTest, BasicFunction) {
    auto sine = lexy::zstring_input("sin(x+x^2)");
    auto faulty_sine = lexy::zstring_input("sin(x+x2)");

    EXPECT_TRUE(lexy::match<test::basic_function>(sine));
    EXPECT_FALSE(lexy::match<test::basic_function>(faulty_sine));
}

TEST(GrammarTest, BasicFunctionsChain) {
    auto sum_of_sines = lexy::zstring_input("sin(x+x^2)+sin(x+2x)");
    auto sine = lexy::zstring_input("sin(x+x^2)");
    auto atom = lexy::zstring_input("x");
    auto polynomial = lexy::zstring_input("x+x^2");
    auto faulty_sine = lexy::zstring_input("sin(x+x2)");

    EXPECT_TRUE(lexy::match<test::basic_functions_chain>(sum_of_sines));
    EXPECT_TRUE(lexy::match<test::basic_functions_chain>(sine));
    EXPECT_TRUE(lexy::match<test::basic_functions_chain>(atom));
    EXPECT_TRUE(lexy::match<test::basic_functions_chain>(polynomial));
    EXPECT_FALSE(lexy::match<test::basic_functions_chain>(faulty_sine));
}

TEST(GrammarTest, IntermediateFunction) {
    auto sine_of_sine = lexy::zstring_input("sin(sin(x+x^2))");
    auto sine_of_addition = lexy::zstring_input("sin(cos(x)+x^2)");
    auto polynomial = lexy::zstring_input("x^2+2x");

    EXPECT_TRUE(lexy::match<test::intermediate_function>(sine_of_sine));
    EXPECT_TRUE(lexy::match<test::intermediate_function>(sine_of_addition));
    EXPECT_TRUE(lexy::match<test::intermediate_function>(polynomial));
}

TEST(GrammarTest, IntermediateFunctionChain) {
    auto sine_of_sine = lexy::zstring_input("sin(sin(x+x^2))");
    auto sine_of_addition = lexy::zstring_input("sin(cos(x)+x^2)");
    auto addition = lexy::zstring_input("sin(sin(x+x^2))+sin(cos(x)+x^2)");
    auto subtract = lexy::zstring_input("sin(sin(x+x^2))-sin(cos(x)+x^2)");
    auto basic_functions_chain = lexy::zstring_input("sin(x+x^2)+sin(x+2x)");
    auto polynomial = lexy::zstring_input("x^2+2x");

    EXPECT_TRUE(lexy::match<test::intermediate_functions_chain>(sine_of_sine));
    EXPECT_TRUE(lexy::match<test::intermediate_functions_chain>(sine_of_addition));
    EXPECT_TRUE(lexy::match<test::intermediate_functions_chain>(addition));
    EXPECT_TRUE(lexy::match<test::intermediate_functions_chain>(subtract));
    EXPECT_TRUE(lexy::match<test::intermediate_functions_chain>(polynomial));
    EXPECT_TRUE(lexy::match<test::intermediate_functions_chain>(basic_functions_chain));
}

TEST(GrammarTest, AdvancedFunction) {
    auto sine_of_addition = lexy::zstring_input("sin(sin(sin(x+x^2))+sin(cos(x)+x^2))");
    auto cosine_of_subtraction = lexy::zstring_input("cos(sin(sin(x+x^2))-sin(cos(x)+x^2))");
    auto polynomial = lexy::zstring_input("x^2+2x");
    auto itermediate_function = lexy::zstring_input("sin(cos(x)+x^2)");;

    EXPECT_TRUE(lexy::match<test::advanced_function>(sine_of_addition));
    EXPECT_TRUE(lexy::match<test::advanced_function>(cosine_of_subtraction));
    EXPECT_TRUE(lexy::match<test::advanced_function>(polynomial));
    EXPECT_TRUE(lexy::match<test::advanced_function>(itermediate_function));
}

TEST(GrammarTest, AdvancedFunctionChain) {
    auto sine_cosine_addition =
            lexy::zstring_input("sin(sin(sin(x+x^2))+sin(cos(x)+x^2))+cos(sin(sin(x+x^2))-sin(cos(x)+x^2))");
    auto polynomial = lexy::zstring_input("x^2+2x");
    auto itermediate_function = lexy::zstring_input("sin(cos(x)+x^2)");
    auto intermediate_functions_chain = lexy::zstring_input("sin(sin(x+x^2))+sin(cos(x)+x^2)");
    auto atom = lexy::zstring_input("x");

    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(sine_cosine_addition));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(polynomial));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(itermediate_function));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(intermediate_functions_chain));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(atom));
}
