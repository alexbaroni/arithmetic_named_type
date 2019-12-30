#ifndef ARITHMETIC_NAMED_TYPE_HPP
#define ARITHMETIC_NAMED_TYPE_HPP

#include <type_traits>
#include "arithmetic_operators.hpp"
#include "relational_operators.hpp"
#include "bitwise_operators.hpp"
#include "logical_operators.hpp"

namespace type_util {
  template<typename T, typename Tag, template<typename> class... Skills>
  class arithmetic_named_type : public Skills<arithmetic_named_type<T, Tag, Skills...>> ... {
    static_assert(std::is_arithmetic_v<T>, "Requires arithmetic types");
  public:
    using underlying_type = T;

    constexpr arithmetic_named_type() noexcept : value_{} {}
    explicit constexpr arithmetic_named_type(T value) noexcept : value_(value) {}
    constexpr T& get() noexcept { return value_; }
    constexpr T const& get() const noexcept { return value_; }

  private:
    T value_;
  };

  template<typename To>
  struct implicitly_convertible_to {
    template<typename T>
    struct conv_op : detail::crtp_helper<T, conv_op> {
      operator To() const {
        static_assert(
            is_safe_conversion_v<To,
                typename detail::crtp_helper<T, conv_op>::underlying_type::underlying_type>,
            "unsafe conversion detected");
        return this->underlying().get();
      }
    };
  };

  template<typename T>
  struct hashable {
    static constexpr bool is_hashable = true;
  };
}

namespace std {
  template<typename T, typename Tag, template<typename> class... Skills>
  struct hash<type_util::arithmetic_named_type<T, Tag, Skills...>> {
    using named_type = type_util::arithmetic_named_type<T, Tag, Skills...>;
    using check_if_hashable = typename std::enable_if<named_type::is_hashable, void>::type;

    size_t operator()(type_util::arithmetic_named_type<T, Tag, Skills...> const& x) const {
      return std::hash<T>()(x.get());
    }
  };

}
#endif //ARITHMETIC_NAMED_TYPE_HPP
