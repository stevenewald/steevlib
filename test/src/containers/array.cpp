#include <stdexcept>

#include "containers/array.hpp"

#include <gtest/gtest.h>

class ArrayTest : public ::testing::Test
{
protected:
  steev::array<int, 5> vec = {1, 2, 3, 4, 5};
};

// Size and Capacity Tests
TEST_F(ArrayTest, Size)
{
  EXPECT_EQ(vec.size(), 5);
}

TEST_F(ArrayTest, Capacity)
{
  EXPECT_GE(vec.capacity(), 5);
}
