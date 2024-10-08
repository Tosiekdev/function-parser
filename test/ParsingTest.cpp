#include <az_math/function_parser.hpp>
#include <gtest/gtest.h>

#include "lexy/dsl.hpp"
#include "lexy_ext/report_error.hpp"

TEST(ParsingTest, ParseNumber) {
    auto integerResult = az::parse_expression("5");
    auto decimalResult = az::parse_expression("3.14");
    ASSERT_TRUE(integerResult);
    EXPECT_DOUBLE_EQ(integerResult->evaluate(0), 5.0);
    ASSERT_TRUE(decimalResult);
    EXPECT_DOUBLE_EQ(decimalResult->evaluate(0), 3.14);
}

TEST(ParsingTest, ParseX) {
    auto result = az::parse_expression("x");
    ASSERT_TRUE(result);
    EXPECT_DOUBLE_EQ(result->evaluate(3.14), 3.14);
}

TEST(ParsingTest, Functions) {
    auto sin = az::parse_expression("sin(x)");
    auto cos = az::parse_expression("cos(x)");
    auto tan = az::parse_expression("tan(x)");
    auto cot = az::parse_expression("cot(x)");
    auto sqrt = az::parse_expression("sqrt(x)");
    auto cbrt = az::parse_expression("cbrt(x)");
    auto ln = az::parse_expression("ln(x)");
    auto lg = az::parse_expression("lg(x)");
    auto log = az::parse_expression("log(x)");
    auto arcsin = az::parse_expression("arcsin(x)");
    auto arccos = az::parse_expression("arccos(x)");
    auto arctan = az::parse_expression("arctan(x)");
    ASSERT_TRUE(sin);
    EXPECT_DOUBLE_EQ(sin->evaluate(3.14), std::sin(3.14));
    ASSERT_TRUE(cos);
    EXPECT_DOUBLE_EQ(cos->evaluate(3.14), std::cos(3.14));
    ASSERT_TRUE(tan);
    EXPECT_DOUBLE_EQ(tan->evaluate(3.14), std::tan(3.14));
    ASSERT_TRUE(cot);
    EXPECT_DOUBLE_EQ(cot->evaluate(3.14), std::cos(3.14) / std::sin(3.14));
    ASSERT_TRUE(sqrt);
    EXPECT_DOUBLE_EQ(sqrt->evaluate(3.14), std::sqrt(3.14));
    ASSERT_TRUE(cbrt);
    EXPECT_DOUBLE_EQ(cbrt->evaluate(3.14), std::cbrt(3.14));
    ASSERT_TRUE(ln);
    EXPECT_DOUBLE_EQ(ln->evaluate(3.14), std::log(3.14));
    ASSERT_TRUE(lg);
    EXPECT_DOUBLE_EQ(lg->evaluate(3.14), std::log2(3.14));
    ASSERT_TRUE(log);
    EXPECT_DOUBLE_EQ(log->evaluate(3.14), std::log10(3.14));
    ASSERT_TRUE(arcsin);
    EXPECT_DOUBLE_EQ(arcsin->evaluate(0.14), std::asin(0.14));
    ASSERT_TRUE(arccos);
    EXPECT_DOUBLE_EQ(arccos->evaluate(0.14), std::acos(0.14));
    ASSERT_TRUE(arctan);
    EXPECT_DOUBLE_EQ(arctan->evaluate(3.14), std::atan(3.14));
}

TEST(ParsingTest, Exponentitation) {
    auto result = az::parse_expression("x^5");
    auto result2 = az::parse_expression("x^5^5");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->evaluate(3.14), std::pow(3.14, 5));
    ASSERT_TRUE(result2);
    EXPECT_EQ(result2->evaluate(3.14), std::pow(3.14, std::pow(5, 5)));
}

TEST(ParsingTest, Multiplication) {
    auto result = az::parse_expression("x*5");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->evaluate(3.14), 3.14 * 5);
}

TEST(ParsingTest, Division) {
    auto result = az::parse_expression("x/5");
    auto result2 = az::parse_expression("x/5/5");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->evaluate(3.14), 3.14 / 5);
    ASSERT_TRUE(result2);
    EXPECT_EQ(result2->evaluate(3.14), 3.14 / 5 / 5);
}

TEST(ParsingTest, Addition) {
    auto result = az::parse_expression("x+5");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->evaluate(3.14), 3.14 + 5);
}

TEST(ParsingTest, Subtraction) {
    auto result = az::parse_expression("x-5");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->evaluate(3.14), 3.14 - 5);
}

TEST(ParsingTest, OperatorPrecedence) {
    auto result = az::parse_expression("(2+5)*2+3*5^2");
    auto result2 = az::parse_expression("(2+x)*2+3*x^x");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->evaluate(3.14), (2+5)*2+3*std::pow(5,2));
    ASSERT_TRUE(result2);
    EXPECT_EQ(result2->evaluate(3.14), (2+3.14)*2+3*std::pow(3.14,3.14));
}

TEST(ParsingTest, InvalidFunction) {
    auto result = az::parse_expression("2x");
    ASSERT_FALSE(result);
}
