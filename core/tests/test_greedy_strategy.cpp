#include <gtest/gtest.h>

#include "greedy_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(GreedyStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(GreedyStrategy(Matrix(5)));
}