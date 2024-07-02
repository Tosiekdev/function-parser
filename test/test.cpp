//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include "../src/library.hpp"

#define WRAP(x) struct x {static constexpr auto rule = lexy::dsl::p<az::grammar::x> >> lexy::dsl::eof;}

namespace test{
    WRAP(number);
    WRAP(addition);
    WRAP(atom);
    WRAP(polynomial);
    WRAP(basic_function);
    WRAP(basic_functions_chain);
    WRAP(intermediate_function);
    WRAP(intermediate_functions_chain);
    WRAP(advanced_function);
    WRAP(advanced_functions_chain);
    WRAP(fun_of_advanced_functions_chain);
    WRAP(expression);
}

TEST(GrammarTest, Number) {
    auto number = lexy::zstring_input("5");
    auto fraction = lexy::zstring_input("5.2");
    auto zero = lexy::zstring_input("0");
    auto notWhole = lexy::zstring_input("0.2566");
    auto big = lexy::zstring_input("3546532.37264572");

    EXPECT_EQ(lexy::match<test::number>(number), true);
    EXPECT_EQ(lexy::match<test::number>(fraction), true);
    EXPECT_EQ(lexy::match<test::number>(zero), true);
    EXPECT_EQ(lexy::match<test::number>(notWhole), true);
    EXPECT_EQ(lexy::match<test::number>(big), true);
}

TEST(GrammarTest, Addition) {
    auto number = lexy::zstring_input("5");
    auto x = lexy::zstring_input("x");
    auto sumOfNumbers = lexy::zstring_input("3.24+5");
    auto sumOfXs = lexy::zstring_input("x+x+x");
    auto sum = lexy::zstring_input("x+5.223+x+4+0+x+x");

    EXPECT_EQ(lexy::match<test::addition>(number), true);
    EXPECT_EQ(lexy::match<test::addition>(x), true);
    EXPECT_EQ(lexy::match<test::addition>(sumOfNumbers), true);
    EXPECT_EQ(lexy::match<test::addition>(sumOfXs), true);
    EXPECT_EQ(lexy::match<test::addition>(sum), true);
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
    auto polynomial = lexy::zstring_input("x");
    auto sine = lexy::zstring_input("sin(x+x^2)");
    auto faulty_sine = lexy::zstring_input("sin(x+x2)");

    EXPECT_TRUE(lexy::match<test::basic_function>(polynomial));
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
    auto sine_cosine_addition_faulty =
            lexy::zstring_input("sin(sin(sin(x+x^2))+sin(cos(x)+x^2))+cos(sin(sin(x+x^2))-sin(cos(x)+x^2)");
    auto polynomial = lexy::zstring_input("x^2+2x");
    auto itermediate_function = lexy::zstring_input("sin(cos(x)+x^2)");
    auto intermediate_functions_chain = lexy::zstring_input("sin(sin(x+x^2))+sin(cos(x)+x^2)");
    auto atom = lexy::zstring_input("x");
    auto mix =
            lexy::zstring_input("sin(sin(sin(x+x^2))+sin(cos(x)+x^2))+cos(sin(sin(x+x^2))-sin(cos(x)+x^2))+x");

    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(sine_cosine_addition));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(polynomial));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(itermediate_function));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(intermediate_functions_chain));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(atom));
    EXPECT_TRUE(lexy::match<test::advanced_functions_chain>(mix));

    EXPECT_FALSE(lexy::match<test::advanced_functions_chain>(sine_cosine_addition_faulty));
}

TEST(GrammarTest, FunOfAdvancedFunctionsChain) {
    auto sine_of_mix =
            lexy::zstring_input("sin(sin(sin(sin(x+x^2))+sin(cos(x)+x^2))+cos(sin(sin(x+x^2))-sin(cos(x)+x^2))+x)");

    EXPECT_TRUE(lexy::match<test::fun_of_advanced_functions_chain>(sine_of_mix));
}
