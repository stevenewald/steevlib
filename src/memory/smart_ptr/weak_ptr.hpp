#pragma once

#include "control_block.hpp"
#include "shared_ptr.hpp"

namespace steev
{
template<typename T>
class weak_ptr
{
  T* pointer;
  control_block* ctrl;

public:
  weak_ptr(const shared_ptr<T>& other) noexcept
      : pointer(other.get())
      , ctrl(other.ctrl)
  {
    if (pointer != nullptr) {
      ctrl->add_weak_ref();
    }
  }

  void swap(weak_ptr& other) noexcept
  {
    std::swap(pointer, other.pointer);
    std::swap(ctrl, other.ctrl);
  }

  weak_ptr(const weak_ptr& other) noexcept
      : pointer(other.pointer)
      , ctrl(other.ctrl)
  {
    if (pointer != nullptr) {
      ctrl->add_weak_ref();
    }
  }

  weak_ptr(weak_ptr&& other) noexcept
      : pointer(other.pointer)
      , ctrl(other.ctrl)
  {
    other.pointer = nullptr;
    other.ctrl = nullptr;
  }

  weak_ptr& operator=(weak_ptr&& other) noexcept
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

  weak_ptr& operator=(const weak_ptr& other) noexcept
  {
    if (this != &other) {
      release();
      pointer = other.pointer;
      ctrl = other.ctrl;
      if (pointer != nullptr) {
        ctrl->add_weak_ref();
      }
    }
    return *this;
  }

  void reset() noexcept { release(); }

  bool operator==(const weak_ptr& other) const noexcept
  {
    return pointer == other.pointer && ctrl == other.ctrl;
  }

  ~weak_ptr() noexcept { release(); }

  uint32_t use_count() const noexcept
  {
    return pointer == nullptr ? 0 : ctrl->get_refs();
  }

  shared_ptr<T> lock() const noexcept
  {
    if (expired()) {
      return nullptr;
    };

    shared_ptr<T> shared;
    shared.pointer = pointer;
    shared.ctrl = ctrl;

    ctrl->add_ref();

    return shared;
  }

  bool operator==(T* ptr) const noexcept { return pointer == ptr; }

  bool expired() const noexcept
  {
    if (pointer == nullptr) {
      return true;
    }
    return ctrl->get_refs() == 0;
  }

private:
  void release() noexcept
  {
    if (pointer != nullptr) {
      ctrl->remove_weak_ref();
      pointer = nullptr;
    }
  }
};
}  // namespace steev
