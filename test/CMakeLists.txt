cmake_minimum_required(VERSION 3.29)
project(function-parser)
enable_testing()
add_executable(parser_test GrammarTest.cpp
        ParsingTest.cpp)
set_property(TARGET parser_test PROPERTY CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(lexy)
FetchContent_MakeAvailable(googletest)

target_link_libraries(parser_test GTest::gtest_main foonathan::lexy)
target_include_directories(parser_test PRIVATE ../include)
include(GoogleTest)
gtest_discover_tests(parser_test)
