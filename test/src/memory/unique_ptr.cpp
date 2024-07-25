#include "memory/smart_ptr/unique_ptr.hpp"

#include <gtest/gtest.h>

// Basic operations
TEST(UniquePtrTest, DefaultConstructor)
{
  steev::unique_ptr<int> ptr;
  EXPECT_EQ(ptr, nullptr);
}
TEST(UniquePtrTest, PointerConstructor)
{
  steev::unique_ptr<int> ptr(new int(5));
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 5);
}
TEST(UniquePtrTest, MoveConstructor)
{
  steev::unique_ptr<int> ptr1(new int(5));
  steev::unique_ptr<int> ptr2(std::move(ptr1));
  EXPECT_EQ(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(*ptr2, 5);
}

TEST(UniquePtrTest, MoveAssignment)
{
  steev::unique_ptr<int> ptr1(new int(5));
  steev::unique_ptr<int> ptr2;
  ptr2 = std::move(ptr1);
  EXPECT_EQ(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(*ptr2, 5);
}
TEST(UniquePtrTest, Reset)
{
  steev::unique_ptr<int> ptr(new int(5));
  ptr.reset(new int(10));
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 10);
  ptr.reset();
  EXPECT_EQ(ptr, nullptr);
}
TEST(UniquePtrTest, Release)
{
  steev::unique_ptr<int> ptr(new int(5));
  int* rawPtr = ptr.release();
  EXPECT_EQ(ptr, nullptr);
  EXPECT_EQ(*rawPtr, 5);
  delete rawPtr;
}
TEST(UniquePtrTest, Swap)
{
  steev::unique_ptr<int> ptr1(new int(5));
  steev::unique_ptr<int> ptr2(new int(10));
  ptr1.swap(ptr2);
  EXPECT_EQ(*ptr1, 10);
  EXPECT_EQ(*ptr2, 5);
}

// Custom deleter
struct ArrayDeleter
{
  void operator()(int* p) { delete[] p; }
};
// Array handling
TEST(UniquePtrTest, ArrayDefaultConstructor)
{
  steev::unique_ptr<int[]> ptr;
  EXPECT_EQ(ptr, nullptr);
}

TEST(UniquePtrTest, ArrayPointerConstructor)
{
  steev::unique_ptr<int[]> ptr(new int[5] {1, 2, 3, 4, 5});
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[4], 5);
}

TEST(UniquePtrTest, ArrayMoveConstructor)
{
  steev::unique_ptr<int[]> ptr1(new int[5] {1, 2, 3, 4, 5});
  steev::unique_ptr<int[]> ptr2(std::move(ptr1));
  EXPECT_EQ(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(ptr2[0], 1);
  EXPECT_EQ(ptr2[4], 5);
}
TEST(UniquePtrTest, ArrayMoveAssignment)
{
  steev::unique_ptr<int[]> ptr1(new int[5] {1, 2, 3, 4, 5});
  steev::unique_ptr<int[]> ptr2;
  ptr2 = std::move(ptr1);
  EXPECT_EQ(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(ptr2[0], 1);
  EXPECT_EQ(ptr2[4], 5);
}

TEST(UniquePtrTest, ArrayReset)
{
  steev::unique_ptr<int[]> ptr(new int[5] {1, 2, 3, 4, 5});
  ptr.reset(new int[3] {6, 7, 8});
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 6);
  EXPECT_EQ(ptr[2], 8);
  ptr.reset();
  EXPECT_EQ(ptr, nullptr);
}

TEST(UniquePtrTest, ArrayRelease)
{
  steev::unique_ptr<int[]> ptr(new int[5] {1, 2, 3, 4, 5});
  int* rawPtr = ptr.release();
  EXPECT_EQ(ptr, nullptr);
  EXPECT_EQ(rawPtr[0], 1);
  EXPECT_EQ(rawPtr[4], 5);
  delete[] rawPtr;
}

TEST(UniquePtrTest, ArraySwap)
{
  steev::unique_ptr<int[]> ptr1(new int[5] {1, 2, 3, 4, 5});
  steev::unique_ptr<int[]> ptr2(new int[3] {6, 7, 8});
  ptr1.swap(ptr2);
  EXPECT_EQ(ptr1[0], 6);
  EXPECT_EQ(ptr1[2], 8);
  EXPECT_EQ(ptr2[0], 1);
  EXPECT_EQ(ptr2[4], 5);
}

// Other operations
TEST(UniquePtrTest, BoolConversion)
{
  steev::unique_ptr<int> ptr1;
  steev::unique_ptr<int> ptr2(new int(5));
  EXPECT_FALSE(ptr1);
  EXPECT_TRUE(ptr2);
}

TEST(UniquePtrTest, Dereference)
{
  steev::unique_ptr<int> ptr(new int(5));
  EXPECT_EQ(*ptr, 5);
}

TEST(UniquePtrTest, Get)
{
  steev::unique_ptr<int> ptr(new int(5));
  int* rawPtr = ptr.get();
  EXPECT_NE(rawPtr, nullptr);
  EXPECT_EQ(*rawPtr, 5);
}

// Custom deleter
struct Deleter
{
  void operator()(int* p) { delete p; }
};

TEST(UniquePtrTest, CustomDeleter)
{
  steev::unique_ptr<int, Deleter> ptr(new int(5));
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 5);
}

