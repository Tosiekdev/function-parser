#ifndef FUNCTION_PARSER_LIBRARY_HPP
#define FUNCTION_PARSER_LIBRARY_HPP

#include <lexy/dsl.hpp>
#include <lexy/callback.hpp>

namespace az { namespace { namespace grammar {
    namespace dsl = lexy::dsl;

    struct Number {
        Number(const std::string& i, const std::optional<std::string>& f) :
            value(f ? std::stod(i+"."+*f) : std::stod(i)) {}
        double value;
    };

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

    struct production : lexy::expression_production {
        static constexpr auto whitespace = dsl::ascii::space;
        static constexpr auto atom= [] {
            auto integer= dsl::digits<>.no_leading_zero();
            auto fraction= dsl::digits<>;
            auto functionKw = dsl::lit<"sin">
                    | dsl::lit<"cos"> | dsl::lit<"tan"> | dsl::lit<"cot"> | dsl::lit<"sqrt"> | dsl::lit<"cbrt">;
            return functionKw >> dsl::parenthesized(dsl::recurse<production>) | integer >> dsl::if_(dsl::period >> fraction) | dsl::lit_c<'x'>;
        }();

        struct power : dsl::infix_op_left {
            static constexpr auto op = dsl::op(dsl::lit_c<'^'>);
            using operand = dsl::atom;
        };

        struct prefix : dsl::prefix_op {
            static constexpr auto op = dsl::op(dsl::lit_c<'-'>);
            using operand            = power;
        };

        struct product : dsl::infix_op_left {
            static constexpr auto op= dsl::op(dsl::lit_c<'*'>) / dsl::op(dsl::lit_c<'/'>);
            using operand = prefix;
        };

        struct sum : dsl::infix_op_left {
            static constexpr auto op= dsl::op(dsl::lit_c<'+'>) / dsl::op(dsl::lit_c<'-'>);
            using operand = product;
        };

        using operation = sum;
    };
}}} // namespace az::<anonymous>::grammar

#endif //FUNCTION_PARSER_LIBRARY_HPP
