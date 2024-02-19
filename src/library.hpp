#ifndef FUNCTION_PARSER_LIBRARY_HPP
#define FUNCTION_PARSER_LIBRARY_HPP

#include <lexy/dsl.hpp>

/*
 * FUNCTION -> OPERATION | (OPERATION)
 * OPERATION -> ADDITION | MULTIPLICATION | DIVISION | EXPONENTIATION | ONE_ARG
 * ADDITION -> 
 * */

namespace az {
    namespace {
        namespace grammar {
            namespace dsl = lexy::dsl;
            struct sine {
                static constexpr auto rule = dsl::lit<"sin">;
            };

            struct cosine {
                static constexpr auto rule = dsl::lit<"cos">;
            };

            struct tangens {
                static constexpr auto rule = dsl::lit<"tan">;
            };

            struct cotangens {
                static constexpr auto rule = dsl::lit<"cot">;
            };

            struct square_root {
                static constexpr auto rule = dsl::lit<"sqrt">;
            };

            struct cube_root {
                static constexpr auto rule = dsl::lit<"cbrt">;
            };

            struct function_kw {
                static constexpr auto rule = dsl::p<sine> | dsl::p<cosine>
                        | dsl::p<tangens> | dsl::p<cotangens>
                        | dsl::p<square_root> | dsl::p<cube_root>;
            };

            struct argument_function {
                static constexpr auto rule = dsl::p<function_kw> + dsl::lit<"("> + dsl::lit<")">;
            };

            struct number {
                static constexpr auto rule = [] {
                    auto integer  = dsl::digits<>.no_leading_zero();
                    auto fraction = dsl::digits<>;

                    return integer + dsl::if_(dsl::period >> fraction);
                }();
            };

            struct atom {
                static constexpr auto rule = dsl::try_(dsl::p<number>) + dsl::lit<"x"> + dsl::opt(dsl::lit_c<'^'> >> dsl::p<number>);
            };

            struct polynomial {
                static constexpr auto rule = dsl::p<atom> + dsl::while_(dsl::lit_c<'+'> >> dsl::p<atom>);
            };

            struct expression {
                static constexpr auto rule = dsl::p<atom>;
            };
        }
    }

    int hello() {
        return 4;
    }
}

#endif //FUNCTION_PARSER_LIBRARY_HPP
