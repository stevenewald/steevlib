#include "memory/unique_ptr.hpp"

#include <gtest/gtest.h>

// Basic operations
TEST(UniquePtrTest, DefaultConstructor) {
    std::unique_ptr<int> ptr;
    EXPECT_EQ(ptr, nullptr);
}

TEST(UniquePtrTest, PointerConstructor) {
    std::unique_ptr<int> ptr(new int(5));
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 5);
}

TEST(UniquePtrTest, MoveConstructor) {
    std::unique_ptr<int> ptr1(new int(5));
    std::unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(*ptr2, 5);
}

TEST(UniquePtrTest, MoveAssignment) {
    std::unique_ptr<int> ptr1(new int(5));
    std::unique_ptr<int> ptr2;
    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(*ptr2, 5);
}

TEST(UniquePtrTest, Reset) {
    std::unique_ptr<int> ptr(new int(5));
    ptr.reset(new int(10));
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 10);
    ptr.reset();
    EXPECT_EQ(ptr, nullptr);
}

TEST(UniquePtrTest, Release) {
    std::unique_ptr<int> ptr(new int(5));
    int* rawPtr = ptr.release();
    EXPECT_EQ(ptr, nullptr);
    EXPECT_EQ(*rawPtr, 5);
    delete rawPtr;
}

TEST(UniquePtrTest, Swap) {
    std::unique_ptr<int> ptr1(new int(5));
    std::unique_ptr<int> ptr2(new int(10));
    ptr1.swap(ptr2);
    EXPECT_EQ(*ptr1, 10);
    EXPECT_EQ(*ptr2, 5);
}

// Custom deleter
struct Deleter {
    void operator()(int* p) {
        delete p;
    }
};

TEST(UniquePtrTest, CustomDeleter) {
    std::unique_ptr<int, Deleter> ptr(new int(5));
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 5);
}

// Array handling
TEST(UniquePtrTest, ArrayDefaultConstructor) {
    std::unique_ptr<int[]> ptr;
    EXPECT_EQ(ptr, nullptr);
}

TEST(UniquePtrTest, ArrayPointerConstructor) {
    std::unique_ptr<int[]> ptr(new int[5]{1, 2, 3, 4, 5});
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 1);
    EXPECT_EQ(ptr[4], 5);
}

TEST(UniquePtrTest, ArrayMoveConstructor) {
    std::unique_ptr<int[]> ptr1(new int[5]{1, 2, 3, 4, 5});
    std::unique_ptr<int[]> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(ptr2[0], 1);
    EXPECT_EQ(ptr2[4], 5);
}

TEST(UniquePtrTest, ArrayMoveAssignment) {
    std::unique_ptr<int[]> ptr1(new int[5]{1, 2, 3, 4, 5});
    std::unique_ptr<int[]> ptr2;
    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_EQ(ptr2[0], 1);
    EXPECT_EQ(ptr2[4], 5);
}

TEST(UniquePtrTest, ArrayReset) {
    std::unique_ptr<int[]> ptr(new int[5]{1, 2, 3, 4, 5});
    ptr.reset(new int[3]{6, 7, 8});
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 6);
    EXPECT_EQ(ptr[2], 8);
    ptr.reset();
    EXPECT_EQ(ptr, nullptr);
}

TEST(UniquePtrTest, ArrayRelease) {
    std::unique_ptr<int[]> ptr(new int[5]{1, 2, 3, 4, 5});
    int* rawPtr = ptr.release();
    EXPECT_EQ(ptr, nullptr);
    EXPECT_EQ(rawPtr[0], 1);
    EXPECT_EQ(rawPtr[4], 5);
    delete[] rawPtr;
}

TEST(UniquePtrTest, ArraySwap) {
    std::unique_ptr<int[]> ptr1(new int[5]{1, 2, 3, 4, 5});
    std::unique_ptr<int[]> ptr2(new int[3]{6, 7, 8});
    ptr1.swap(ptr2);
    EXPECT_EQ(ptr1[0], 6);
    EXPECT_EQ(ptr1[2], 8);
    EXPECT_EQ(ptr2[0], 1);
    EXPECT_EQ(ptr2[4], 5);
}

// Other operations
TEST(UniquePtrTest, BoolConversion) {
    std::unique_ptr<int> ptr1;
    std::unique_ptr<int> ptr2(new int(5));
    EXPECT_FALSE(ptr1);
    EXPECT_TRUE(ptr2);
}

TEST(UniquePtrTest, Dereference) {
    std::unique_ptr<int> ptr(new int(5));
    EXPECT_EQ(*ptr, 5);
}

TEST(UniquePtrTest, Get) {
    std::unique_ptr<int> ptr(new int(5));
    int* rawPtr = ptr.get();
    EXPECT_NE(rawPtr, nullptr);
    EXPECT_EQ(*rawPtr, 5);
}

TEST(UniquePtrTest, GetDeleter) {
    std::unique_ptr<int, Deleter> ptr(new int(5));
    Deleter& del = ptr.get_deleter();
    (void)del; // Just to use the deleter to avoid warnings
}

TEST(UniquePtrTest, CustomDeleterLambda) {
    bool deleted = false;
    {
        std::unique_ptr<int, std::function<void(int*)>> ptr(new int(5), [&deleted](int* p) {
            delete p;
            deleted = true;
        });
    }
    EXPECT_TRUE(deleted);
}

