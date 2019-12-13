#include "catch.hpp"

#include <iterator>
#include <iostream>
#include "arithmetic_named_type/arithmetic_named_type.hpp"

TEST_CASE("Arithmetic named type use") {
  SECTION("construction") {
    using num_value = arithmetic_named_type<std::size_t, struct num_value_tag>;
  }
}

