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
