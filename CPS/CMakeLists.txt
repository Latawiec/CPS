cmake_minimum_required (VERSION 2.6)
project (CPS)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-D_GLIBCXX_DEBUG -g")

include_directories(
    Base
    Generators
    Numeric
    Operations
    Interface
)

add_executable(CPS Source.cpp)