#ifndef ARITHMETIC_NAMED_TYPE_HPP
#define ARITHMETIC_NAMED_TYPE_HPP

#include <type_traits>

namespace type_util {
  namespace detail {
    template<typename T, template<typename> class CRTP>
    struct crtp_helper {
      T& underlying() { return static_cast<T&>(*this); }
      T const& underlying() const { return static_cast<T const&>(*this); }

    private:
      crtp_helper() {}
      friend CRTP<T>;
    };
  }

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
  struct comparable : detail::crtp_helper<T, comparable> {
    bool operator==(T const& y) const { return this->underlying().get() == y.get(); }
    bool operator!=(T const& y) const { return !(*this == y); }

  private:
    // generates a non-template operator... for this T and this arithmetic_named_type
    template<typename U>
    friend bool operator==(U const& y, T const& x) {
      return T(y).get() == x.get();
    }

    template<typename U>
    friend bool operator==(T const& x, U const& y) {
      return x.get() == T(y).get();
    }

    friend bool operator==(T const& x, T const& y) {
      return x.get() == y.get();
    }

    template<typename U>
    friend bool operator!=(U const& y, T const& x) {
      return T(y).get() != x.get();
    }

    template<typename U>
    friend bool operator!=(T const& x, U const& y) {
      return x.get() != T(y).get();
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
    template<typename U>
    friend bool operator<(U const& y, T const& x) {
      return T(y).get() < x.get();
    }

    template<typename U>
    friend bool operator<(T const& x, U const& y) {
      return x.get() < T(y).get();
    }

    friend bool operator<(T const& x, T const& y) {
      return x.get() < y.get();
    }

    template<typename U>
    friend bool operator>(U const& y, T const& x) {
      return T(y).get() > x.get();
    }

    template<typename U>
    friend bool operator>(T const& x, U const& y) {
      return x.get() > T(y).get();
    }

    friend bool operator>(T const& x, T const& y) {
      return x.get() > y.get();
    }

    template<typename U>
    friend bool operator<=(U const& y, T const& x) {
      return T(y).get() <= x.get();
    }

    template<typename U>
    friend bool operator<=(T const& x, U const& y) {
      return x.get() <= T(y).get();
    }

    friend bool operator<=(T const& x, T const& y) {
      return x.get() <= y.get();
    }

    template<typename U>
    friend bool operator>=(U const& y, T const& x) {
      return T(y).get() >= x.get();
    }

    template<typename U>
    friend bool operator>=(T const& x, U const& y) {
      return x.get() >= T(y).get();
    }

    friend bool operator>=(T const& x, T const& y) {
      return x.get() >= y.get();
    }
  };

  template<typename T>
  struct addable : detail::crtp_helper<T, addable> {
    T& operator+=(T const& y) {
      this->underlying().get() += y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator+=(U const& y) {
      this->underlying().get() += y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator+(T x, U const& y) {
      return x += y;
    }

    template<typename U>
    friend T operator+(U const& y, T x) {
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

    template<typename U>
    T& operator-=(U const& y) {
      this->underlying().get() -= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator-(T x, U const& y) {
      return x -= y;
    }

    template<typename U>
    friend T operator-(U const& y, T x) {
      return T{y} -= x;
    }

    friend T operator-(T x, T const& y) {
      return x -= y;
    }
  };

  template<typename T>
  struct multiplicable : detail::crtp_helper<T, multiplicable> {
    T& operator*=(T const& y) {
      this->underlying().get() *= y.get();
      return this->underlying();
    }

    template<typename U>
    T& operator*=(U const& y) {
      this->underlying().get() *= y;
      return this->underlying();
    }

  private:
    template<typename U>
    friend T operator*(T x, U const& y) {
      return x *= y;
    }

    template<typename U>
    friend T operator*(U const& y, T x) {
      return T{y} *= x;
    }

    friend T operator*(T x, T const& y) {
      return x *= y;
    }
  };
}
#endif //ARITHMETIC_NAMED_TYPE_HPP
