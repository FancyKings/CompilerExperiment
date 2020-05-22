cmake_minimum_required(VERSION 3.15)
project(CompilerExperiment)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilerExperiment lexical_analysis/main.cpp lexical_analysis/main.hpp lexical_analysis/scanner.cpp lexical_analysis/scanner.hpp)
