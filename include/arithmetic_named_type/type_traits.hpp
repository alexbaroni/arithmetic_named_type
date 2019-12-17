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

  template<typename T>
  using has_increment_t = std::conjunction<
      decltype(++std::declval<T&>()),
      decltype(std::declval<T&>()++)>;

  template<typename T>
  using has_increment = std::experimental::is_detected<has_increment_t, T>;

  template<typename T, typename U>
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

  template<typename T, typename U>
  constexpr bool has_decrement_v = has_decrement<T>::value;

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
  constexpr bool has_ordering_v = has_ordering<T, U>::value;

  template<typename T, typename U>
  using has_addition_t = std::conjunction<
      decltype(std::declval<T>() += std::declval<T>()),
      decltype(std::declval<T>() += std::declval<U>()),
      decltype(std::declval<T>() + std::declval<U>()),
      decltype(std::declval<U>() + std::declval<T>()),
      decltype(std::declval<T>() + std::declval<T>())>;

  template<typename T, typename U>
  using has_addition = std::experimental::is_detected<has_addition_t, T, U>;

  template<typename T, typename U>
  constexpr bool has_addition_v = has_addition<T, U>::value;

  template<typename T>
  struct identity { using type = T; };

  template<typename To>
  constexpr std::true_type is_narrowing_conversion_aux(typename identity<To>::type);
  constexpr std::false_type is_narrowing_conversion_aux(...);

  template<typename From, typename To, typename = void, typename = void>
  struct is_narrowing_conversion : std::true_type {};
  template<typename From, typename To>
  struct is_narrowing_conversion<From, To,
      std::enable_if_t<std::is_arithmetic_v<From> && std::is_arithmetic_v<To>>,
      std::enable_if_t<decltype(is_narrowing_conversion_aux<To>({std::declval<From>()}))::value>> : std::false_type {
  };

  template<typename From, typename To>
  inline constexpr bool is_narrowing_conversion_v =
      is_narrowing_conversion<From, To>::value;
}

//template <class T, class U>
//struct is_same_signedness
//    : public std::integral_constant<bool, std::is_signed<T>::value == std::is_signed<U>::value>
//{
//};

#endif //ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP
