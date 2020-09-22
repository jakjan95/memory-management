#include <gtest/gtest.h>

#include "shared_ptr.hpp"

constexpr int initialValue = 5;

struct SharedPtrTest : ::testing::Test {
    SharedPtrTest()
        : ptr(new int{initialValue}) {}

    cs::shared_ptr<int> ptr;
};

TEST_F(SharedPtrTest, shouldDereferenceSharedPtr) {
    ASSERT_EQ(*ptr, initialValue);
}

TEST_F(SharedPtrTest, shouldCopySharedPtr) {
    auto ptr2(ptr);
    auto ptr3 = ptr;

    ASSERT_EQ(*ptr, *ptr2);
    ASSERT_EQ(*ptr, *ptr3);
}
