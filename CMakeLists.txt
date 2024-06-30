cmake_minimum_required(VERSION 3.22)
project(better_lexer)

set(CMAKE_CXX_STANDARD 17)

add_executable(better_lexer main.cpp
        headers/lexer.h
        sources/lexer.cpp
        headers/error.h
        sources/error.cpp)
