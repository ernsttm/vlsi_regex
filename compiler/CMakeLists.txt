cmake_minimum_required(VERSION 3.12)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(COMPILER_SRC src/compiler/PatternCompiler.cpp
                 src/compiler/RootCompiler.cpp)
set(PARSER_SRC src/parser/Codon.cpp)
set(MAIN_SRC src/CompilerMain.cpp)
add_executable(regex_compiler ${MAIN_SRC} ${COMPILER_SRC} ${PARSER_SRC})