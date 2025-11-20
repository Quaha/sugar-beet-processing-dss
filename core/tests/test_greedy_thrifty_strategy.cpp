#include <gtest/gtest.h>

#include "greedy_thrifty_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(GreedyThriftyStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(GreedyThriftyStrategy(Matrix(5)));
}