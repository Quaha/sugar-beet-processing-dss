#include <gtest/gtest.h>

#include "thrifty_greedy_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(ThriftyGreedyStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(ThriftyGreedyStrategy(Matrix(5)));
}