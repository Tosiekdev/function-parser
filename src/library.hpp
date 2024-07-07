#ifndef FUNCTION_PARSER_LIBRARY_HPP
#define FUNCTION_PARSER_LIBRARY_HPP

#include <lexy/dsl.hpp>

namespace az { namespace { namespace grammar {
    namespace dsl = lexy::dsl;

    struct production : lexy::expression_production {
        static constexpr auto whitespace = dsl::ascii::space;
        static constexpr auto atom= [] {
            auto integer= dsl::digits<>.no_leading_zero();
            auto fraction= dsl::digits<>;

            return integer >> dsl::if_(dsl::period >> fraction) | dsl::lit_c<'x'>;
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
