cmake_minimum_required(VERSION 3.12)
project(arithmetic_named_type_test)
set(CMAKE_CXX_STANDARD 20)

#configure directories
set(CATCH_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/catch2")

#include custom cmake function
include("${CATCH_INCLUDE_PATH}/ParseAndAddCatchTests.cmake")

add_library(catch2 INTERFACE)
target_sources(catch2 INTERFACE ${CATCH_INCLUDE_PATH}/catch.hpp)
target_include_directories(catch2 INTERFACE ${CATCH_INCLUDE_PATH})

enable_testing()

set(SOURCES_ARITHMETIC_NAMED_TYPE_MAIN arithmetic_named_type_main.cpp)
set(SOURCES_ARITHMETIC_NAMED_TYPE_TEST ${SOURCES_ARITHMETIC_NAMED_TYPE_MAIN} arithmetic_named_type_test.cpp)
set(SOURCES_ARITHMETIC_NAMED_TYPE_ALL_TEST ${SOURCES_ARITHMETIC_NAMED_TYPE_MAIN} arithmetic_named_type_test.cpp)


add_executable(test.arithmetic_named_type.arithmetic_named_type_test ${SOURCES_ARITHMETIC_NAMED_TYPE_TEST})
target_link_libraries(test.arithmetic_named_type.arithmetic_named_type_test INTERFACE mem_tracker INTERFACE catch2)
target_include_directories(test.arithmetic_named_type.arithmetic_named_type_test PRIVATE ${ARITHMETIC_NAMED_TYPE_INCLUDE_PATH} ${CATCH_INCLUDE_PATH})

add_executable(test.arithmetic_named_type.arithmetic_named_type.all_test ${SOURCES_ARITHMETIC_NAMED_TYPE_ALL_TEST})
target_link_libraries(test.arithmetic_named_type.arithmetic_named_type.all_test INTERFACE mem_tracker INTERFACE catch2)
target_include_directories(test.arithmetic_named_type.arithmetic_named_type.all_test PRIVATE ${ARITHMETIC_NAMED_TYPE_INCLUDE_PATH} ${CATCH_INCLUDE_PATH})

add_test(test.arithmetic_named_type.arithmetic_named_type_test test.arithmetic_named_type.arithmetic_named_type_test)
add_test(test.arithmetic_named_type.arithmetic_named_type_all_test test.arithmetic_named_type.arithmetic_named_type_all_test)
