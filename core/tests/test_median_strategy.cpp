#include <gtest/gtest.h>

#include "median_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(MedianStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(MedianStrategy(Matrix(5)));
}