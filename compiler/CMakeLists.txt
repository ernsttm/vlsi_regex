cmake_minimum_required(VERSION 3.12)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(COMPILER_SRC src/compiler/Compiler.cpp
                 src/compiler/CompilerException.cpp
                 src/compiler/PatternCompiler.cpp
                 src/compiler/RepetitionCompiler.cpp
                 src/compiler/RootCompiler.cpp
                 src/compiler/WildcardCompiler.cpp)
set(PARSER_SRC src/parser/Codon.cpp
               src/parser/Parser.cpp
               src/parser/ParserException.cpp)
set(MAIN_SRC src/CompilerMain.cpp)
add_library(regex_compiler_lib ${COMPILER_SRC} ${PARSER_SRC})

add_executable(regex_compiler ${MAIN_SRC})
target_link_libraries(regex_compiler regex_compiler_lib)

set(COMPILER_TEST_SRC test/compiler/TestPatternCompiler.cpp)
set(INTEGRATION_TEST_SRC test/integration/IntegrationTest.cpp
                         test/integration/simple/TestSimplePattern.cpp
        test/integration/repetition/TestRepetition.cpp
                         test/integration/wildcard/TestWildcard.cpp)
set(PARSER_TEST_SRC test/parser/TestParser.cpp)
add_executable(regex_test ${COMPILER_TEST_SRC} ${INTEGRATION_TEST_SRC} ${PARSER_TEST_SRC})
target_link_libraries(regex_test regex_compiler_lib)
target_link_libraries(regex_test gtest)
target_link_libraries(regex_test gtest_main)
target_link_libraries(regex_test pthread)