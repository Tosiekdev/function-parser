#ifndef FUNCTION_PARSER_FUNCTION_PARSER_HPP
#define FUNCTION_PARSER_FUNCTION_PARSER_HPP

#include <lexy/dsl.hpp>
#include <lexy/callback.hpp>
#include <lexy/token.hpp>

#include <cmath>
#include <utility>

namespace az {
    struct Expression {
        [[nodiscard]] virtual double evaluate(double x) = 0;
    };

    struct Number : Expression {
        Number(const std::string& i, const std::optional<std::string>& f) :
                value(f ? std::stod(i+"."+*f) : std::stod(i)) {}
        double value;

        [[nodiscard]] double evaluate(double x) override {
            return value;
        }
    };

    struct X : Expression {
        X()=default;
        [[nodiscard]] double evaluate(double x) override {
            return x;
        }
    };

    struct Sin : Expression {
        explicit Sin(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sin(prod->evaluate(x));
        }
    };

    struct Cos : Expression {
        explicit Cos(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cos(prod->evaluate(x));
        }
    };

    struct Tan : Expression {
        explicit Tan(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::tan(prod->evaluate(x));
        }
    };

    struct Cot : Expression {
        explicit Cot(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cos(prod->evaluate(x)) / std::sin(prod->evaluate(x));
        }
    };

    struct Sqrt : Expression {
        explicit Sqrt(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sqrt(prod->evaluate(x));
        }
    };

    struct Cbrt : Expression {
        explicit Cbrt(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cbrt(prod->evaluate(x));
        }
    };

    struct Negative : Expression {
        explicit Negative(std::shared_ptr<Expression> p) : prod(std::move(p)){};
        std::shared_ptr<Expression> prod;

        [[nodiscard]] double evaluate(double x) override {
            return -prod->evaluate(x);
        }
    };

    struct Pow : Expression {
        explicit Pow(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return std::pow(lhs->evaluate(x), rhs->evaluate(x));
        }
    };

    struct Mul : Expression {
        explicit Mul(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) * rhs->evaluate(x);
        }
    };

    struct Div : Expression {
        explicit Div(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) / rhs->evaluate(x);
        }
    };

    struct Plus : Expression {
        explicit Plus(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) + rhs->evaluate(x);
        }
    };

    struct Minus : Expression {
        explicit Minus(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Expression> lhs;
        std::shared_ptr<Expression> rhs;

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

        static constexpr auto value =
                lexy::callback<std::shared_ptr<Number>>(
                        [](const std::string& i, const std::optional<std::string>& f){
                            return std::make_shared<Number>(i, f);
                        });
    };

    struct x {
        static constexpr auto rule = dsl::lit_c<'x'>;
        static constexpr auto value = lexy::callback<std::shared_ptr<X>>([](){
            return std::make_shared<X>();
        });
    };

    template<typename T>
    auto callback = [](std::shared_ptr<Expression> p){ return std::make_shared<T>(p); };

    template<typename Op, typename T>
    auto binOperatorCallback =
            [](const std::shared_ptr<Expression>& l, Op, const std::shared_ptr<Expression>& r){
                return std::make_shared<T>(l, r);
            };

    template<typename T>
    auto forwardCallback = [](std::shared_ptr<T> e) { return e; };

    constexpr auto op_plus  = dsl::op(dsl::lit_c<'+'>);
    constexpr auto op_minus = dsl::op(dsl::lit_c<'-'>);
    constexpr auto op_mul  = dsl::op(dsl::lit_c<'*'>);
    constexpr auto op_div = dsl::op(dsl::lit_c<'/'>);
    constexpr auto op_pow  = dsl::op(dsl::lit_c<'^'>);
    struct expression : lexy::expression_production {
        struct sin {
            static constexpr auto rule = dsl::lit<"sin"> >> dsl::parenthesized(dsl::p<expression>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Sin>>(callback<Sin>);
        };

        struct cos {
            static constexpr auto rule = dsl::lit<"cos"> >> dsl::parenthesized(dsl::p<expression>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Cos>>(callback<Cos>);
        };

        struct tan {
            static constexpr auto rule = dsl::lit<"tan"> >> dsl::parenthesized(dsl::p<expression>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Tan>>(callback<Tan>);
        };

        struct cot {
            static constexpr auto rule = dsl::lit<"cot"> >> dsl::parenthesized(dsl::p<expression>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Cot>>(callback<Cot>);
        };

        struct sqrt {
            static constexpr auto rule = dsl::lit<"sqrt"> >> dsl::parenthesized(dsl::p<expression>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Sqrt>>(callback<Sqrt>);
        };

        struct cbrt {
            static constexpr auto rule = dsl::lit<"cbrt"> >> dsl::parenthesized(dsl::p<expression>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Cbrt>>(callback<Cbrt>);
        };

        static constexpr auto whitespace = dsl::ascii::space;
        static constexpr auto atom= [] {
            auto function =
                    dsl::p<sin> | dsl::p<cos> | dsl::p<tan> | dsl::p<cot> | dsl::p<sqrt> | dsl::p<cbrt>;
            return function | dsl::p<number> | dsl::p<x> | dsl::parenthesized(dsl::p<expression>);
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
        static constexpr auto value = lexy::callback<std::shared_ptr<Expression>>(
                forwardCallback<Number>,
                forwardCallback<X>,
                forwardCallback<Sin>,
                forwardCallback<Cos>,
                forwardCallback<Tan>,
                forwardCallback<Cot>,
                forwardCallback<Sqrt>,
                forwardCallback<Cbrt>,
                forwardCallback<Expression>,
                [](lexy::op<op_minus>, const std::shared_ptr<Expression>& e) {
                    return std::make_shared<Negative>(e);
                    },
                binOperatorCallback<lexy::op<op_pow>, Pow>,
                binOperatorCallback<lexy::op<op_mul>, Mul>,
                binOperatorCallback<lexy::op<op_div>, Div>,
                binOperatorCallback<lexy::op<op_plus>, Plus>,
                binOperatorCallback<lexy::op<op_minus>, Minus>);
    };
}}} // namespace az::<anonymous>::grammar

#endif //FUNCTION_PARSER_FUNCTION_PARSER_HPP
