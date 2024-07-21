#ifndef FUNCTION_PARSER_LIBRARY_HPP
#define FUNCTION_PARSER_LIBRARY_HPP

#include <lexy/dsl.hpp>
#include <lexy/callback.hpp>
#include <lexy/token.hpp>

#include <cmath>
#include <utility>

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
        X()=default;
        [[nodiscard]] double evaluate(double x) override {
            return x;
        }
    };

    struct Sin : Production {
        explicit Sin(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sin(prod->evaluate(x));
        }
    };

    struct Cos : Production {
        explicit Cos(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cos(prod->evaluate(x));
        }
    };

    struct Tan : Production {
        explicit Tan(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::tan(prod->evaluate(x));
        }
    };

    struct Cot : Production {
        explicit Cot(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cos(prod->evaluate(x)) / std::sin(prod->evaluate(x));
        }
    };

    struct Sqrt : Production {
        explicit Sqrt(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::sqrt(prod->evaluate(x));
        }
    };

    struct Cbrt : Production {
        explicit Cbrt(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return std::cbrt(prod->evaluate(x));
        }
    };

    struct Negative : Production {
        explicit Negative(std::shared_ptr<Production> p) : prod(std::move(p)){};
        std::shared_ptr<Production> prod;

        [[nodiscard]] double evaluate(double x) override {
            return -prod->evaluate(x);
        }
    };

    struct Pow : Production {
        explicit Pow(std::shared_ptr<Production> l, std::shared_ptr<Production> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return std::pow(lhs->evaluate(x), rhs->evaluate(x));
        }
    };

    struct Mul : Production {
        explicit Mul(std::shared_ptr<Production> l, std::shared_ptr<Production> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) * rhs->evaluate(x);
        }
    };

    struct Div : Production {
        explicit Div(std::shared_ptr<Production> l, std::shared_ptr<Production> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) / rhs->evaluate(x);
        }
    };

    struct Plus : Production {
        explicit Plus(std::shared_ptr<Production> l, std::shared_ptr<Production> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
        std::shared_ptr<Production> lhs;
        std::shared_ptr<Production> rhs;

        [[nodiscard]] double evaluate(double x) override {
            return lhs->evaluate(x) + rhs->evaluate(x);
        }
    };

    struct Minus : Production {
        explicit Minus(std::shared_ptr<Production> l, std::shared_ptr<Production> r)
                        : lhs(std::move(l)), rhs(std::move(r)){};
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

        static constexpr auto value =
                lexy::callback<std::shared_ptr<Number>>([](std::string i, std::optional<std::string> f){
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
    auto callback = [](std::shared_ptr<Production> p){ return std::make_shared<T>(p); };

    template<typename Op, typename T>
    auto binOperatorCallback =
            [](const std::shared_ptr<Production>& l, Op, const std::shared_ptr<Production>& r){
                return std::make_shared<T>(l, r);
            };

    constexpr auto op_plus  = dsl::op(dsl::lit_c<'+'>);
    constexpr auto op_minus = dsl::op(dsl::lit_c<'-'>);
    constexpr auto op_mul  = dsl::op(dsl::lit_c<'*'>);
    constexpr auto op_div = dsl::op(dsl::lit_c<'/'>);
    constexpr auto op_pow  = dsl::op(dsl::lit_c<'^'>);
    struct production : lexy::expression_production {
        struct sin {
            static constexpr auto rule = dsl::lit<"sin"> >> dsl::parenthesized(dsl::p<production>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Sin>>(callback<Sin>);
        };

        struct cos {
            static constexpr auto rule = dsl::lit<"cos"> >> dsl::parenthesized(dsl::p<production>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Cos>>(callback<Cos>);
        };

        struct tan {
            static constexpr auto rule = dsl::lit<"tan"> >> dsl::parenthesized(dsl::p<production>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Tan>>(callback<Tan>);
        };

        struct cot {
            static constexpr auto rule = dsl::lit<"cot"> >> dsl::parenthesized(dsl::p<production>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Cot>>(callback<Cot>);
        };

        struct sqrt {
            static constexpr auto rule = dsl::lit<"sqrt"> >> dsl::parenthesized(dsl::p<production>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Sqrt>>(callback<Sqrt>);
        };

        struct cbrt {
            static constexpr auto rule = dsl::lit<"cbrt"> >> dsl::parenthesized(dsl::p<production>);
            static constexpr auto value = lexy::callback<std::shared_ptr<Cbrt>>(callback<Cbrt>);
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
        static constexpr auto value = lexy::callback<std::shared_ptr<Production>>(
                [](std::shared_ptr<Number> e) {return e;},
                [](std::shared_ptr<X> e) {return e;},
                [](std::shared_ptr<Sin> e) {return e;},
                [](std::shared_ptr<Cos> e) {return e;},
                [](std::shared_ptr<Tan> e) {return e;},
                [](std::shared_ptr<Cot> e) {return e;},
                [](std::shared_ptr<Sqrt> e) {return e;},
                [](std::shared_ptr<Cbrt> e) {return e;},
                [](lexy::op<op_minus>, const std::shared_ptr<Production>& e) {
                    return std::make_shared<Negative>(e);
                    },
                binOperatorCallback<lexy::op<op_pow>, Pow>,
                binOperatorCallback<lexy::op<op_mul>, Mul>,
                binOperatorCallback<lexy::op<op_div>, Div>,
                binOperatorCallback<lexy::op<op_plus>, Plus>,
                binOperatorCallback<lexy::op<op_minus>, Minus>);
    };
}}} // namespace az::<anonymous>::grammar

#endif //FUNCTION_PARSER_LIBRARY_HPP
