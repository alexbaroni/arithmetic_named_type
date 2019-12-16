#ifndef ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP
#define ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP

#include <experimental/type_traits>

namespace type_util {
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

  template<typename T, typename U>
  using has_equivalence_t = std::conjunction<
      decltype(std::declval<T>() == std::declval<U>()),
      decltype(std::declval<T>() != std::declval<U>())>;

  template<typename T, typename U>
  using has_equivalence = std::experimental::is_detected<has_equivalence_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_equivalence_v = has_equivalence<T, U>::value;

  template<typename T, typename U>
  using has_ordering_t = std::conjunction<
      decltype(std::declval<T>() < std::declval<U>()),
      decltype(std::declval<T>() <= std::declval<U>()),
      decltype(std::declval<T>() >= std::declval<U>()),
      decltype(std::declval<T>() > std::declval<U>())>;

  template<typename T, typename U>
  using has_ordering = std::experimental::is_detected<has_ordering_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_ordering_v = has_ordering<T, U>::value;}

#endif //ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP
