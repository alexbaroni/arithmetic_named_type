#ifndef ARITHMETIC_NAMED_TYPE_ARITHMETIC_TYPE_TRAITS_HPP
#define ARITHMETIC_NAMED_TYPE_ARITHMETIC_TYPE_TRAITS_HPP

#include <experimental/type_traits>

namespace type_util {
  template<typename T>
  using unary_plus_t = decltype(+std::declval<T>());

  template<typename T>
  using has_unary_plus = std::experimental::is_detected<unary_plus_t, T>;

  template<typename T>
  constexpr bool has_unary_plus_v = has_unary_plus<T>::value;

  template<typename T>
  using unary_minus_t = decltype(-std::declval<T>());

  template<typename T>
  using has_unary_minus = std::experimental::is_detected<unary_minus_t, T>;

  template<typename T>
  constexpr bool has_unary_minus_v = has_unary_minus<T>::value;

  template<typename T>
  using pre_increment_t = decltype(++std::declval<T>());

  template<typename T>
  using has_pre_increment = std::experimental::is_detected<pre_increment_t, T>;

  template<typename T>
  constexpr bool has_pre_increment_v = has_pre_increment<T>::value;

  template<typename T>
  using post_increment_t = decltype(std::declval<T>()++);

  template<typename T>
  using has_post_increment = std::experimental::is_detected<post_increment_t, T>;

  template<typename T>
  constexpr bool has_post_increment_v = has_post_increment<T>::value;

  template<typename T>
  using has_increment_t = std::conjunction<
      decltype(++std::declval<T&>()),
      decltype(std::declval<T&>()++)>;

  template<typename T>
  using has_increment = std::experimental::is_detected<has_increment_t, T>;

  template<typename T>
  constexpr bool has_increment_v = has_increment<T>::value;

  template<typename T>
  using pre_decrement_t = decltype(--std::declval<T>());

  template<typename T>
  using has_pre_decrement = std::experimental::is_detected<pre_decrement_t, T>;

  template<typename T>
  constexpr bool has_pre_decrement_v = has_pre_decrement<T>::value;

  template<typename T>
  using post_decrement_t = decltype(std::declval<T>()--);

  template<typename T>
  using has_post_decrement = std::experimental::is_detected<post_decrement_t, T>;

  template<typename T>
  constexpr bool has_post_decrement_v = has_post_decrement<T>::value;

  template<typename T>
  using has_decrement_t = std::conjunction<
      decltype(--std::declval<T&>()),
      decltype(std::declval<T&>()--)>;

  template<typename T>
  using has_decrement = std::experimental::is_detected<has_decrement_t, T>;

  template<typename T>
  constexpr bool has_decrement_v = has_decrement<T>::value;

  template<typename T>
  using has_addition_t = std::conjunction<
      decltype(std::declval<T>() += std::declval<T>()),
      decltype(std::declval<T>() + std::declval<T>())>;

  template<typename T>
  using has_addition = std::experimental::is_detected<has_addition_t, T>;

  template<typename T>
  constexpr bool has_addition_v = has_addition<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_addition_t = std::conjunction<
      decltype(std::declval<T>() += std::declval<T>()),
      decltype(std::declval<T>() += std::declval<U>()),
      decltype(std::declval<T>() + std::declval<U>()),
      decltype(std::declval<U>() + std::declval<T>()),
      decltype(std::declval<T>() + std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_addition = std::experimental::is_detected<has_mixed_mode_addition_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_addition_v = has_mixed_mode_addition<T, U>::value;

  template<typename T>
  using has_subtraction_t = std::conjunction<
      decltype(std::declval<T>() -= std::declval<T>()),
      decltype(std::declval<T>() - std::declval<T>())>;

  template<typename T>
  using has_subtraction = std::experimental::is_detected<has_subtraction_t, T>;

  template<typename T>
  constexpr bool has_subtraction_v = has_subtraction<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_subtraction_t = std::conjunction<
      decltype(std::declval<T>() -= std::declval<T>()),
      decltype(std::declval<T>() -= std::declval<U>()),
      decltype(std::declval<T>() - std::declval<U>()),
      decltype(std::declval<U>() - std::declval<T>()),
      decltype(std::declval<T>() - std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_subtraction = std::experimental::is_detected<has_mixed_mode_subtraction_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_subtraction_v = has_mixed_mode_subtraction<T, U>::value;

  template<typename T>
  using has_multiplication_t = std::conjunction<
      decltype(std::declval<T>() *= std::declval<T>()),
      decltype(std::declval<T>() * std::declval<T>())>;

  template<typename T>
  using has_multiplication = std::experimental::is_detected<has_multiplication_t, T>;

  template<typename T>
  constexpr bool has_multiplication_V = has_multiplication<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_multiplication_t = std::conjunction<
      decltype(std::declval<T>() *= std::declval<T>()),
      decltype(std::declval<T>() *= std::declval<U>()),
      decltype(std::declval<T>() * std::declval<U>()),
      decltype(std::declval<U>() * std::declval<T>()),
      decltype(std::declval<T>() * std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_multiplication = std::experimental::is_detected<has_mixed_mode_multiplication_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_multiplication_v = has_mixed_mode_multiplication<T, U>::value;

  template<typename T>
  using has_division_t = std::conjunction<
      decltype(std::declval<T>() /= std::declval<T>()),
      decltype(std::declval<T>() / std::declval<T>())>;

  template<typename T>
  using has_division = std::experimental::is_detected<has_division_t, T>;

  template<typename T>
  constexpr bool has_division_v = has_division<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_division_t = std::conjunction<
      decltype(std::declval<T>() /= std::declval<T>()),
      decltype(std::declval<T>() /= std::declval<U>()),
      decltype(std::declval<T>() / std::declval<U>()),
      decltype(std::declval<U>() / std::declval<T>()),
      decltype(std::declval<T>() / std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_division = std::experimental::is_detected<has_mixed_mode_division_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_division_v = has_mixed_mode_division<T, U>::value;

  template<typename T>
  using has_modulus_t = std::conjunction<
      decltype(std::declval<T>() %= std::declval<T>()),
      decltype(std::declval<T>() % std::declval<T>())>;

  template<typename T>
  using has_modulus = std::experimental::is_detected<has_modulus_t, T>;

  template<typename T>
  constexpr bool has_modulus_v = has_modulus<T>::value;


  template<typename T, typename U>
  using has_mixed_mode_modulus_t = std::conjunction<
      decltype(std::declval<T>() %= std::declval<T>()),
      decltype(std::declval<T>() %= std::declval<U>()),
      decltype(std::declval<T>() % std::declval<U>()),
      decltype(std::declval<U>() % std::declval<T>()),
      decltype(std::declval<T>() % std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_modulus = std::experimental::is_detected<has_mixed_mode_modulus_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_modulus_v = has_mixed_mode_modulus<T, U>::value;
}
#endif //ARITHMETIC_NAMED_TYPE_ARITHMETIC_TYPE_TRAITS_HPP
