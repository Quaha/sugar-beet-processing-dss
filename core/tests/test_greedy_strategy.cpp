#include <gtest/gtest.h>

#include "greedy_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(GreedyStrategy, CanUseStrategy) {
    EXPECT_NO_THROW(GreedyStrategy(Matrix(5)));
}

TEST(GreedyStrategy, StrategyCorrectnessM0x0) {
    Matrix m(0);

    std::vector<int> expected;

    EXPECT_EQ(GreedyStrategy(m), expected);
}

TEST(GreedyStrategy, StrategyCorrectnessM1x1) {
    Matrix m(1);
    m(0, 0) = 1.0;

    std::vector<int> expected = { 0 };

    EXPECT_EQ(GreedyStrategy(m), expected);
}

TEST(GreedyStrategy, StrategyCorrectnessM2x2) {
    Matrix m(2);
    m(0, 0) = 4.0; m(0, 1) = 2.0;
    m(1, 0) = 2.0; m(1, 1) = 1.0;

    std::vector<int> expected = { 0, 1};

    EXPECT_EQ(GreedyStrategy(m), expected );
}

TEST(GreedyStrategy, StrategyCorrectnessM3x3) {
    Matrix m(3);
    m(0, 0) = 1.0; m(0, 1) = 2.0; m(0, 2) = 4.0;
    m(1, 0) = 2.0; m(1, 1) = 3.0; m(1, 2) = 4.0;
    m(2, 0) = 1.0; m(2, 1) = 1.0; m(2, 2) = 3.0;

    std::vector<int> expected = { 1, 0, 2 };

    EXPECT_EQ(GreedyStrategy(m), expected);
}

TEST(GreedyStrategy, StrategyCorrectnessM4x4) {
    Matrix m(4);
    m(0, 0) = 1.0; m(0, 1) = 2.0; m(0, 2) = 9.0; m(0, 3) = 1.0;
    m(1, 0) = 2.0; m(1, 1) = 1.0; m(1, 2) = 4.0; m(1, 3) = 3.0;
    m(2, 0) = 6.0; m(2, 1) = 7.0; m(2, 2) = 2.0; m(2, 3) = 9.0;
    m(3, 0) = 3.0; m(3, 1) = 1.5; m(3, 2) = 3.0; m(3, 3) = 4.0;

    std::vector<int> expected = { 2, 0, 1, 3 };

    EXPECT_EQ(GreedyStrategy(m), expected);
}