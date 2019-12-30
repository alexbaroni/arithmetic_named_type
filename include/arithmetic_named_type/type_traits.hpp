#ifndef ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP
#define ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP

#include <experimental/type_traits>
#include "arithmetic_type_traits.hpp"
#include "bitwise_type_traits.hpp"
#include "relational_type_traits.hpp"
#include "logical_type_traits.hpp"
#include "crtp_helper.hpp"

namespace type_util {
  template <class T, class U>
  struct is_same_signedness
      : public std::integral_constant<bool, std::is_signed_v<T> == std::is_signed_v<U>> {};

  template <class T, class U>
  constexpr bool is_same_signedness_v = is_same_signedness<T, U>::value;

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
  constexpr bool is_narrowing_conversion_v = is_narrowing_conversion<From, To>::value;

  template<typename From, typename To>
  struct is_safe_conversion :
      public std::integral_constant<bool,
        std::is_same_v<std::decay_t<To>, std::decay_t<From>> ||
        std::is_same_v<std::decay_t<To>, typename std::common_type_t<std::decay_t<To>, std::decay_t<From>>>> {};

  template<typename From, typename To>
  constexpr bool is_safe_conversion_() {
    using from_t = std::decay_t<From>;
    using to_t = std::decay_t<To>;
    if constexpr (std::is_same_v<bool, from_t> || std::is_same_v<bool, to_t>) {
      return false;
    }
    else if constexpr (std::is_integral_v<From> && std::is_integral_v<To>) {
      return std::is_same_v<from_t, to_t> ||
          (!std::is_same_v<std::make_unsigned_t<from_t>, std::make_unsigned_t<to_t>> &&
              is_safe_conversion<From, To>::value);
    }
    else {
      return is_safe_conversion<From, To>::value;
    }
  }

  template<typename From, typename To>
  constexpr bool is_safe_conversion_v = is_safe_conversion_<From, To>();
}


#endif //ARITHMETIC_NAMED_TYPE_TYPE_TRAITS_HPP
