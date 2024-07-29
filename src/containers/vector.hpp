#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

namespace steev
{
template<typename T>
class vector
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

  std::size_t size_;
  std::size_t capacity_;
  T* data;

  void reallocate(std::size_t new_size)
  {
    data = static_cast<int*>(realloc(data, sizeof(T) * new_size));
    capacity_ = new_size;
  }

public:
  vector()
      : size_(0)
      , capacity_(10)
      , data(new T[10])
  {
  }

  std::size_t capacity() { return capacity_; }

  const T& operator[](std::size_t index) const { return data[index]; }
  T& operator[](std::size_t index) { return data[index]; }

  void resize(std::size_t new_size)
  {
    if (capacity_ == new_size) {
      return;
    }

    std::size_t old_capacity = capacity_;
    reallocate(new_size);
    size_ = new_size;

    if (old_capacity < new_size) {
      for (std::size_t i = old_capacity; i < new_size; i++) {
        data[i] = T {};
      }
    }
  }

  void push_back(T&& element)
  {
    if (size_ == capacity_) {
      reallocate(capacity_ * 2);
    }
    data[size_++] = element;
  }

  void pop_back()
  {
    if (size_ == 0) {
      throw std::runtime_error("Unable to pop vector with 0 elements");
    }
    size_--;
  }

  Iterator insert(Iterator it, T&& element)
  {
    if (size_ + 1 == capacity_) {
      reallocate(capacity_ * 2);
    }

    std::copy_backward(it,
                       begin() + static_cast<std::ptrdiff_t>(size_),
                       begin() + static_cast<std::ptrdiff_t>(size_) + 1);
    *it = element;
    ++size_;
    return it;
  }

  vector(std::initializer_list<T> elements)
      : size_(elements.size())
      , capacity_(elements.size())
      , data(new T[elements.size()])
  {
    size_t i = 0;
    for (auto it = elements.begin(); it != elements.end(); it++) {
      data[i++] = *it;
    }
  }

  explicit vector(std::size_t initial_size) noexcept
      : size_(initial_size)
      , capacity_(initial_size)
      , data(new T[initial_size])
  {
    for (T* ptr = data; ptr < data + initial_size; ptr++) {
      data[ptr] = {};
    }
  }

  explicit vector(std::size_t initial_size, T&& initial_element) noexcept
      : vector(initial_size)
  {
    for (T* ptr = data; ptr < data + initial_size; ptr++) {
      data[ptr] = initial_element;
    }
  }

  vector(vector&& other) noexcept
      : size_(other.size)
      , capacity_(other.capacity)
      , data(other.data)
  {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data = nullptr;
  }

  vector(const vector& other) noexcept
      : size_(other.size_)
      , capacity_(other.capacity_)
      , data(new T[other.capacity_])
  {
    memcpy(data, other.data, capacity_);
  }

  vector& operator=(vector&& other) noexcept
  {
    if (this != &other) {
      size_ = other.size_;
      capacity_ = other.capacity_;
      data = other.data;

      other.size_ = 0;
      other.capacity_ = 0;
      other.data = nullptr;
    }

    return *this;
  }

  vector& operator=(const vector& other) noexcept
  {
    if (this != &other) {
      size_ = other.size_;
      capacity_ = other.capacity_;
      data = new T[capacity_];
      memcpy(data, other.data, other.capacity);
    }

    return *this;
  }

  Iterator begin() { return data; }
  Iterator end() { return data + capacity_; }

  T& at(std::size_t idx)
  {
    if (idx >= capacity_) {
      throw std::out_of_range("Index out of bounds");
    }
    return data[idx];
  }

  T& front() { return data[0]; }
  T& back() { return data[size_ - 1]; }

  std::size_t size() const { return size_; }

  ~vector() { delete[] data; }
};
}  // namespace steev
