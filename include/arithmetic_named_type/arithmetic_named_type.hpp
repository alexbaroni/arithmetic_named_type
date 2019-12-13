#ifndef ARITHMETIC_NAMED_TYPE_HPP
#define ARITHMETIC_NAMED_TYPE_HPP

#include <type_traits>

template<typename T, typename Tag, typename std::enable_if_t<std::is_arithmetic_v<T>>>
class arithmetic_named_type {
public:
  explicit arithmetic_named_type(T value) : value_(value) {}
  operator T() const { return value_; }

private:
  T value_;
};

#endif //ARITHMETIC_NAMED_TYPE_HPP
