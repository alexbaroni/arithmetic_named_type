#include <sstream>
#include "catch.hpp"

#include "arithmetic_named_type/type_traits.hpp"
#include "arithmetic_named_type/arithmetic_named_type.hpp"

using namespace type_util;

using num_value = arithmetic_named_type<std::size_t, struct num_value_tag,
    unary_plus,
    incrementable,
    decrementable,
    mixed_mode_comparable,
    mixed_mode_orderable,
    mixed_mode_addable,
    mixed_mode_and,
    mixed_mode_or,
    mixed_mode_xor,
    mixed_mode_bitwise_left_shift,
    mixed_mode_bitwise_right_shift>;

using num_value_s = arithmetic_named_type<long, struct num_value_s_tag,
    unary_minus,
    mixed_mode_comparable,
    mixed_mode_orderable,
    mixed_mode_subtractable,
    mixed_mode_multipliable,
    mixed_mode_divisible,
    bitwise_not,
    logical_not,
    implicitly_convertible_to<int>::conv_op,
    hashable>;

using num_value_nm = arithmetic_named_type<long, struct num_value_nm_tag,
    mixed_mode_comparable,
    mixed_mode_orderable,
    addable,
    subtractable,
    multipliable,
    divisible,
    bitwise_and,
    bitwise_or,
    bitwise_xor,
    bitwise_left_shift,
    bitwise_right_shift>;

using num_value_nmu = arithmetic_named_type<long, struct num_value_nmu_tag,
    comparable,
    orderable>;

using num_value_d = arithmetic_named_type<double, struct num_value_d_tag,
    mixed_mode_comparable,
    mixed_mode_orderable,
    mixed_mode_divisible>;

