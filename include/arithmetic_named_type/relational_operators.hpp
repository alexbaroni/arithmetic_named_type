#ifndef ARITHMETIC_NAMED_TYPE_RELATIONAL_OPERATORS_HPP
#define ARITHMETIC_NAMED_TYPE_RELATIONAL_OPERATORS_HPP

#include <type_traits>
#include "crtp_helper.hpp"

namespace type_util {
  template<typename T>
  struct comparable : detail::crtp_helper<T, comparable> {
    bool operator==(T const& y) const { return this->underlying().get() == y.get(); }
    bool operator!=(T const& y) const { return !(*this == y); }

  private:
    friend bool operator==(T const& x, T const& y) {
      return x.get() == y.get();
    }
    friend bool operator!=(T const& x, T const& y) {
      return x.get() != y.get();
    }
  };

  template<typename T>
  struct mixed_mode_comparable : detail::crtp_helper<T, mixed_mode_comparable> {
    bool operator==(T const& y) const { return this->underlying().get() == y.get(); }
    bool operator!=(T const& y) const { return !(*this == y); }

    template<typename U>
    bool operator==(U const& y) const { return this->underlying().get() == y; }
    template<typename U>
    bool operator!=(U const& y) const { return !(this->underlying().get() == y); }

  private:
    // generates a non-template operator... for this T and this arithmetic_named_type
    template<typename U>
    friend bool operator==(U const& y, T const& x) {
      return x.get() == y;
    }

    friend bool operator==(T const& x, T const& y) {
      return x.get() == y.get();
    }

    template<typename U>
    friend bool operator!=(U const& y, T const& x) {
      return x.get() != y;
    }

    friend bool operator!=(T const& x, T const& y) {
      return x.get() != y.get();
    }
  };

  template<typename T>
  struct orderable : detail::crtp_helper<T, orderable> {
    bool operator<(T const& y) const { return this->underlying().get() < y.get(); }
    bool operator>(T const& y) const { return y.get() < this->underlying().get(); }
    bool operator<=(T const& y) const { return !(*this > y); }
    bool operator>=(T const& y) const { return !(*this < y); }
  private:
    friend bool operator<(T const& x, T const& y) {
      return x.get() < y.get();
    }

    friend bool operator>(T const& x, T const& y) {
      return x.get() > y.get();
    }

    friend bool operator<=(T const& x, T const& y) {
      return x.get() <= y.get();
    }

    friend bool operator>=(T const& x, T const& y) {
      return x.get() >= y.get();
    }
  };

  template<typename T>
  struct mixed_mode_orderable : detail::crtp_helper<T, mixed_mode_orderable> {
    bool operator<(T const& y) const { return this->underlying().get() < y.get(); }
    bool operator>(T const& y) const { return y.get() < this->underlying().get(); }
    bool operator<=(T const& y) const { return !(*this > y); }
    bool operator>=(T const& y) const { return !(*this < y); }

    template<typename U>
    bool operator<(U const& y) const { return this->underlying().get() < y; }
    template<typename U>
    bool operator>(U const& y) const { return y < this->underlying().get(); }
    template<typename U>
    bool operator<=(U const& y) const { return !(*this > y); }
    template<typename U>
    bool operator>=(U const& y) const { return !(*this < y); }
  private:
    template<typename U>
    friend bool operator<(U const& y, T const& x) {
      return T(y).get() < x.get();
    }

    friend bool operator<(T const& x, T const& y) {
      return x.get() < y.get();
    }

    template<typename U>
    friend bool operator>(U const& y, T const& x) {
      return T(y).get() > x.get();
    }

    friend bool operator>(T const& x, T const& y) {
      return x.get() > y.get();
    }

    template<typename U>
    friend bool operator<=(U const& y, T const& x) {
      return T(y).get() <= x.get();
    }

    friend bool operator<=(T const& x, T const& y) {
      return x.get() <= y.get();
    }

    template<typename U>
    friend bool operator>=(U const& y, T const& x) {
      return T(y).get() >= x.get();
    }

    friend bool operator>=(T const& x, T const& y) {
      return x.get() >= y.get();
    }
  };
}

#endif //ARITHMETIC_NAMED_TYPE_RELATIONAL_OPERATORS_HPP
