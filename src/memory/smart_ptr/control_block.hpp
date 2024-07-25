#pragma once

#include <atomic>

namespace steev
{

class control_block
{
  std::atomic<uint32_t> strong_count {1};
  std::atomic<uint32_t> weak_count {0};

public:
  uint32_t get_refs() const noexcept { return strong_count; }
  uint32_t get_weak_refs() const noexcept { return strong_count; }

  void add_ref() noexcept { strong_count++; }

  uint32_t remove_ref() noexcept
  {
    uint32_t new_strong_count = --strong_count;

    if (new_strong_count == 0 && weak_count == 0) {
      delete this;
    }
    return new_strong_count;
  }

  void add_weak_ref() noexcept { weak_count++; }

  void remove_weak_ref() noexcept
  {
    if (--weak_count == 0 && strong_count == 0) {
      delete this;
    }
  }
};
}  // namespace steev
