#include <gtest/gtest.h>

#include "optimal_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(OptimalStrategy, CanUseStrategy) {
    TestableMatrix tm(5);
    Matrix m = tm;

    EXPECT_NO_THROW(OptimalStrategy(m));
}