#pragma once

#include "memory/default_delete.hpp"

namespace steev
{

template<typename T, typename Deleter = steev::default_delete<T>>
class unique_ptr
{
  T* pointer_;
  [[no_unique_address]] Deleter deleter_ {};

public:
  explicit unique_ptr(T* ptr = nullptr)
      : pointer_(ptr)
  {
  }

  Deleter& get_deleter() { return deleter_; }

  unique_ptr& operator=(T* ptr)
  {
    reset();
    pointer_ = ptr;
    return *this;
  }

  unique_ptr& operator=(unique_ptr&& ptr) noexcept
  {
    pointer_ = ptr.pointer_;
    ptr.pointer_ = nullptr;
    return *this;
  }

  const T& operator[](std::size_t index) const { return pointer_[index]; }
  T& operator[](std::size_t index) { return pointer_[index]; }

  unique_ptr(unique_ptr&& ptr) noexcept
      : pointer_(ptr.pointer_)
  {
    ptr.pointer_ = nullptr;
  }

  T* operator->() { return pointer_; }
  T* get() { return pointer_; }

  explicit operator bool() const noexcept { return pointer_ != nullptr; }

  unique_ptr& operator=(const unique_ptr&) = delete;
  unique_ptr(const unique_ptr&) = delete;

  T& operator*() { return *pointer_; }

  bool operator==(const T* other) const { return pointer_ == other; }

  void swap(unique_ptr& other) noexcept
  {
    T* tmp = pointer_;
    pointer_ = other.pointer_;
    other.pointer_ = tmp;
  }

  void reset(T* new_ptr = nullptr) noexcept
  {
    if (pointer_ != new_ptr) {
      if (pointer_) {
        deleter_(pointer_);
      }
      pointer_ = new_ptr;
    }
  }

  T* release() noexcept
  {
    T* tmp = pointer_;
    pointer_ = nullptr;
    return tmp;
  }

  ~unique_ptr() { reset(); }
};

template<typename T, typename Deleter>
class unique_ptr<T[], Deleter>
{
  T* pointer_;
  Deleter deleter_ {};

public:
  explicit unique_ptr(T* ptr)
      : pointer_(ptr)
  {
  }

  Deleter& get_deleter() { return deleter_; }

  unique_ptr()
      : pointer_ {nullptr}
  {
  }

  unique_ptr& operator=(unique_ptr&& ptr) noexcept
  {
    pointer_ = ptr.pointer_;
    ptr.pointer_ = nullptr;
    return *this;
  }

  const T& operator[](std::size_t index) const { return pointer_[index]; }
  T& operator[](std::size_t index) { return pointer_[index]; }

  unique_ptr(unique_ptr&& ptr) noexcept
      : pointer_(ptr.pointer_)
  {
    ptr.pointer_ = nullptr;
  }

  T* operator->() { return pointer_; }
  T* get() { return pointer_; }

  explicit operator bool() const noexcept { return pointer_ != nullptr; }

  unique_ptr& operator=(const unique_ptr&) = delete;
  unique_ptr(const unique_ptr&) = delete;

  T& operator*() { return *pointer_; }

  bool operator==(const T* other) const { return pointer_ == other; }

  void swap(unique_ptr& other) noexcept
  {
    T* tmp = pointer_;
    pointer_ = other.pointer_;
    other.pointer_ = tmp;
  }

  void reset(T* new_ptr = nullptr) noexcept
  {
    if (pointer_ != new_ptr) {
      if (pointer_) {
        deleter_(pointer_);
      }
      pointer_ = new_ptr;
    }
  }

  T* release() noexcept
  {
    T* tmp = pointer_;
    pointer_ = nullptr;
    return tmp;
  }

  ~unique_ptr() { reset(); }
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args... args)
{
  return unique_ptr<T>(new T {std::forward<Args>(args)...});
}

template<typename T>
unique_ptr<T> make_unique()
{
  return unique_ptr<T>(new T {});
}
}  // namespace steev
