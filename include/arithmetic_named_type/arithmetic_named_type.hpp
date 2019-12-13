#ifndef ARITHMETIC_NAMED_TYPE_HPP
#define ARITHMETIC_NAMED_TYPE_HPP

#include <type_traits>

namespace type_util {
  namespace detail {
    template <typename T, template<typename> class>
    struct crtp_helper {
      T& underlying() { return static_cast<T&>(*this); }
      T const& underlying() const { return static_cast<T const&>(*this); }
    };
  }

  template<typename T, typename Tag, template<typename> class... Skills>
  class arithmetic_named_type  : public Skills<arithmetic_named_type<T, Tag, Skills...>>... {
    static_assert(std::is_arithmetic_v<T>, "Requires arithmetic types");
  public:
    using underlying_type = T;

    constexpr arithmetic_named_type() noexcept : value_{} {}
    explicit constexpr arithmetic_named_type(T value) noexcept : value_(value) {}

    constexpr operator T&() noexcept { return value_; }
    constexpr operator const T&() const noexcept { return value_; }

  private:
    T value_;
  };

  template <typename T>
  struct pre_incrementable : detail::crtp_helper<T, pre_incrementable>
  {
    T& operator++() {
      ++this->underlying();
      return this->underlying();
    }
  };
}
#endif //ARITHMETIC_NAMED_TYPE_HPP
