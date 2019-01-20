cmake_minimum_required(VERSION 3.12)
project(ex3_cpp)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS -Wall -Wextra -pthread -g)

add_executable(TimeChecker.cpp Matrix.hpp Complex.cpp TimeChecker.cpp)