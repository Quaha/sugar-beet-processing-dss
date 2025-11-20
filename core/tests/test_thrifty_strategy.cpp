#include <gtest/gtest.h>

#include "thrifty_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(ThriftyStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(ThriftyStrategy(Matrix(5)));
}