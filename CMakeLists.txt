cmake_minimum_required(VERSION 3.12)
project(ex3_cpp)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS -Wall -Wextra -pthread -g)

add_executable(exceptionTesterEx3.cpp Matrix.hpp Complex.cpp exceptionTesterEx3.cpp)