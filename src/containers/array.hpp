#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
namespace steev
{
template<typename T, std::size_t Capacity>
class array
{
  class Iterator
  {
    T* ptr_;

  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    Iterator(T* ptr)
        : ptr_(ptr)
    {
    }

    // Dereference operator
    reference operator*() const { return *ptr_; }

    // Arrow operator
    pointer operator->() const { return ptr_; }

    // Addition with a difference type
    Iterator operator+(difference_type incr) const
    {
      return Iterator(ptr_ + incr);
    }

    // Subtraction with a difference type
    Iterator operator-(difference_type decr) const
    {
      return Iterator(ptr_ - decr);
    }

    // Increment operators (pre-increment and post-increment)
    Iterator& operator++()
    {
      ++ptr_;
      return *this;
    }

    Iterator operator++(int)
    {
      Iterator temp = *this;
      ++ptr_;
      return temp;
    }

    // Decrement operators (pre-decrement and post-decrement)
    Iterator& operator--()
    {
      --ptr_;
      return *this;
    }

    Iterator operator--(int)
    {
      Iterator temp = *this;
      --ptr_;
      return temp;
    }

    // Difference between two iterators
    difference_type operator-(const Iterator& other) const
    {
      return ptr_ - other.ptr_;
    }

    // Compound assignment operators
    Iterator& operator+=(difference_type incr)
    {
      ptr_ += incr;
      return *this;
    }

    Iterator& operator-=(difference_type decr)
    {
      ptr_ -= decr;
      return *this;
    }

    // Comparison operators
    bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
    bool operator<(const Iterator& other) const { return ptr_ < other.ptr_; }
    bool operator<=(const Iterator& other) const { return ptr_ <= other.ptr_; }
    bool operator>(const Iterator& other) const { return ptr_ > other.ptr_; }
    bool operator>=(const Iterator& other) const { return ptr_ >= other.ptr_; }
  };

  T data_[Capacity];

public:
  // initializer_list constructor

  array(std::initializer_list<T> list)
  {
    std::size_t i = 0;
    for (const auto& elem : list) {
      data_[i++] = elem;
    }
  }

  Iterator begin() noexcept { return data_; }
  Iterator end() noexcept { return data_[Capacity]; }

  T& at(std::size_t idx)
  {
    if (idx >= Capacity) {
      throw std::out_of_range("Index out of bounds");
    }
    return data_[idx];
  }

  T& front() noexcept { return data_; }
  T& back() noexcept { return data_[Capacity - 1]; }

  constexpr std::size_t size() const noexcept { return Capacity; }
  constexpr bool empty() const noexcept { return Capacity == 0; }
  constexpr std::size_t capacity() const noexcept { return Capacity; }
};
}  // namespace steev
