#ifndef ARITHMETIC_NAMED_TYPE_BITWISE_TYPE_TRAITS_HPP
#define ARITHMETIC_NAMED_TYPE_BITWISE_TYPE_TRAITS_HPP

#include <experimental/type_traits>

namespace type_util {

  template<typename T>
  using has_bitwise_not_t = decltype(~std::declval<T>());

  template<typename T>
  using has_bitwise_not = std::experimental::is_detected<has_bitwise_not_t, T>;

  template<typename T>
  constexpr bool has_bitwise_not_v = has_bitwise_not<T>::value;

  template<typename T>
  using has_bitwise_and_t = std::conjunction<
      decltype(std::declval<T>() &= std::declval<T>()),
      decltype(std::declval<T>() & std::declval<T>())>;

  template<typename T>
  using has_bitwise_and = std::experimental::is_detected<has_bitwise_and_t, T>;

  template<typename T>
  constexpr bool has_bitwise_and_v = has_bitwise_and<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_and_t = std::conjunction<
      decltype(std::declval<T>() &= std::declval<T>()),
      decltype(std::declval<T>() &= std::declval<U>()),
      decltype(std::declval<T>() & std::declval<U>()),
      decltype(std::declval<U>() & std::declval<T>()),
      decltype(std::declval<T>() & std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_and = std::experimental::is_detected<has_mixed_mode_and_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_and_v = has_mixed_mode_and<T, U>::value;

  template<typename T>
  using has_bitwise_or_t = std::conjunction<
      decltype(std::declval<T>() |= std::declval<T>()),
      decltype(std::declval<T>() | std::declval<T>())>;

  template<typename T>
  using has_bitwise_or = std::experimental::is_detected<has_bitwise_or_t, T>;

  template<typename T>
  constexpr bool has_bitwise_or_v = has_bitwise_or<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_or_t = std::conjunction<
      decltype(std::declval<T>() |= std::declval<T>()),
      decltype(std::declval<T>() |= std::declval<U>()),
      decltype(std::declval<T>() | std::declval<U>()),
      decltype(std::declval<U>() | std::declval<T>()),
      decltype(std::declval<T>() | std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_or = std::experimental::is_detected<has_mixed_mode_or_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_or_v = has_mixed_mode_or<T, U>::value;

  template<typename T>
  using has_bitwise_xor_t = std::conjunction<
      decltype(std::declval<T>() ^= std::declval<T>()),
      decltype(std::declval<T>() ^ std::declval<T>())>;

  template<typename T>
  using has_bitwise_xor = std::experimental::is_detected<has_bitwise_xor_t, T>;

  template<typename T>
  constexpr bool has_bitwise_xor_v = has_bitwise_xor<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_xor_t = std::conjunction<
      decltype(std::declval<T>() ^= std::declval<T>()),
      decltype(std::declval<T>() ^= std::declval<U>()),
      decltype(std::declval<T>() ^ std::declval<U>()),
      decltype(std::declval<U>() ^ std::declval<T>()),
      decltype(std::declval<T>() ^ std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_xor = std::experimental::is_detected<has_mixed_mode_xor_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_xor_v = has_mixed_mode_xor<T, U>::value;

  template<typename T>
  using has_bitwise_left_shift_t = std::conjunction<
      decltype(std::declval<T>() <<= std::declval<T>()),
      decltype(std::declval<T>() << std::declval<T>())>;

  template<typename T>
  using has_bitwise_left_shift = std::experimental::is_detected<has_bitwise_left_shift_t, T>;

  template<typename T>
  constexpr bool has_bitwise_left_shift_v = has_bitwise_left_shift<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_bitwise_left_shift_t = std::conjunction<
      decltype(std::declval<T>() <<= std::declval<T>()),
      decltype(std::declval<T>() <<= std::declval<U>()),
      decltype(std::declval<T>() << std::declval<U>())/*,
      decltype(std::declval<U>() << std::declval<T>())*/,
      decltype(std::declval<T>() << std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_bitwise_left_shift = std::experimental::is_detected<has_mixed_mode_bitwise_left_shift_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_bitwise_left_shift_v = has_mixed_mode_bitwise_left_shift<T, U>::value;

  template<typename T>
  using has_bitwise_right_shift_t = std::conjunction<
      decltype(std::declval<T>() >>= std::declval<T>()),
      decltype(std::declval<T>() >> std::declval<T>())>;

  template<typename T>
  using has_bitwise_right_shift = std::experimental::is_detected<has_bitwise_right_shift_t, T>;

  template<typename T>
  constexpr bool has_bitwise_right_shift_v = has_bitwise_right_shift<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_bitwise_right_shift_t = std::conjunction<
      decltype(std::declval<T>() >>= std::declval<T>()),
      decltype(std::declval<T>() >>= std::declval<U>()),
      decltype(std::declval<T>() >> std::declval<U>())/*,
      decltype(std::declval<U>() >> std::declval<T>())*/,
      decltype(std::declval<T>() >> std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_bitwise_right_shift = std::experimental::is_detected<has_mixed_mode_bitwise_right_shift_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_bitwise_right_shift_v = has_mixed_mode_bitwise_right_shift<T, U>::value;
}
#endif //ARITHMETIC_NAMED_TYPE_BITWISE_TYPE_TRAITS_HPP
