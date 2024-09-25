#pragma once

#include <cstddef>
namespace steev
{
template<typename Ptr>
struct pointer_traits
{
  using pointer = Ptr;
  using element_type = Ptr::element_type;
  using difference_type = Ptr::difference_type;

  static pointer pointer_to(element_type& element)
  {
    return Ptr::pointer_to(element);
  }

  static const element_type* to_address(const pointer& ptr) noexcept
  {
    return ptr.get();
  }

  template<typename U>
  using rebind = typename Ptr::template rebind<U>;

  static element_type* to_address(pointer& ptr) noexcept { return ptr.get(); }
};

template<typename T>
struct pointer_traits<T*>
{
  using pointer = T*;
  using element_type = T;
  using difference_type = std::ptrdiff_t;

  template<typename U>
  using rebind = U*;

  static pointer pointer_to(element_type& element) { return &element; }

  static element_type* to_address(pointer* ptr) noexcept { return ptr; }
};
}  // namespace steev
