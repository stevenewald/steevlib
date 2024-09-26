#include <stdexcept>

#include "containers/vector.hpp"

#include <gtest/gtest.h>

class VectorTest : public ::testing::Test
{
protected:
  steev::vector<int> vec;

  void SetUp() override { vec = {1, 2, 3, 4, 5}; }
};

// Size and Capacity Tests
TEST_F(VectorTest, Size)
{
  EXPECT_EQ(vec.size(), 5);
}

TEST_F(VectorTest, Capacity)
{
  EXPECT_GE(vec.capacity(), 5);
}

TEST_F(VectorTest, Empty)
{
  vec.clear();
  EXPECT_TRUE(vec.empty());
  vec.push_back(1);
  EXPECT_FALSE(vec.empty());
  vec.pop_back();
  EXPECT_TRUE(vec.empty());
}

TEST_F(VectorTest, ResizeLarger)
{
  vec.resize(10);
  EXPECT_EQ(vec.size(), 10);
  EXPECT_EQ(vec[5], 0);
}

TEST_F(VectorTest, ResizeSmaller)
{
  vec.resize(3);
  EXPECT_EQ(vec.size(), 3);
}
// Element Access Tests
TEST_F(VectorTest, AccessElements)
{
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec.at(1), 2);
  EXPECT_EQ(vec.front(), 1);
  EXPECT_EQ(vec.back(), 5);
}

TEST_F(VectorTest, AccessOutOfBounds)
{
  EXPECT_THROW(int test = vec.at(10); test++, std::out_of_range);
}

// Modifiers Tests
TEST_F(VectorTest, PushBack)
{
  vec.push_back(6);
  EXPECT_EQ(vec.back(), 6);
  EXPECT_EQ(vec.size(), 6);
}

TEST_F(VectorTest, PopBack)
{
  vec.pop_back();
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec.back(), 4);
}

TEST_F(VectorTest, Insert)
{
  auto it = vec.insert(vec.begin() + static_cast<std::ptrdiff_t>(2), 10);
  EXPECT_EQ(*it, 10);
  EXPECT_EQ(vec[2], 10);
  EXPECT_EQ(vec.size(), 6);
}

TEST_F(VectorTest, Erase)
{
  auto it = vec.erase(vec.begin() + 1);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec.size(), 4);
}

TEST_F(VectorTest, Clear)
{
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

TEST_F(VectorTest, Assign)
{
  vec.assign(7, 100);
  EXPECT_EQ(vec.size(), 7);
  EXPECT_EQ(vec[0], 100);
  EXPECT_EQ(vec.back(), 100);
}

// Iterator Tests
TEST_F(VectorTest, IterateWithRangeBasedForLoop)
{
  int sum = 0;
  for (const auto& val : vec) {
    sum += val;
  }
  EXPECT_EQ(sum, 15);
}

TEST_F(VectorTest, IteratorBeginEnd)
{
  auto it = vec.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

// Capacity Tests
TEST_F(VectorTest, Reserve)
{
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

TEST_F(VectorTest, ShrinkToFit)
{
  vec.reserve(10);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

// Relational Operators Tests
TEST_F(VectorTest, Equality)
{
  steev::vector<int> otherVec = {1, 2, 3, 4, 5};
  EXPECT_EQ(vec, otherVec);
}

TEST_F(VectorTest, Inequality)
{
  steev::vector<int> otherVec = {1, 2, 3, 4};
  EXPECT_NE(vec, otherVec);
}

TEST_F(VectorTest, LessThan)
{
  steev::vector<int> otherVec = {1, 2, 3, 4, 6};
  EXPECT_LT(vec, otherVec);
}

// Swap Test
TEST_F(VectorTest, Swap)
{
  steev::vector<int> otherVec = {10, 20, 30};
  vec.swap(otherVec);
  EXPECT_EQ(vec, (steev::vector<int> {10, 20, 30}));
  EXPECT_EQ(otherVec, (steev::vector<int> {1, 2, 3, 4, 5}));
}
// Move Semantics Tests
TEST(VectorMoveTest, MoveConstructor)
{
  std::vector<int> source = {1, 2, 3};
  std::vector<int> target = std::move(source);
  EXPECT_EQ(target, (std::vector<int> {1, 2, 3}));
  EXPECT_TRUE(source.empty());
}

TEST(VectorMoveTest, MoveAssignment)
{
  std::vector<int> source = {1, 2, 3};
  std::vector<int> target;
  target = std::move(source);
  EXPECT_EQ(target, (std::vector<int> {1, 2, 3}));
  EXPECT_TRUE(source.empty());
}
