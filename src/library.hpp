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
        }
    }

    int hello() {
        return 4;
    }
}

#endif //FUNCTION_PARSER_LIBRARY_HPP
