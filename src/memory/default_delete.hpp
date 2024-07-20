#pragma once

#include <memory>

namespace steev
{
template<typename T>
class default_delete
{
public:
  constexpr default_delete() noexcept = default;

  template<typename U>
  constexpr default_delete(const default_delete<U>&) noexcept
  {
    static_assert(std::is_convertible_v<U*, T*>);
  }

  void operator()(T* ptr) const
  {
    static_assert(sizeof(T) != 0, "Can't delete pointer to incomplete type");
    delete ptr;
  }
};

template<typename T>
class default_delete<T[]>
{
public:
  constexpr default_delete() noexcept = default;

  template<typename U>
  constexpr default_delete(const default_delete<U>&) noexcept
  {
    static_assert(std::is_convertible_v<U*, T*>);
  }

  void operator()(T* ptr) const
  {
    static_assert(sizeof(T) != 0, "Can't delete pointer to incomplete type");
    delete ptr;
  }
};
}  // namespace steev
