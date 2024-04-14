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

            struct tangent {
                static constexpr auto rule = dsl::lit<"tan">;
            };

            struct cotangent {
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
                                             | dsl::p<tangent> | dsl::p<cotangent>
                                             | dsl::p<square_root> | dsl::p<cube_root>;
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
        }
    }
}

#endif //FUNCTION_PARSER_LIBRARY_HPP
