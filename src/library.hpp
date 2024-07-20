#ifndef FUNCTION_PARSER_LIBRARY_HPP
#define FUNCTION_PARSER_LIBRARY_HPP

#include <lexy/dsl.hpp>
#include <lexy/callback.hpp>
#include <lexy/token.hpp>

#include <cmath>

namespace az {
    struct Production {
        [[nodiscard]] virtual double evaluate(double x) = 0;
    };

    struct Number : Production {
        Number(const std::string& i, const std::optional<std::string>& f) :
                value(f ? std::stod(i+"."+*f) : std::stod(i)) {}
        double value;

        [[nodiscard]] double evaluate(double x) override {
            return value;
        }
    };

    struct X : Production {
        [[nodiscard]] double evaluate(double x) override {
            return x;
        }
    };

    struct Sin : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sin(prod->evaluate(x));
        }
    };

    struct Cos : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cos(prod->evaluate(x));
        }
    };

    struct Tan : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::tan(prod->evaluate(x));
        }
    };

    struct Cot : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sin(prod->evaluate(x)) / std::sin(prod->evaluate(x));
        }
    };

    struct Sqrt : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sqrt(prod->evaluate(x));
        }
    };

    struct Cbrt : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cbrt(prod->evaluate(x));
        }
    };

    struct Negative : Production {
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return -prod->evaluate(x);
        }
    };

    struct Pow : Production {
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return std::pow(lhs->evaluate(x), rhs->evaluate(x));
        }
    };

    struct Mul : Production {
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) * rhs->evaluate(x);
        }
    };

    struct Div : Production {
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) / rhs->evaluate(x);
        }
    };

    struct Plus : Production {
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) + rhs->evaluate(x);
        }
    };

    struct Minus : Production {
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) - rhs->evaluate(x);
        }
    };

    namespace { namespace grammar {
    namespace dsl = lexy::dsl;

    struct number {
        struct integer {
            static constexpr auto rule = dsl::capture(dsl::digits<>.no_leading_zero());
            static constexpr auto value = lexy::as_string<std::string>;
        };

        struct fraction {
            static constexpr auto rule = dsl::capture(dsl::digits<>);
            static constexpr auto value = lexy::as_string<std::string>;
        };

        static constexpr auto rule = dsl::p<integer> >> dsl::opt(dsl::period >> dsl::p<fraction>);

        static constexpr auto value = lexy::construct<Number>;
    };

    struct x {
        static constexpr auto rule = dsl::lit_c<'x'>;
        static constexpr auto value = lexy::callback<X>([](){ return X{}; });
    };

    constexpr auto op_plus  = dsl::op(dsl::lit_c<'+'>);
    constexpr auto op_minus = dsl::op(dsl::lit_c<'-'>);
    constexpr auto op_mul  = dsl::op(dsl::lit_c<'*'>);
    constexpr auto op_div = dsl::op(dsl::lit_c<'/'>);
    constexpr auto op_pow  = dsl::op(dsl::lit_c<'^'>);
    struct production : lexy::expression_production {
        struct sin {
            static constexpr auto rule = dsl::lit<"sin"> >> dsl::parenthesized(dsl::p<production>);
        };

        struct cos {
            static constexpr auto rule = dsl::lit<"cos"> >> dsl::parenthesized(dsl::p<production>);
        };

        struct tan {
            static constexpr auto rule = dsl::lit<"tan"> >> dsl::parenthesized(dsl::p<production>);
        };

        struct cot {
            static constexpr auto rule = dsl::lit<"cot"> >> dsl::parenthesized(dsl::p<production>);
        };

        struct sqrt {
            static constexpr auto rule = dsl::lit<"sqrt"> >> dsl::parenthesized(dsl::p<production>);
        };

        struct cbrt {
            static constexpr auto rule = dsl::lit<"cbrt"> >> dsl::parenthesized(dsl::p<production>);
        };

        static constexpr auto whitespace = dsl::ascii::space;
        static constexpr auto atom= [] {
            auto function =
                    dsl::p<sin> | dsl::p<cos> | dsl::p<tan> | dsl::p<cot> | dsl::p<sqrt> | dsl::p<cbrt>;
            return function | dsl::p<number> | dsl::p<x>;
        }();

        struct power : dsl::infix_op_left {
            static constexpr auto op = op_pow;
            using operand = dsl::atom;
        };

        struct prefix : dsl::prefix_op {
            static constexpr auto op = dsl::op(dsl::lit_c<'-'>);
            using operand            = power;
        };

        struct product : dsl::infix_op_left {
            static constexpr auto op = op_mul / op_div;
            using operand = prefix;
        };

        struct sum : dsl::infix_op_left {
            static constexpr auto op= op_plus / op_minus;
            using operand = product;
        };

        using operation = sum;
    };
}}} // namespace az::<anonymous>::grammar

#endif //FUNCTION_PARSER_LIBRARY_HPP
