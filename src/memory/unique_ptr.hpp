#pragma once

namespace steev
{

template<typename T>
class unique_ptr
{
  T* pointer_;

public:
  explicit unique_ptr(T* ptr)
      : pointer_(ptr)
  {
  }

  unique_ptr& operator=(unique_ptr&& ptr) noexcept
  {
    pointer_ = ptr.pointer_;
    ptr.pointer_ = nullptr;
  }

  unique_ptr(unique_ptr&& ptr) noexcept
      : pointer_(ptr.pointer_)
  {
    ptr.pointer_ = nullptr;
  }

  unique_ptr& operator=(const unique_ptr&) = delete;
  unique_ptr(const unique_ptr&) = delete;

  ~unique_ptr() { delete pointer_; }
};
}  // namespace steev
