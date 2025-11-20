#include <gtest/gtest.h>

#include "optimal_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(OptimalStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(OptimalStrategy(Matrix(5)));
}