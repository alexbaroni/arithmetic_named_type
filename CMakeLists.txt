cmake_minimum_required(VERSION 3.15)
project(arithmetic_named_type)

set(CMAKE_CXX_STANDARD 20)
add_compile_options("$<$<CONFIG:DEBUG>:-O0;-fno-inline;-g3;-fno-omit-frame-pointer;-fno-stack-protector;-mieee-fp>")
add_compile_options("$<$<CONFIG:RELEASE>:-O3;-g0;-DNDEBUG>")
add_compile_options("$<$<CONFIG:RELWITHDEBINFO>:-O2;-g;-DNDEBUG>")

set(ARITHMETIC_NAMED_TYPE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(arithmetic_named_type INTERFACE)
target_sources(arithmetic_named_type INTERFACE
        ${ARITHMETIC_NAMED_TYPE_INCLUDE_PATH}/arithmetic_named_type/arithmetic_named_type.hpp)
target_include_directories(arithmetic_named_type INTERFACE ${ARITHMETIC_NAMED_TYPE_INCLUDE_PATH})

enable_testing()
include(CTest)
add_subdirectory(test)