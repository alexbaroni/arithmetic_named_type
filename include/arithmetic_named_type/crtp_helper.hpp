#ifndef ARITHMETIC_NAMED_TYPE_CRTP_HELPER_HPP
#define ARITHMETIC_NAMED_TYPE_CRTP_HELPER_HPP

namespace type_util::detail {
  template<typename T, template<typename> class CRTP>
  struct crtp_helper {
    using underlying_type = T;

    T& underlying() { return static_cast<T&>(*this); }

    T const& underlying() const { return static_cast<T const&>(*this); }

  private:
    crtp_helper() {}

    friend CRTP<T>;
  };
}
#endif //ARITHMETIC_NAMED_TYPE_CRTP_HELPER_HPP
