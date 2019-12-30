#ifndef ARITHMETIC_NAMED_TYPE_RELATIONAL_TYPE_TRAITS_HPP
#define ARITHMETIC_NAMED_TYPE_RELATIONAL_TYPE_TRAITS_HPP

#include <experimental/type_traits>

namespace type_util {
  template<typename T>
  using has_equivalence_t = std::conjunction<
      decltype(std::declval<T>() == std::declval<T>()),
      decltype(std::declval<T>() != std::declval<T>())>;

  template<typename T>
  using has_equivalence = std::experimental::is_detected<has_equivalence_t, T>;

  template<typename T>
  constexpr bool has_equivalence_v = has_equivalence<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_equivalence_t = std::conjunction<
      decltype(std::declval<T>() == std::declval<T>()),
      decltype(std::declval<T>() == std::declval<U>()),
      decltype(std::declval<U>() == std::declval<T>()),
      decltype(std::declval<T>() != std::declval<T>()),
      decltype(std::declval<T>() != std::declval<U>()),
      decltype(std::declval<U>() != std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_equivalence = std::experimental::is_detected<has_mixed_mode_equivalence_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_equivalence_v = has_mixed_mode_equivalence<T, U>::value;

  template<typename T>
  using has_ordering_t = std::conjunction<
      decltype(std::declval<T>() < std::declval<T>()),
      decltype(std::declval<T>() <= std::declval<T>()),
      decltype(std::declval<T>() >= std::declval<T>()),
      decltype(std::declval<T>() > std::declval<T>())>;

  template<typename T>
  using has_ordering = std::experimental::is_detected<has_ordering_t, T>;

  template<typename T>
  constexpr bool has_ordering_v = has_ordering<T>::value;

  template<typename T, typename U>
  using has_mixed_mode_ordering_t = std::conjunction<
      decltype(std::declval<T>() < std::declval<T>()),
      decltype(std::declval<T>() < std::declval<U>()),
      decltype(std::declval<U>() < std::declval<T>()),
      decltype(std::declval<T>() <= std::declval<T>()),
      decltype(std::declval<T>() <= std::declval<U>()),
      decltype(std::declval<U>() <= std::declval<T>()),
      decltype(std::declval<T>() >= std::declval<T>()),
      decltype(std::declval<T>() >= std::declval<U>()),
      decltype(std::declval<U>() >= std::declval<T>()),
      decltype(std::declval<T>() > std::declval<T>()),
      decltype(std::declval<T>() > std::declval<U>()),
      decltype(std::declval<U>() > std::declval<T>())>;

  template<typename T, typename U>
  using has_mixed_mode_ordering = std::experimental::is_detected<has_mixed_mode_ordering_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_mixed_mode_ordering_v = has_mixed_mode_ordering<T, U>::value;
}
#endif //ARITHMETIC_NAMED_TYPE_RELATIONAL_TYPE_TRAITS_HPP
