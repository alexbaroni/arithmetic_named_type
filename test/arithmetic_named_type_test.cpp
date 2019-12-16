#include "catch.hpp"

#include <iterator>
#include "arithmetic_named_type/type_traits.hpp"
#include "arithmetic_named_type/arithmetic_named_type.hpp"

using namespace type_util;

TEST_CASE("Arithmetic named type use") {
  using num_value = arithmetic_named_type<std::size_t, struct num_value_tag,
      pre_incrementable,
      comparable,
      orderable>;

  SECTION("default construction") {
    auto num = num_value{};
    REQUIRE(num == 0);
  }
  SECTION("construction") {
    auto num = num_value{1u};
    REQUIRE(num == 1u);
  }
  SECTION("copy construction") {
    auto num = num_value{1u};
    auto num2 = num;
    REQUIRE(num2 == 1u);
  }
  SECTION("assignment") {
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    num = num2;
    REQUIRE((num == num2 && num == 2));
  }
  SECTION("swap") {
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    std::swap(num, num2);
    REQUIRE((num == 2 && num2 == 1));
  }
  SECTION("equivalence") {
    static_assert(has_equivalence_v<num_value, num_value>);
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    auto num3 = num_value{2u};
    REQUIRE(num2 == num3);
    REQUIRE(2 == num3);
    REQUIRE(num3 == 2);
    REQUIRE(num != num2);
  }

  SECTION("ordering") {
    static_assert(has_ordering_v<num_value, num_value>);
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    REQUIRE(num < num2);
    REQUIRE(num2 > num);
    REQUIRE(num2 >= num);
    REQUIRE(num <= num2);
  }

  SECTION("pre increment") {
    static_assert(has_pre_increment_v<num_value>);
    auto num = num_value{1u};
    ++num;
    REQUIRE(num == 2);
  }
}