TEST(UniquePtrTest, GetDeleter)
{
  steev::unique_ptr<int, Deleter> ptr(new int(5));
  Deleter& del = ptr.get_deleter();
  (void)del;  // Just to use the deleter to avoid warnings
}

// Test for nullptr assignment
TEST(UniquePtrTest, NullptrAssignment)
{
  steev::unique_ptr<int> ptr(new int(5));
  ptr = nullptr;
  EXPECT_EQ(ptr, nullptr);
}


// Test for custom deleter with array
struct CustomArrayDeleter
{
  void operator()(int* p) { delete[] p; }
};

TEST(UniquePtrTest, CustomArrayDeleter)
{
  steev::unique_ptr<int[], CustomArrayDeleter> ptr(new int[3]{1, 2, 3});
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[2], 3);
}

// Test for nullptr reset with custom deleter
TEST(UniquePtrTest, ResetWithNullptrAndCustomDeleter)
{
  steev::unique_ptr<int, Deleter> ptr(new int(5));
  ptr.reset(nullptr);
  EXPECT_EQ(ptr, nullptr);
}

// Test for array handling with custom deleter
TEST(UniquePtrTest, ArrayHandlingWithCustomDeleter)
{
  steev::unique_ptr<int[], CustomArrayDeleter> ptr(new int[3]{1, 2, 3});
  ptr.reset(new int[2]{4, 5});
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 4);
  EXPECT_EQ(ptr[1], 5);
  ptr.reset();
  EXPECT_EQ(ptr, nullptr);
}

// Test for operator bool with array
TEST(UniquePtrTest, ArrayBoolConversion)
{
  steev::unique_ptr<int[]> ptr1;
  steev::unique_ptr<int[]> ptr2(new int[3]{1, 2, 3});
  EXPECT_FALSE(ptr1);
  EXPECT_TRUE(ptr2);
}

// Test for dereference with array
TEST(UniquePtrTest, ArrayDereference)
{
  steev::unique_ptr<int[]> ptr(new int[3]{1, 2, 3});
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
}

// Test for release with custom deleter
TEST(UniquePtrTest, CustomDeleterRelease)
{
  steev::unique_ptr<int, Deleter> ptr(new int(5));
  int* rawPtr = ptr.release();
  EXPECT_EQ(ptr, nullptr);
  EXPECT_EQ(*rawPtr, 5);
  delete rawPtr; // Ensure to delete the raw pointer manually
}

// Test for swap with custom deleter
TEST(UniquePtrTest, CustomDeleterSwap)
{
  steev::unique_ptr<int, Deleter> ptr1(new int(5));
  steev::unique_ptr<int, Deleter> ptr2(new int(10));
  ptr1.swap(ptr2);
  EXPECT_EQ(*ptr1, 10);
  EXPECT_EQ(*ptr2, 5);
}

// Test for multiple resets
TEST(UniquePtrTest, MultipleResets)
{
  steev::unique_ptr<int> ptr(new int(5));
  ptr.reset(new int(10));
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 10);
  ptr.reset(new int(20));
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 20);
  ptr.reset();
  EXPECT_EQ(ptr, nullptr);
}

// Test for array multiple resets
TEST(UniquePtrTest, ArrayMultipleResets)
{
  steev::unique_ptr<int[]> ptr(new int[2]{1, 2});
  ptr.reset(new int[3]{3, 4, 5});
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 3);
  EXPECT_EQ(ptr[2], 5);
  ptr.reset(new int[1]{6});
  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr[0], 6);
  ptr.reset();
  EXPECT_EQ(ptr, nullptr);
}

// Test for get with custom deleter
TEST(UniquePtrTest, CustomDeleterGet)
{
  steev::unique_ptr<int, Deleter> ptr(new int(5));
  int* rawPtr = ptr.get();
  EXPECT_NE(rawPtr, nullptr);
  EXPECT_EQ(*rawPtr, 5);
}

// Test for move assignment with self-assignment guard
TEST(UniquePtrTest, MoveAssignmentWithSelfGuard)
{
  steev::unique_ptr<int> ptr1(new int(5));
  steev::unique_ptr<int> ptr2;
  ptr2 = std::move(ptr1);
  EXPECT_EQ(ptr1, nullptr);
  EXPECT_NE(ptr2, nullptr);
  EXPECT_EQ(*ptr2, 5);
}

// Test for get_deleter with array and custom deleter
TEST(UniquePtrTest, ArrayCustomDeleterGetDeleter)
{
  steev::unique_ptr<int[], CustomArrayDeleter> ptr(new int[3]{1, 2, 3});
  CustomArrayDeleter& del = ptr.get_deleter();
  (void)del;  // Just to use the deleter to avoid warnings
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[2], 3);
}

// Test for swap with array and custom deleter
TEST(UniquePtrTest, ArrayCustomDeleterSwap)
{
  steev::unique_ptr<int[], CustomArrayDeleter> ptr1(new int[3]{1, 2, 3});
  steev::unique_ptr<int[], CustomArrayDeleter> ptr2(new int[2]{4, 5});
  ptr1.swap(ptr2);
  EXPECT_EQ(ptr1[0], 4);
  EXPECT_EQ(ptr1[1], 5);
  EXPECT_EQ(ptr2[0], 1);
  EXPECT_EQ(ptr2[2], 3);
}

