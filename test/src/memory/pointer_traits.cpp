#include "memory/pointer_traits.hpp"

#include <gtest/gtest.h>

// Custom pointer type for testing
template<typename T>
class CustomPtr
{
public:
  CustomPtr(T* ptr)
      : ptr_(ptr)
  {
  }

  T* operator->() { return ptr_; }
  T& operator*() { return *ptr_; }

  operator T*() const { return ptr_; }  // Implicit conversion

private:
  T* ptr_;
};

// steev::pointer_traits specialization for CustomPtr
namespace steev
{
template<typename T>
struct pointer_traits<CustomPtr<T>>
{
  using pointer = CustomPtr<T>;
  using element_type = T;
  using difference_type = std::ptrdiff_t;

  static pointer pointer_to(T& r) { return CustomPtr<T>(&r); }

  template<typename U>
  using rebind = CustomPtr<U>;
};
}  // namespace steev

// Basic test for steev::pointer_traits::element_type
TEST(PointerTraitsTest, ElementType)
{
  static_assert(std::is_same_v<steev::pointer_traits<int*>::element_type, int>,
                "Element type mismatch");
  static_assert(
      std::is_same_v<steev::pointer_traits<CustomPtr<int>>::element_type, int>,
      "Element type mismatch");
}

// Basic test for steev::pointer_traits::pointer_to
TEST(PointerTraitsTest, PointerTo)
{
  int value = 42;

  auto ptr = steev::pointer_traits<int*>::pointer_to(value);
  EXPECT_EQ(ptr, &value);

  auto customPtr = steev::pointer_traits<CustomPtr<int>>::pointer_to(value);
  EXPECT_EQ(*customPtr, value);
}

// Test for steev::pointer_traits::difference_type
TEST(PointerTraitsTest, DifferenceType)
{
  static_assert(std::is_same_v<steev::pointer_traits<int*>::difference_type,
                               std::ptrdiff_t>,
                "Difference type mismatch");
  static_assert(
      std::is_same_v<steev::pointer_traits<CustomPtr<int>>::difference_type,
                     std::ptrdiff_t>,
      "Difference type mismatch");
}

// Test implicit conversion via pointer_traits::rebind
TEST(PointerTraitsTest, Rebind)
{
  using ReboundPtr = steev::pointer_traits<int*>::rebind<double>;
  static_assert(std::is_same_v<ReboundPtr, double*>, "Rebound type mismatch");

  using ReboundCustomPtr =
      steev::pointer_traits<CustomPtr<int>>::rebind<double>;
  static_assert(std::is_same_v<ReboundCustomPtr, CustomPtr<double>>,
                "Rebound custom pointer type mismatch");
}

// Test for nullptr interaction
TEST(PointerTraitsTest, NullPointer)
{
  int* nullPtr = nullptr;
  EXPECT_EQ(nullPtr, static_cast<int*>(nullptr));

  CustomPtr<int> customNullPtr(nullptr);
  EXPECT_EQ(customNullPtr, static_cast<int*>(nullptr));
}

// Test for pointer arithmetic (with raw pointers only)
TEST(PointerTraitsTest, PointerArithmetic)
{
  int arr[] = {1, 2, 3, 4, 5};
  int* ptr1 = &arr[0];
  int* ptr2 = &arr[2];

  EXPECT_EQ(ptr2 - ptr1, 2);
  EXPECT_EQ(ptr1 + 3, &arr[3]);
}

// Test for pointer_to for different types
TEST(PointerTraitsTest, PointerToDifferentTypes)
{
  double value = 3.14;

  auto ptr = steev::pointer_traits<double*>::pointer_to(value);
  EXPECT_EQ(ptr, &value);

  auto customPtr = steev::pointer_traits<CustomPtr<double>>::pointer_to(value);
  EXPECT_EQ(*customPtr, value);
}

// Test for steev::pointer_traits::rebind and custom pointer
TEST(PointerTraitsTest, CustomPointerRebind)
{
  using ReboundPtr = steev::pointer_traits<CustomPtr<int>>::rebind<float>;
  float value = 1.23f;

  ReboundPtr reboundPtr =
      steev::pointer_traits<CustomPtr<float>>::pointer_to(value);
  EXPECT_EQ(*reboundPtr, value);
}

// Test custom pointer dereference
TEST(PointerTraitsTest, CustomPointerDereference)
{
  int value = 99;
  CustomPtr<int> customPtr(&value);

  EXPECT_EQ(*customPtr, value);
  EXPECT_EQ(customPtr.operator->(), &value);
}
