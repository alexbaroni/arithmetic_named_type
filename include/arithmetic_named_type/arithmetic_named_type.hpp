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

    constexpr T& get() noexcept { return value_; }
    constexpr T const& get() const noexcept { return value_; }

  private:
    T value_;
  };

  template <typename T>
  struct pre_incrementable : detail::crtp_helper<T, pre_incrementable>
  {
    T& operator++() { ++this->underlying().get(); return this->underlying(); }
  };

  template <typename T>
  struct post_incrementable : detail::crtp_helper<T, post_incrementable>
  {
    const T& operator++(int) { auto tmp = this->underlying().get(); this->underlying().get()++; return tmp; }
  };

  template <typename T>
  struct comparable : detail::crtp_helper<T, comparable>
  {
    bool operator==(T const& other) const { return this->underlying().get() == other.get(); }
    bool operator!=(T const& other) const { return !(*this == other); }
  private:
    // generates a non-template operator... for this T and this arithmetic_named_type
    template <typename U>
    friend bool operator== (U const& y, T const& x)
    {
      return T(y).get() == x.get();
    }

    template <typename U>
    friend bool operator== (T const& x, U const& y)
    {
      return x.get() == T(y).get();
    }

    friend bool operator== (T const& x, T const& y)
    {
      return x.get() == y.get();
    }

    template <typename U>
    friend bool operator!= (U const& y, T const& x)
    {
      return T(y).get() != x.get();
    }

    template <typename U>
    friend bool operator!= (T const& x, U const& y)
    {
      return x.get() != T(y).get();
    }

    friend bool operator!= (T const& x, T const& y)
    {
      return x.get() != y.get();
    }
  };

  template <typename T>
  struct orderable : detail::crtp_helper<T, orderable>
  {
    bool operator<(T const& other) const  { return this->underlying().get() < other.get(); }
    bool operator>(T const& other) const  { return other.get() < this->underlying().get(); }
    bool operator<=(T const& other) const { return !(*this > other); }
    bool operator>=(T const& other) const { return !(*this < other); }
  private:
    template <typename U>
    friend bool operator< (U const& y, T const& x)
    {
      return T(y).get() < x.get();
    }

    template <typename U>
    friend bool operator< (T const& x, U const& y)
    {
      return x.get() < T(y).get();
    }

    friend bool operator< (T const& x, T const& y)
    {
      return x.get() < y.get();
    }

    template <typename U>
    friend bool operator> (U const& y, T const& x)
    {
      return T(y).get() > x.get();
    }

    template <typename U>
    friend bool operator> (T const& x, U const& y)
    {
      return x.get() > T(y).get();
    }

    friend bool operator> (T const& x, T const& y)
    {
      return x.get() > y.get();
    }

    template <typename U>
    friend bool operator<= (U const& y, T const& x)
    {
      return T(y).get() <= x.get();
    }

    template <typename U>
    friend bool operator<= (T const& x, U const& y)
    {
      return x.get() <= T(y).get();
    }

    friend bool operator<= (T const& x, T const& y)
    {
      return x.get() <= y.get();
    }

    template <typename U>
    friend bool operator>= (U const& y, T const& x)
    {
      return T(y).get() >= x.get();
    }

    template <typename U>
    friend bool operator>= (T const& x, U const& y)
    {
      return x.get() >= T(y).get();
    }

    friend bool operator>= (T const& x, T const& y)
    {
      return x.get() >= y.get();
    }
  };
}
#endif //ARITHMETIC_NAMED_TYPE_HPP
