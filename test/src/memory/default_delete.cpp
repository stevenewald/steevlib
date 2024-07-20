#include "memory/default_delete.hpp"

#include <gtest/gtest.h>

class DefaultDeleteTest : public ::testing::Test
{
};

TEST_F(DefaultDeleteTest, DefaultConstructor)
{
  EXPECT_NO_THROW(steev::default_delete<int>());
}

TEST_F(DefaultDeleteTest, ConvertConstructor)
{
  steev::default_delete<int> intDeleter;
  steev::default_delete<const int> constIntDeleter(intDeleter);
  EXPECT_NO_THROW(steev::default_delete<const int>());
}

TEST_F(DefaultDeleteTest, DeletePointer)
{
  int* ptr = new int(42);
  steev::default_delete<int> deleter;
  EXPECT_NO_THROW(deleter(ptr));
}

struct Base
{
  virtual ~Base() = default;
};
struct Derived : public Base
{
};

TEST_F(DefaultDeleteTest, DeleteBasePointer)
{
  Base* basePtr = new Base();
  steev::default_delete<Base> deleter;
  EXPECT_NO_THROW(deleter(basePtr));
}

TEST_F(DefaultDeleteTest, DeleteDerivedPointerThroughBase)
{
  Derived* derivedPtr = new Derived();
  steev::default_delete<Base> deleter;
  EXPECT_NO_THROW(deleter(derivedPtr));
}
