#include <gtest/gtest.h>

#include "mylib.hpp"

TEST(MyLibTest, SimpleTest) {
    EXPECT_EQ(add(1, 2), 3);
}
