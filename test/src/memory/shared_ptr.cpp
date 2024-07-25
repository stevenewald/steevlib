#include "memory/shared_ptr.hpp"
#include <gtest/gtest.h>

// Test construction and assignment
TEST(SharedPtrTest, ConstructionAndAssignment) {
    steev::shared_ptr<int> p1(new int(5));
    EXPECT_EQ(*p1, 5);
    EXPECT_EQ(p1.use_count(), 1);

    steev::shared_ptr<int> p2(p1);
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(p1.use_count(), 2);
    EXPECT_EQ(p2.use_count(), 2);

    steev::shared_ptr<int> p3;
    EXPECT_EQ(p3.use_count(), 0);

    p3 = p1;
    EXPECT_EQ(p1, p3);
    EXPECT_EQ(p1.use_count(), 3);
    EXPECT_EQ(p2.use_count(), 3);
    EXPECT_EQ(p3.use_count(), 3);
}

// Test reset
TEST(SharedPtrTest, Reset) {
    steev::shared_ptr<int> p1(new int(10));
    EXPECT_EQ(*p1, 10);
    EXPECT_EQ(p1.use_count(), 1);

    p1.reset(new int(20));
    EXPECT_EQ(*p1, 20);
    EXPECT_EQ(p1.use_count(), 1);
}

// 1. Default Constructor
TEST(SharedPtrTest, DefaultConstructor) {
    steev::shared_ptr<int> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
}

// 2. Nullptr Constructor
TEST(SharedPtrTest, NullptrConstructor) {
    steev::shared_ptr<int> sp(nullptr);
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
}

// 3. Single Ownership
TEST(SharedPtrTest, SingleOwnership) {
    auto sp = steev::make_shared<int>(10);
    EXPECT_EQ(sp.use_count(), 1);
}

// 4. Multiple Ownership
TEST(SharedPtrTest, MultipleOwnership) {
    auto sp1 = steev::make_shared<int>(10);
    steev::shared_ptr<int> sp2 = sp1;
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

// 5. Unique Ownership After Copy
TEST(SharedPtrTest, UniqueOwnershipAfterCopy) {
    auto sp1 = steev::make_shared<int>(10);
    steev::shared_ptr<int> sp2 = sp1;
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

// 6. Reset to Null
TEST(SharedPtrTest, ResetToNull) {
    auto sp = steev::make_shared<int>(10);
    sp.reset();
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
}

// 7. Reset to New Object
TEST(SharedPtrTest, ResetToNewObject) {
    auto sp = steev::make_shared<int>(10);
    sp.reset(new int(20));
    EXPECT_EQ(sp.use_count(), 1);
    EXPECT_EQ(*sp, 20);
}

// 8. Use Count After Assignment
TEST(SharedPtrTest, UseCountAfterAssignment) {
    auto sp1 = steev::make_shared<int>(10);
    steev::shared_ptr<int> sp2;
    sp2 = sp1;
    EXPECT_EQ(sp1.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
}

// 9. Use Count After Move
TEST(SharedPtrTest, UseCountAfterMove) {
    auto sp1 = steev::make_shared<int>(10);
    steev::shared_ptr<int> sp2 = std::move(sp1);
    EXPECT_EQ(sp1.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 1);
}

// 10. Object Access
TEST(SharedPtrTest, ObjectAccess) {
    auto sp = steev::make_shared<int>(10);
    EXPECT_EQ(*sp, 10);
    EXPECT_EQ(*sp.operator->(), 10);
}

// 13. Const Correctness
TEST(SharedPtrTest, ConstCorrectness) {
    const steev::shared_ptr<int> sp = steev::make_shared<int>(10);
    EXPECT_EQ(*sp, 10);
}

// 15. Swap
TEST(SharedPtrTest, Swap) {
    auto sp1 = steev::make_shared<int>(10);
    auto sp2 = steev::make_shared<int>(20);
    sp1.swap(sp2);
    EXPECT_EQ(*sp1, 20);
    EXPECT_EQ(*sp2, 10);
}

// 16. Make Shared
TEST(SharedPtrTest, MakeShared) {
    auto sp = steev::make_shared<int>(10);
    EXPECT_EQ(sp.use_count(), 1);
    EXPECT_EQ(*sp, 10);
}

// 18. Outliving Copies
TEST(SharedPtrTest, OutlivingCopies) {
    steev::shared_ptr<int> sp1;
    {
        auto sp2 = steev::make_shared<int>(10);
        sp1 = sp2;
        EXPECT_EQ(sp2.use_count(), 2);
    }
    EXPECT_EQ(sp1.use_count(), 1);
}

// 19. Circular Reference
struct Node {
    steev::shared_ptr<Node> next;
};
TEST(SharedPtrTest, CircularReference) {
    auto node1 = steev::make_shared<Node>();
    auto node2 = steev::make_shared<Node>();
    node1->next = node2;
    node2->next = node1; // Circular reference
    node1->next.reset(); // Break the circular reference
    node2->next.reset();
    EXPECT_EQ(node1->next, nullptr);
    EXPECT_EQ(node2->next, nullptr);
}

// 20. Null Shared Ptr
TEST(SharedPtrTest, NullSharedPtr) {
    steev::shared_ptr<int> sp1;
    steev::shared_ptr<int> sp2 = nullptr;
    EXPECT_EQ(sp1, nullptr);
    EXPECT_EQ(sp2, nullptr);
    EXPECT_EQ(sp1.use_count(), 0);
    EXPECT_EQ(sp2.use_count(), 0);
}

