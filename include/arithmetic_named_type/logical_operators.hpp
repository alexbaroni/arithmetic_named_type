#ifndef ARITHMETIC_NAMED_TYPE_LOGICAL_OPERATORS_HPP
#define ARITHMETIC_NAMED_TYPE_LOGICAL_OPERATORS_HPP

#include <type_traits>
#include "crtp_helper.hpp"

namespace type_util {
  template<typename T>
  struct logical_not : detail::crtp_helper<T, logical_not> {
    bool operator!() const { return !this->underlying().get(); }

  private:
    friend bool operator!(T const& x) {
      return !x.get();
    }
  };
}
#endif //ARITHMETIC_NAMED_TYPE_LOGICAL_OPERATORS_HPP
