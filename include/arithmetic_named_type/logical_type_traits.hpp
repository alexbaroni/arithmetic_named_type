#ifndef ARITHMETIC_NAMED_TYPE_LOGICAL_TYPE_TRAITS_HPP
#define ARITHMETIC_NAMED_TYPE_LOGICAL_TYPE_TRAITS_HPP

#include <experimental/type_traits>

namespace type_util {
  template<typename T>
  using logical_not_t = decltype(!std::declval<T>());

  template<typename T>
  using has_logical_not = std::experimental::is_detected<logical_not_t, T>;

  template<typename T>
  constexpr bool has_logical_not_v = has_logical_not<T>::value;
}
#endif //ARITHMETIC_NAMED_TYPE_LOGICAL_TYPE_TRAITS_HPP
