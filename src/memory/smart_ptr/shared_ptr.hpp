#pragma once

#include <cassert>

#include "control_block.hpp"
#include "memory/default_delete.hpp"

namespace steev
{

template<typename T>
class weak_ptr;

template<typename T, typename Deleter = default_delete<T>>
class shared_ptr
{
  T* pointer;
  control_block* ctrl;
  Deleter deleter {};

public:
  shared_ptr(T* ptr)
      : pointer(ptr)
      , ctrl(make_control_block(ptr))
  {
  }

  void swap(shared_ptr& other) noexcept
  {
    std::swap(pointer, other.pointer);
    std::swap(ctrl, other.ctrl);
  }

  bool operator==(T* ptr) const noexcept { return pointer == ptr; }

  shared_ptr(shared_ptr&& other) noexcept
      : pointer(other.pointer)
      , ctrl(other.ctrl)
  {
    other.pointer = nullptr;
    other.ctrl = nullptr;
  }

  shared_ptr(const shared_ptr& other) noexcept
      : pointer(other.pointer)
      , ctrl(other.ctrl)
  {
    if (pointer != nullptr) {
      ctrl->add_ref();
    }
  }

  shared_ptr& operator=(shared_ptr&& other) noexcept
  {
    if (this != &other) {
      release();
      pointer = other.pointer;
      ctrl = other.ctrl;

      other.pointer = nullptr;
      other.ctrl = nullptr;
    }

    return *this;
  }

  shared_ptr& operator=(const shared_ptr& other) noexcept
  {
    if (this != &other) {
      release();
      pointer = other.pointer;
      ctrl = other.ctrl;

      if (pointer != nullptr) {
        ctrl->add_ref();
      }
    }

    return *this;
  }

  bool operator==(const shared_ptr& other) const noexcept
  {
    return pointer == other.pointer && ctrl == other.ctrl;
  }

  void reset(T* ptr = nullptr)
  {
    release();

    pointer = ptr;
    ctrl = make_control_block(pointer);
  }

  T& operator*() const noexcept { return *pointer; }
  T* operator->() const noexcept { return pointer; }

  T* get() const noexcept { return pointer; }

  uint32_t use_count() const
  {
    return pointer == nullptr ? 0 : ctrl->get_refs();
  }

  shared_ptr()
      : pointer(nullptr)
      , ctrl(nullptr)
  {
  }

  ~shared_ptr() noexcept { release(); }

private:
  static control_block* make_control_block(T* pointer)
  {
    if (pointer == nullptr) {
      return nullptr;
    }
    return new control_block {};
  }
  void release() noexcept
  {
    assert(!pointer == !ctrl);

    if (pointer == nullptr) {
      return;
    }

    if (ctrl->remove_ref() == 0) {
      deleter(pointer);
    }

    pointer = nullptr;
    ctrl = nullptr;
  }

  friend class weak_ptr<T>;
};

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args... args)
{
  return shared_ptr<T>(new T(std::forward<Args...>(args...)));
}

template<typename T>
shared_ptr<T> make_shared()
{
  return shared_ptr<T>(new T {});
}

}  // namespace steev
