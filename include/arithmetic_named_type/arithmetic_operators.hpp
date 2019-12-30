#ifndef ARITHMETIC_NAMED_TYPE_ARITHMETIC_OPERATORS_HPP
#define ARITHMETIC_NAMED_TYPE_ARITHMETIC_OPERATORS_HPP

#include <type_traits>
#include <cmath>
#include "crtp_helper.hpp"

namespace type_util {
  template<typename T>
  struct unary_plus : detail::crtp_helper<T, unary_plus> {
    T operator+() const {
      return this->underlying();
    }
  };

  template<typename T>
  struct unary_minus : detail::crtp_helper<T, unary_minus> {
    T operator-() const {
      T tmp{-this->underlying().get()};
      return tmp;
    }
  };

  template<typename T>
  struct pre_incrementable : detail::crtp_helper<T, pre_incrementable> {
    T& operator++() {
      ++this->underlying().get();
      return this->underlying();
    }
  };

  template<typename T>
  struct post_incrementable : detail::crtp_helper<T, post_incrementable> {
    T const& operator++(int) {
      auto tmp = *this;
      this->underlying().get()++;
      return tmp.underlying();
    }
  };

  template<typename T>
  struct incrementable : detail::crtp_helper<T, incrementable> {
    T& operator++() {
      ++this->underlying().get();
      return this->underlying();
    }

    T const& operator++(int) {
      auto tmp = *this;
      this->underlying().get()++;
      return tmp.underlying();
    }
  };

  template<typename T>
  struct pre_decrementable : detail::crtp_helper<T, pre_decrementable> {
    T& operator--() {
      --this->underlying().get();
      return this->underlying();
    }
  };

  template<typename T>
  struct post_decrementable : detail::crtp_helper<T, post_decrementable> {
    T const& operator--(int) {
      auto tmp = *this;
      this->underlying().get()--;
      return tmp.underlying();
    }
  };

  template<typename T>
  struct decrementable : detail::crtp_helper<T, decrementable> {
    T& operator--() {
      --this->underlying().get();
      return this->underlying();
    }

    T const& operator--(int) {
      auto tmp = *this;
      this->underlying().get()--;
      return tmp.underlying();
    }
  };

  template<typename T>
  struct addable : detail::crtp_helper<T, addable> {
    T& operator+=(T const& y) {
      this->underlying().get() += y.get();
      return this->underlying();
    }

  private:
    friend T operator+(T x, T const& y) {
      return x += y;
    }
  };

  template<typename T>
  struct mixed_mode_addable : detail::crtp_helper<T, mixed_mode_addable> {
    T& operator+=(T const& y) {
      this->underlying().get() += y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator+=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_addable>::underlying_type::underlying_type>,
          "addition with unsafe conversion detected");
      this->underlying().get() += y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator+(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_addable>::underlying_type::underlying_type>,
          "addition with unsafe conversion detected");
      return x += y;
    }

    template<typename U>
    friend T operator+(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_addable>::underlying_type::underlying_type>,
          "addition with unsafe conversion detected");
      return x += y;
    }

    friend T operator+(T x, T const& y) {
      return x += y;
    }
  };

  template<typename T>
  struct subtractable : detail::crtp_helper<T, subtractable> {
    T& operator-=(T const& y) {
      this->underlying().get() -= y.get();
      return this->underlying();
    }

  private:
    friend T operator-(T x, T const& y) {
      return x -= y;
    }
  };

  template<typename T>
  struct mixed_mode_subtractable : detail::crtp_helper<T, mixed_mode_subtractable> {
    T& operator-=(T const& y) {
      this->underlying().get() -= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator-=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_subtractable>::underlying_type::underlying_type>,
          "subtraction with unsafe conversion detected");
      this->underlying().get() -= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator-(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_subtractable>::underlying_type::underlying_type>,
          "subtraction with unsafe conversion detected");
      return x -= y;
    }

    template<typename U>
    friend T operator-(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_subtractable>::underlying_type::underlying_type>,
          "subtraction with unsafe conversion detected");
      return T{y} -= x;
    }

    friend T operator-(T x, T const& y) {
      return x -= y;
    }
  };

  template<typename T>
  struct multipliable : detail::crtp_helper<T, multipliable> {
    T& operator*=(T const& y) {
      this->underlying().get() *= y.get();
      return this->underlying();
    }

  private:
    friend T operator*(T x, T const& y) {
      return x *= y;
    }
  };

  template<typename T>
  struct mixed_mode_multipliable : detail::crtp_helper<T, mixed_mode_multipliable> {
    T& operator*=(T const& y) {
      this->underlying().get() *= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator*=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_multipliable>::underlying_type::underlying_type>,
          "multiplication with unsafe conversion detected");
      this->underlying().get() *= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator*(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_multipliable>::underlying_type::underlying_type>,
          "multiplication with unsafe conversion detected");
      return x *= y;
    }

    template<typename U>
    friend T operator*(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_multipliable>::underlying_type::underlying_type>,
          "multiplication with unsafe conversion detected");
      return T{y} *= x;
    }

    friend T operator*(T x, T const& y) {
      return x *= y;
    }
  };

  namespace detail {
    template<typename T, typename U>
    auto remainder(T const& x, U const& y) {
      if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
        return x % y;
      else
        return std::fmod(x, y);
    }
  }

  template<typename T>
  struct divisible : detail::crtp_helper<T, divisible> {
    T& operator/=(T const& y) {
      this->underlying().get() /= y.get();
      return this->underlying();
    }

    T& operator%=(T const& y) {
      this->underlying().get() = detail::remainder(this->underlying().get(), y.get());
      return this->underlying();
    }
  private:
    friend T operator/(T x, T const& y) {
      return x /= y;
    }

    friend T operator%(T x, T const& y) {
      return x %= y;
    }
  };

  template<typename T>
  struct mixed_mode_divisible : detail::crtp_helper<T, mixed_mode_divisible> {
    T& operator/=(T const& y) {
      this->underlying().get() /= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator/=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_divisible>::underlying_type::underlying_type>,
          "division with unsafe conversion detected");
      this->underlying().get() /= y;
      return this->underlying();
    }

    T& operator%=(T const& y) {
      this->underlying().get() = detail::remainder(this->underlying().get(), y.get());
      return this->underlying();
    }

    template<typename U>
    T& operator%=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_divisible>::underlying_type::underlying_type>,
          "modulus with unsafe conversion detected");
      this->underlying().get() = detail::remainder(this->underlying().get(), y);
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator/(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_divisible>::underlying_type::underlying_type>,
          "division with unsafe conversion detected");
      return x /= y;
    }

    template<typename U>
    friend T operator/(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_divisible>::underlying_type::underlying_type>,
          "division with unsafe conversion detected");
      return T{y} /= x;
    }

    friend T operator/(T x, T const& y) {
      return x /= y;
    }

    template<typename U>
    friend T operator%(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_divisible>::underlying_type::underlying_type>,
          "modulus with unsafe conversion detected");
      return x %= y;
    }

    template<typename U>
    friend T operator%(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_divisible>::underlying_type::underlying_type>,
          "modulus with unsafe conversion detected");
      return T{y} %= x;
    }

    friend T operator%(T x, T const& y) {
      return x %= y;
    }
  };
}
#endif //ARITHMETIC_NAMED_TYPE_ARITHMETIC_OPERATORS_HPP
