#include "catch.hpp"

#include <iterator>
#include "arithmetic_named_type/type_traits.hpp"
#include "arithmetic_named_type/arithmetic_named_type.hpp"

using namespace type_util;

using num_value = arithmetic_named_type<std::size_t, struct num_value_tag,
    incrementable,
    decrementable,
    comparable,
    orderable,
    addable>;

using num_value_s = arithmetic_named_type<long, struct num_value_s_tag,
    comparable,
    orderable,
    subtractable,
    multiplicable>;

TEST_CASE("Arithmetic named type use") {

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

  SECTION("post increment") {
    static_assert(has_post_increment_v<num_value>);
    auto num = num_value{1u};
    num++;
    REQUIRE(num == 2);
  }

  SECTION("pre decrement") {
    static_assert(has_pre_decrement_v<num_value>);
    auto num = num_value{1u};
    --num;
    REQUIRE(num == 0);
  }

  SECTION("post decrement") {
    static_assert(has_post_decrement_v<num_value>);
    auto num = num_value{1u};
    num--;
    REQUIRE(num == 0);
  }

  SECTION("addition") {
    static_assert(has_addition_v<num_value, num_value>);
    static_assert(has_addition_v<num_value, unsigned>);
    static_assert(is_narrowing_conversion_v<int, unsigned long long>);
    static_assert(is_narrowing_conversion_v<unsigned long long, unsigned>);
    static_assert(is_narrowing_conversion_v<unsigned long long, int>);
    static_assert(!is_narrowing_conversion_v<unsigned, unsigned long long>);
    static_assert(!is_narrowing_conversion_v<unsigned, unsigned>);
    static_assert(!is_narrowing_conversion_v<int, int>);
    static_assert(is_narrowing_conversion_v<long long, unsigned long long>);
    static_assert(is_narrowing_conversion_v<int, double>);
    static_assert(is_narrowing_conversion_v<double, int>);
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    num2 += num;
    REQUIRE(num2 == 3);
    num += 3l;
    REQUIRE(num == 4);
    auto num3 = num + num2;
    REQUIRE(num3 == 7);
    auto num4 = num + 2;
    REQUIRE(num4 == 6);
    auto num5 = 2 + num;
    REQUIRE(num5 == 6);
  }

  SECTION("subtraction") {
    static_assert(has_subtraction_v<num_value_s, num_value_s>);
    static_assert(has_subtraction_v<num_value_s, int>);

    auto num = num_value_s{2};
    auto num2 = num_value_s{1};
    num2 -= num;
    REQUIRE(num2 == -1);
    num -= 3;
    REQUIRE(num == -1);
    auto num3 = num - num2;
    REQUIRE(num3 == 0);
    auto num4 = num - 2;
    REQUIRE(num4 == -3);
    auto num5 = 2 - num;
    REQUIRE(num5 == 3);
  }

  SECTION("multiplication") {
    static_assert(has_multiplication_v<num_value_s, num_value_s>);
    static_assert(has_multiplication_v<num_value_s, int>);
    auto num = num_value_s{2};
    auto num2 = num_value_s{1};
    num2 *= num;
    REQUIRE(num2 == 2);
    num *= -3;
    REQUIRE(num == -6);
    auto num3 = num * num2;
    REQUIRE(num3 == -12);
    auto num4 = num * -2;
    REQUIRE(num4 == 12);
    auto num5 = -2 * num;
    REQUIRE(num5 == 12);
  }
}

