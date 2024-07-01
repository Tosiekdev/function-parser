#ifndef FUNCTION_PARSER_LIBRARY_HPP
#define FUNCTION_PARSER_LIBRARY_HPP

#include <lexy/dsl.hpp>

/*
 * sine -> "sin"
 * cosine -> "cos"
 * tangent -> "tan"
 * cotangent -> "cot"
 * square_root -> "sqrt"
 * cube_root -> "cbrt"
 * function_kw -> sine | cosine | tangent | cotangent | square_root | cube_root
 * number -> floating point bigger than 1 (for now - I just saw the bug)
 * atom -> number | number"x" | number"x^"number | "x" | "x^"number
 * polynomial -> atom | atom+polynomial | atom-polynomial
 * basic_function -> polynomial | function_kw"("polynomial")"
 * basic_function_chain -> basic_function | basic_function+basic_function_chain | basic_function+basic_function_chain
 * */

namespace az { namespace { namespace grammar {
    namespace dsl = lexy::dsl;
    struct sin {
        static constexpr auto rule = dsl::lit<"sin">;
    };

    struct cos {
        static constexpr auto rule = dsl::lit<"cos">;
    };

    struct tan {
        static constexpr auto rule = dsl::lit<"tan">;
    };

    struct cot {
        static constexpr auto rule = dsl::lit<"cot">;
    };

    struct sqrt {
        static constexpr auto rule = dsl::lit<"sqrt">;
    };

    struct cbrt {
        static constexpr auto rule = dsl::lit<"cbrt">;
    };

    struct function_kw {
        static constexpr auto rule = dsl::p<sin> | dsl::p<cos>
                | dsl::p<tan> | dsl::p<cot>
                | dsl::p<sqrt> | dsl::p<cbrt>;
    };

    struct number {
        static constexpr auto rule = [] {
            auto integer  = dsl::digits<>.no_leading_zero();
            auto fraction = dsl::digits<>;

            return integer >> dsl::if_(dsl::period >> fraction);
        }();
    };

    struct atom {
        static constexpr auto rule = []{
            auto with_number = dsl::p<number> >> dsl::opt(dsl::lit_c<'x'> >> dsl::opt(dsl::lit_c<'^'> >> dsl::p<number>));
            auto without_number = dsl::lit_c<'x'> >> dsl::opt(dsl::lit_c<'^'> >> dsl::p<number>);
            return with_number | without_number;
        }();
    };

    struct atom2 {
        static constexpr auto rule = dsl::lit_c<'x'>;
    };

    struct atomic {
        static constexpr auto rule = dsl::p<number> | dsl::p<atom2>;
    };

    struct addition {
        static constexpr auto rule =
                dsl::lit_c<'+'> >> dsl::p<atomic> >> dsl::recurse<addition> | dsl::eof;
    };

    struct addition_p {
        static constexpr auto rule = dsl::p<atomic> >> dsl::p<addition>;
    };


    struct polynomial {
        static constexpr auto rule =
                dsl::p<atom> >> dsl::while_(dsl::lit_c<'+'> >> dsl::p<atom> | dsl::lit_c<'-'> >> dsl::p<atom>);
    };

    struct basic_function {
        static constexpr auto rule =
                dsl::p<polynomial> |
                dsl::p<function_kw> >> dsl::lit<"("> >> dsl::p<polynomial> >> dsl::lit<")">;
    };

    struct basic_functions_chain {
        static constexpr auto rule =
                dsl::p<basic_function> >>
                dsl::while_(dsl::lit_c<'+'> >> dsl::p<basic_function>
                | dsl::lit_c<'-'> >> dsl::p<basic_function>);
    };

    struct intermediate_function {
        static constexpr auto rule =
                dsl::p<function_kw> >>
                dsl::lit<"("> >> dsl::p<basic_functions_chain> >> dsl::lit<")"> | dsl::p<basic_functions_chain>;
    };

    struct intermediate_functions_chain {
        static constexpr auto rule =
                dsl::p<intermediate_function> >>
                dsl::while_(dsl::lit_c<'+'> >> dsl::p<intermediate_function>
                | dsl::lit_c<'-'> >> dsl::p<intermediate_function>);
    };

    struct advanced_function {
        static constexpr auto rule =
                dsl::p<function_kw> >>
                dsl::lit<"("> >> dsl::p<intermediate_functions_chain> >> dsl::lit<")">
                | dsl::p<intermediate_functions_chain>;
    };

    struct advanced_functions_chain {
        static constexpr auto rule =
                dsl::p<advanced_function> >>
                dsl::while_(dsl::lit_c<'+'> >> dsl::p<advanced_function>
                | dsl::lit_c<'-'> >> dsl::p<advanced_function>);
    };

    struct fun_of_advanced_functions_chain {
        static constexpr auto rule =
                dsl::p<function_kw> >> dsl::lit<"("> >> dsl::p<advanced_functions_chain> >> dsl::lit<")">;
    };

    struct expression {
        static constexpr auto rule =
                dsl::p<advanced_functions_chain> | dsl::p<fun_of_advanced_functions_chain>;
    };

    struct function {
        static constexpr auto rule =
                dsl::p<expression> >>
                dsl::while_(dsl::lit_c<'+'> >> dsl::p<expression>
                | dsl::lit_c<'-'> >> dsl::p<expression>);
    };
}}} // namespace az::<anonymous>::grammar

#endif //FUNCTION_PARSER_LIBRARY_HPP
