#include "memory/smart_ptr/weak_ptr.hpp"

#include <gtest/gtest.h>

#include "memory/smart_ptr/shared_ptr.hpp"

// Test construction and assignment
TEST(WeakPtrTest, ConstructionAndAssignment)
{
  steev::shared_ptr<int> sp1(new int(10));
  steev::weak_ptr<int> wp1(sp1);
  EXPECT_EQ(wp1.use_count(), 1);
  EXPECT_FALSE(wp1.expired());

  steev::shared_ptr<int> sp2 = wp1.lock();
  EXPECT_EQ(*sp2, 10);
  EXPECT_EQ(wp1.use_count(), 2);

  steev::weak_ptr<int> wp2(wp1);
  EXPECT_EQ(wp2.use_count(), 2);
  EXPECT_FALSE(wp2.expired());

  sp1.reset();
  EXPECT_EQ(wp1.use_count(), 1);
  EXPECT_FALSE(wp1.expired());
  EXPECT_FALSE(wp2.expired());

  sp2.reset();
  EXPECT_EQ(wp1.use_count(), 0);
  EXPECT_TRUE(wp1.expired());
  EXPECT_TRUE(wp2.expired());
}
// Test expired
TEST(WeakPtrTest, Expired)
{
  steev::shared_ptr<int> sp(new int(20));
  steev::weak_ptr<int> wp(sp);
  EXPECT_FALSE(wp.expired());

  sp.reset();
  EXPECT_TRUE(wp.expired());
}

// Test lock
TEST(WeakPtrTest, Lock)
{
  steev::shared_ptr<int> sp(new int(30));
  steev::weak_ptr<int> wp(sp);
  auto sp2 = wp.lock();
  EXPECT_EQ(*sp2, 30);
  EXPECT_EQ(sp2.use_count(), 2);

  sp.reset();
  steev::shared_ptr<int> sp3 = wp.lock();
  EXPECT_NE(sp3.get(), nullptr);

  sp2.reset();
  sp3.reset();

  steev::shared_ptr<int> sp4 = wp.lock();
  EXPECT_EQ(sp4.get(), nullptr);
}
// Test use_count
TEST(WeakPtrTest, UseCount) {
    steev::shared_ptr<int> sp1(new int(40));
    steev::weak_ptr<int> wp1(sp1);
    EXPECT_EQ(wp1.use_count(), 1);

    steev::shared_ptr<int> sp2 = wp1.lock();
    EXPECT_EQ(wp1.use_count(), 2);

    sp2.reset();
    EXPECT_EQ(wp1.use_count(), 1);

    sp1.reset();
    EXPECT_EQ(wp1.use_count(), 0);
}

// Test reset
TEST(WeakPtrTest, Reset) {
    steev::shared_ptr<int> sp(new int(50));
    steev::weak_ptr<int> wp(sp);
    wp.reset();
    EXPECT_EQ(wp.use_count(), 0);
    EXPECT_TRUE(wp.expired());
    EXPECT_EQ(wp.lock(), nullptr);
}

// Test swap
TEST(WeakPtrTest, Swap) {
    steev::shared_ptr<int> sp1(new int(60));
    steev::shared_ptr<int> sp2(new int(70));
    steev::weak_ptr<int> wp1(sp1);
    steev::weak_ptr<int> wp2(sp2);
    wp1.swap(wp2);
    EXPECT_EQ(wp1.lock(), sp2);
    EXPECT_EQ(wp2.lock(), sp1);
}

