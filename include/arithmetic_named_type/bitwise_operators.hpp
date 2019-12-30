#ifndef ARITHMETIC_NAMED_TYPE_BITWISE_OPERATORS_HPP
#define ARITHMETIC_NAMED_TYPE_BITWISE_OPERATORS_HPP

#include <type_traits>
#include "crtp_helper.hpp"

namespace type_util {
  template<typename T>
  struct bitwise_not : detail::crtp_helper<T, bitwise_not> {
    T operator~() const {
      auto tmp = ~this->underlying().get();
      return T{tmp};
    }
  };

  template<typename T>
  struct bitwise_and : detail::crtp_helper<T, bitwise_and> {
    T& operator&=(T const& y) {
      this->underlying().get() &= y.get();
      return this->underlying();
    }

  private:
    friend T operator&(T x, T const& y) {
      return x &= y;
    }
  };

  template<typename T>
  struct mixed_mode_and : detail::crtp_helper<T, mixed_mode_and> {
    T& operator&=(T const& y) {
      this->underlying().get() &= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator&=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_and>::underlying_type::underlying_type>,
          "bitwise and with unsafe conversion detected");
      this->underlying().get() &= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator&(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_and>::underlying_type::underlying_type>,
          "bitwise and with unsafe conversion detected");
      return x &= y;
    }

    template<typename U>
    friend T operator&(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_and>::underlying_type::underlying_type>,
          "bitwise and with unsafe conversion detected");
      return x &= y;
    }

    friend T operator&(T x, T const& y) {
      return x &= y;
    }
  };

  template<typename T>
  struct bitwise_or : detail::crtp_helper<T, bitwise_or> {
    T& operator|=(T const& y) {
      this->underlying().get() |= y.get();
      return this->underlying();
    }

  private:
    friend T operator|(T x, T const& y) {
      return x |= y;
    }
  };

  template<typename T>
  struct mixed_mode_or : detail::crtp_helper<T, mixed_mode_or> {
    T& operator|=(T const& y) {
      this->underlying().get() |= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator|=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_or>::underlying_type::underlying_type>,
          "bitwise or with unsafe conversion detected");
      this->underlying().get() |= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator|(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_or>::underlying_type::underlying_type>,
          "bitwise or with unsafe conversion detected");
      return x |= y;
    }

    template<typename U>
    friend T operator|(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_or>::underlying_type::underlying_type>,
          "bitwise or with unsafe conversion detected");
      return x |= y;
    }

    friend T operator|(T x, T const& y) {
      return x |= y;
    }
  };

  template<typename T>
  struct bitwise_xor : detail::crtp_helper<T, bitwise_xor> {
    T& operator^=(T const& y) {
      this->underlying().get() ^= y.get();
      return this->underlying();
    }

  private:
    friend T operator^(T x, T const& y) {
      return x ^= y;
    }
  };

  template<typename T>
  struct mixed_mode_xor : detail::crtp_helper<T, mixed_mode_xor> {
    T& operator^=(T const& y) {
      this->underlying().get() ^= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator^=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_xor>::underlying_type::underlying_type>,
          "bitwise xor with unsafe conversion detected");
      this->underlying().get() ^= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator^(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_xor>::underlying_type::underlying_type>,
          "bitwise xor with unsafe conversion detected");
      return x ^= y;
    }

    template<typename U>
    friend T operator^(U const& y, T x) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_xor>::underlying_type::underlying_type>,
          "bitwise xor with unsafe conversion detected");
      return x ^= y;
    }

    friend T operator^(T x, T const& y) {
      return x ^= y;
    }
  };

  template<typename T>
  struct bitwise_left_shift : detail::crtp_helper<T, bitwise_left_shift> {
    T& operator<<=(T const& y) {
      this->underlying().get() <<= y.get();
      return this->underlying();
    }

  private:
    friend T operator<<(T x, T const& y) {
      return x <<= y;
    }
  };

  template<typename T>
  struct mixed_mode_bitwise_left_shift : detail::crtp_helper<T, mixed_mode_bitwise_left_shift> {
    T& operator<<=(T const& y) {
      this->underlying().get() <<= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator<<=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_bitwise_left_shift>::underlying_type::underlying_type>,
          "bitwise left shift with unsafe conversion detected");
      this->underlying().get() <<= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator<<(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_bitwise_left_shift>::underlying_type::underlying_type>,
          "bitwise left shift with unsafe conversion detected");
      return x <<= y;
    }

    friend T operator<<(T x, T const& y) {
      return x <<= y;
    }
  };

  template<typename T>
  struct bitwise_right_shift : detail::crtp_helper<T, bitwise_right_shift> {
    T& operator>>=(T const& y) {
      this->underlying().get() >>= y.get();
      return this->underlying();
    }

  private:
    friend T operator>>(T x, T const& y) {
      return x >>= y;
    }
  };

  template<typename T>
  struct mixed_mode_bitwise_right_shift : detail::crtp_helper<T, mixed_mode_bitwise_right_shift> {
    T& operator>>=(T const& y) {
      this->underlying().get() >>= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator>>=(U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_bitwise_right_shift>::underlying_type::underlying_type>,
          "bitwise right shift with unsafe conversion detected");
      this->underlying().get() >>= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator>>(T x, U const& y) {
      static_assert(
          is_safe_conversion_v<U,
          typename detail::crtp_helper<T, mixed_mode_bitwise_right_shift>::underlying_type::underlying_type>,
          "bitwise right shift with unsafe conversion detected");
      return x >>= y;
    }

    friend T operator>>(T x, T const& y) {
      return x >>= y;
    }
  };
}
#endif //ARITHMETIC_NAMED_TYPE_BITWISE_OPERATORS_HPP