TEST_CASE("Arithmetic named type use") {
  SECTION("static assertion") {
    STATIC_REQUIRE(is_safe_conversion_v<int, unsigned long long>);
    STATIC_REQUIRE(!is_safe_conversion_v<int, unsigned>);
    STATIC_REQUIRE(!is_safe_conversion_v<unsigned, int>);
    STATIC_REQUIRE(is_safe_conversion_v<short, int>);
    STATIC_REQUIRE(!is_safe_conversion_v<int, short>);
    STATIC_REQUIRE(!is_safe_conversion_v<unsigned long long, unsigned>);
    STATIC_REQUIRE(!is_safe_conversion_v<unsigned long, unsigned>);
    STATIC_REQUIRE(!is_safe_conversion_v<unsigned long long, int>);
    STATIC_REQUIRE(is_safe_conversion_v<unsigned, unsigned long long>);
    STATIC_REQUIRE(is_safe_conversion_v<unsigned, unsigned long>);
    STATIC_REQUIRE(is_safe_conversion_v<unsigned, unsigned>);
    STATIC_REQUIRE(is_safe_conversion_v<int, int>);
    STATIC_REQUIRE(!is_safe_conversion_v<long long, unsigned long long>); //!!
    STATIC_REQUIRE(!is_safe_conversion_v<unsigned long long, long long>); //!!

    STATIC_REQUIRE(is_safe_conversion_v<int, double>);
    STATIC_REQUIRE(!is_safe_conversion_v<double, int>);

    STATIC_REQUIRE(is_safe_conversion_v<float, double>);
    STATIC_REQUIRE(!is_safe_conversion_v<double, float>);
    STATIC_REQUIRE(!is_safe_conversion_v<long double, double>);
    STATIC_REQUIRE(is_safe_conversion_v<double, long double>);

    STATIC_REQUIRE(!is_safe_conversion_v<bool, int>);
    STATIC_REQUIRE(!is_safe_conversion_v<int, bool>);


    STATIC_REQUIRE(is_safe_conversion_v<int, double>);
    STATIC_REQUIRE(!is_safe_conversion_v<double, int>);
    STATIC_REQUIRE(is_safe_conversion_v<double, double>);
  }

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
    STATIC_REQUIRE(has_equivalence_v<num_value_nmu>);
    auto num = num_value_nmu{1u};
    auto num2 = num_value_nmu{2u};
    auto num3 = num_value_nmu{2u};
    REQUIRE(num2 == num3);
    REQUIRE(num != num2);
  }

  SECTION("mixed mode equivalence") {
    STATIC_REQUIRE(has_mixed_mode_equivalence_v<num_value, num_value>);
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    auto num3 = num_value{2u};
    REQUIRE(num2 == num3);
    REQUIRE(2 == num3);
    REQUIRE(num3 == 2);
    REQUIRE(num != num2);
  }

  SECTION("unary plus") {
    static_assert(has_unary_plus_v<num_value>);
    auto num = num_value{1u};
    REQUIRE(+num == 1);
  }

  SECTION("unary minus") {
    STATIC_REQUIRE(has_unary_minus_v<num_value_s>);
    auto num = num_value_s{1};
    REQUIRE(-num == -1);
    REQUIRE(-(-num) == 1);
  }

  SECTION("ordering") {
    STATIC_REQUIRE(has_ordering_v<num_value_nmu>);
    auto num = num_value_nmu{1u};
    auto num2 = num_value_nmu{2u};
    REQUIRE(num < num2);
    REQUIRE(num2 > num);
    REQUIRE(num2 >= num);
    REQUIRE(num <= num2);
  }

  SECTION("mixed mode ordering") {
    STATIC_REQUIRE(has_mixed_mode_ordering_v<num_value, num_value>);
    auto num = num_value{1u};
    auto num2 = num_value{2u};
    REQUIRE(num < num2);
    REQUIRE(1 < num2);
    REQUIRE(num2 < 3);
    REQUIRE(num2 > num);
    REQUIRE(num2 > 1);
    REQUIRE(2 > num);
    REQUIRE(num2 >= num);
    REQUIRE(2 >= num);
    REQUIRE(num2 >= 1);
    REQUIRE(num <= num2);
    REQUIRE(num <= 1);
    REQUIRE(2 <= num2);
  }

  SECTION("pre increment") {
    STATIC_REQUIRE(has_pre_increment_v<num_value>);
    auto num = num_value{1u};
    ++num;
    REQUIRE(num == 2);
  }

  SECTION("post increment") {
    STATIC_REQUIRE(has_post_increment_v<num_value>);
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
    STATIC_REQUIRE(has_post_decrement_v<num_value>);
    auto num = num_value{1u};
    num--;
    REQUIRE(num == 0);
  }

  SECTION("addition") {
    STATIC_REQUIRE(has_addition_v<num_value_nm>);
    auto num = num_value_nm{1};
    auto num2 = num_value_nm{2};
    num2 += num;
    REQUIRE(num2 == 3);
    auto num3 = num + num2;
    REQUIRE(num3 == 4);
  }

  SECTION("mixed mode addition") {
    STATIC_REQUIRE(has_mixed_mode_addition_v<num_value, num_value>);

    auto num = num_value{1u};
    auto num2 = num_value{2u};
    num2 += num;
    REQUIRE(num2 == 3);
    num += 3;
    REQUIRE(num == 4);
    auto num3 = num + num2;
    REQUIRE(num3 == 7);
    auto num4 = num + 2;
    REQUIRE(num4 == 6);
    auto num5 = 2 + num;
    REQUIRE(num5 == 6);
  }

  SECTION("subtraction") {
    STATIC_REQUIRE(has_subtraction_v<num_value_nm>);

    auto num = num_value_nm{2};
    auto num2 = num_value_nm{1};
    num2 -= num;
    REQUIRE(num2 == -1);
    auto num3 = num - num2;
    REQUIRE(num3 == 3);
  }

  SECTION("mixed mode subtraction") {
    STATIC_REQUIRE(has_mixed_mode_subtraction_v<num_value_s, num_value_s>);
    STATIC_REQUIRE(has_mixed_mode_subtraction_v<num_value_s, int>);

    auto num = num_value_s{2};
    auto num2 = num_value_s{1};
    num2 -= num;
    REQUIRE(num2 == -1);
    num -= 3l;
    REQUIRE(num == -1);
    auto num3 = num - num2;
    REQUIRE(num3 == 0);
    auto num4 = num - 2;
    REQUIRE(num4 == -3);
    auto num5 = 2l - num;
    REQUIRE(num5 == 3);
  }

  SECTION("multiplication") {
    STATIC_REQUIRE(has_multiplication_V<num_value_nm>);
    auto num = num_value_nm{2};
    auto num2 = num_value_nm{1};
    num2 *= num;
    REQUIRE(num2 == 2);
    auto num3 = num * num2;
    REQUIRE(num3 == 4);
  }

  SECTION("mixed mode multiplication") {
    STATIC_REQUIRE(has_mixed_mode_multiplication_v<num_value_s, num_value_s>);
    STATIC_REQUIRE(has_mixed_mode_multiplication_v<num_value_s, int>);
    auto num = num_value_s{2};
    auto num2 = num_value_s{1};
    num2 *= num;
    REQUIRE(num2 == 2);
    num *= -3l;
    REQUIRE(num == -6);
    auto num3 = num * num2;
    REQUIRE(num3 == -12);
    auto num4 = num * -2l;
    REQUIRE(num4 == 12);
    auto num5 = -2l * num;
    REQUIRE(num5 == 12);
  }

  SECTION("division") {
    STATIC_REQUIRE(has_division_v<num_value_nm>);
    auto num = num_value_nm{2};
    auto num2 = num_value_nm{4};
    num2 /= num;
    REQUIRE(num2 == 2);
    auto num3 = num2 / num2;
    REQUIRE(num3 == 1);
    auto num4 = num2 / num;
    REQUIRE(num4 == 1);
  }

  SECTION("modulus") {
    STATIC_REQUIRE(has_modulus_v<num_value_nm>);
    auto num = num_value_nm{5};
    auto num2 = num_value_nm{7};
    num2 %= num;
    REQUIRE(num2 == 2);
    auto num3 = num2 % num2;
    REQUIRE(num3 == 0);
    auto num4 = num % num2;
    REQUIRE(num4 == 1);
  }

  SECTION("mixed mode division") {
    STATIC_REQUIRE(has_mixed_mode_division_v<num_value_s, num_value_s>);
    STATIC_REQUIRE(has_mixed_mode_division_v<num_value_s, int>);
    auto num = num_value_s{4};
    auto num2 = num_value_s{32};
    num2 /= num;
    REQUIRE(num2 == 8);
    num /= -2l;
    REQUIRE(num == -2);
    auto num3 = num2 / num;
    REQUIRE(num3 == -4);
    auto num4 = num3 / -2l;
    REQUIRE(num4 == 2);
    auto num5 = -2l / num;
    REQUIRE(num5 == 1);
  }

  SECTION("mixed mode modulus") {
    using namespace Catch::literals;
    STATIC_REQUIRE(has_mixed_mode_modulus_v<num_value_s, num_value_s>);
    STATIC_REQUIRE(has_mixed_mode_modulus_v<num_value_s, int>);
    STATIC_REQUIRE(has_mixed_mode_modulus_v<num_value_d, double>);
    auto num = num_value_s{11};
    auto num2 = num_value_s{32};
    num2 %= num;
    REQUIRE(num2 == 10);
    num %= 3l;
    REQUIRE(num == 2);
    auto num3 = num2 % num;
    REQUIRE(num3 == 0);
    auto num4 = num2 % 2l;
    REQUIRE(num4 == 0);
    auto num5 = 21l % num;
    REQUIRE(num5 == 1);

    auto num6 = num_value_d{27.0};
    auto num7 = num6 % 7.0;
    REQUIRE(num7.get() == 6.0_a);
    num6 = num_value_d{-5.1};
    num6 %= 3.0;
    REQUIRE(num6.get() == -2.1_a);
    num6 = num_value_d{5.1};
    num6 %= -3.0;
    REQUIRE(num6.get() == 2.1_a);
    num6 = num_value_d{-5.1};
    num6 %= -3.0;
    REQUIRE(num6.get() == -2.1_a);
  }

  SECTION("bitwise not") {
    STATIC_REQUIRE(has_bitwise_not_v<num_value_s>);
    auto num = num_value_s{0};
    REQUIRE(~num == -1);
    REQUIRE(~(~num) == 0);
  }

  SECTION("bitwise and") {
    STATIC_REQUIRE(has_bitwise_and_v<num_value_nm>);
    auto num = num_value_nm{10};
    auto num2 = num_value_nm{2};
    num &= num2;
    REQUIRE(num == 2);
    auto num3 = num & num2;
    REQUIRE(num3 == 2);
  }

  SECTION("mixed mode bitwise and") {
    STATIC_REQUIRE(has_mixed_mode_and_v<num_value, num_value>);

    auto num = num_value{10u};
    auto num2 = num_value{2u};
    num &= num2;
    REQUIRE(num == 2);
    num &= 3;
    REQUIRE(num == 2);
    auto num3 = num & num2;
    REQUIRE(num3 == 2);
    auto num4 = num & 2;
    REQUIRE(num4 == 2);
    auto num5 = 2 & num;
    REQUIRE(num5 == 2);
  }

  SECTION("bitwise or") {
    STATIC_REQUIRE(has_bitwise_or_v<num_value_nm>);
    auto num = num_value_nm{9};
    auto num2 = num_value_nm{2};
    auto num4 = num_value_nm{4};
    num |= num2;
    REQUIRE(num == 11);
    auto num3 = num | num4;
    REQUIRE(num3 == 15);
  }

  SECTION("mixed mode bitwise or") {
    STATIC_REQUIRE(has_mixed_mode_or_v<num_value, num_value>);

    auto num = num_value{9u};
    auto num2 = num_value{2u};
    num |= num2;
    REQUIRE(num == 11);
    num |= 4;
    REQUIRE(num == 15);
    auto num3 = num | num2;
    REQUIRE(num3 == 15);
    auto num4 = num | 4;
    REQUIRE(num4 == 15);
    auto num5 = 4 | num;
    REQUIRE(num5 == 15);
  }

  SECTION("bitwise xor") {
    STATIC_REQUIRE(has_bitwise_xor_v<num_value_nm>);
    auto num = num_value_nm{9};
    auto num2 = num_value_nm{2};
    auto num4 = num_value_nm{4};
    num ^= num2;
    REQUIRE(num == 11);
    auto num3 = num ^ num4;
    REQUIRE(num3 == 15);
  }

  SECTION("mixed mode bitwise xor") {
    STATIC_REQUIRE(has_mixed_mode_xor_v<num_value, num_value>);

    auto num = num_value{9u};
    auto num2 = num_value{2u};
    num ^= num2;
    REQUIRE(num == 11);
    num ^= 4;
    REQUIRE(num == 15);
    auto num3 = num ^ num2;
    REQUIRE(num3 == 13);
    auto num4 = num ^ 4;
    REQUIRE(num4 == 11);
    auto num5 = 4 ^ num;
    REQUIRE(num5 == 11);
  }

  SECTION("bitwise left shift") {
    STATIC_REQUIRE(has_bitwise_left_shift_v<num_value_nm>);
    auto num = num_value_nm{9};
    auto num2 = num_value_nm{2};
    auto num4 = num_value_nm{4};
    num <<= num2;
    REQUIRE(num == 36);
    auto num3 = num2 << num4;
    REQUIRE(num3 == 32);
  }

  SECTION("mixed mode bitwise left shift") {
    STATIC_REQUIRE(has_mixed_mode_bitwise_left_shift_v<num_value, num_value>);

    auto num = num_value{9u};
    auto num2 = num_value{2u};
    auto num4 = num_value{1u};
    num <<= num2;
    REQUIRE(num == 36);
    num2 <<= 4;
    REQUIRE(num2 == 32);
    auto num3 = num << num4;
    REQUIRE(num3 == 72);
    auto num5 = num << 1;
    REQUIRE(num5 == 72);
  }

  SECTION("bitwise right shift") {
    STATIC_REQUIRE(has_bitwise_right_shift_v<num_value_nm>);
    auto num = num_value_nm{16};
    auto num2 = num_value_nm{2};
    auto num4 = num_value_nm{4};
    num >>= num2;
    REQUIRE(num == 4);
    auto num3 = num4 >> num2;
    REQUIRE(num3 == 1);
  }

  SECTION("mixed mode bitwise right shift") {
    STATIC_REQUIRE(has_mixed_mode_bitwise_right_shift_v<num_value, num_value>);

    auto num = num_value{32u};
    auto num2 = num_value{2u};
    auto num4 = num_value{1u};
    num >>= num2;
    REQUIRE(num == 8);
    num2 >>= 1;
    REQUIRE(num2 == 1);
    auto num3 = num >> num4;
    REQUIRE(num3 == 4);
    auto num5 = num >> 1;
    REQUIRE(num5 == 4);
  }

  SECTION("logical not") {
    STATIC_REQUIRE(has_logical_not_v<num_value_s>);
    auto num = num_value_s{0};
    REQUIRE(!num);
    REQUIRE_FALSE(!(!num));
  }

  SECTION("convertible to") {
    STATIC_REQUIRE(std::is_convertible_v<num_value_s, int>);
    auto add_one = [](int i) { return ++i; };
    auto num = num_value_s{22};
    REQUIRE(add_one(num) == 23);
  }

  SECTION("printable to") {
    std::ostringstream oss;
    auto num = num_value_s{22};
    STATIC_REQUIRE(std::is_convertible_v<num_value_s, long>);
    oss << num;
    REQUIRE(oss.str() == "22");
  }

  SECTION("hash")
  {
    std::unordered_map<num_value_s, int> hash_map = {
        {num_value_s{1}, 10},
        {num_value_s{2}, 20}
    };
    num_value_s cc3{3};
    hash_map[cc3] = 30;
    REQUIRE(hash_map[num_value_s{1}] == 10);
    REQUIRE(hash_map[num_value_s{2}] == 20);
    REQUIRE(hash_map[num_value_s{3}] == 30);
  }
}

