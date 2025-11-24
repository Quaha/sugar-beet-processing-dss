#include <gtest/gtest.h>

#include "thrifty_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(ThriftyStrategy, CanUseStrategy) {
	TestableMatrix tm(5);
	Matrix m = tm;

    EXPECT_NO_THROW(ThriftyStrategy(m));
}

TEST(ThriftyStrategy, StrategyCorrectnessM0x0) {
	TestableMatrix tm(0);
    Matrix m = tm;

    std::vector<int> expected;

    EXPECT_EQ(ThriftyStrategy(m), expected);
}

TEST(ThriftyStrategy, StrategyCorrectnessM1x1) {
    TestableMatrix tm(1);
    tm(0, 0) = 1.0;
    Matrix m = tm;

    std::vector<int> expected = { 0 };

    EXPECT_EQ(ThriftyStrategy(m), expected);
}

TEST(ThriftyStrategy, StrategyCorrectnessM2x2) {
    TestableMatrix tm(2);
    tm(0, 0) = 4.0; tm(0, 1) = 2.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0;
    Matrix m = tm;

    std::vector<int> expected = { 1, 0 };

    EXPECT_EQ(ThriftyStrategy(m), expected);
}

TEST(ThriftyStrategy, StrategyCorrectnessM3x3) {
    TestableMatrix tm(3);
    tm(0, 0) = 4.0; tm(0, 1) = 3.0; tm(0, 2) = 9.0;
    tm(1, 0) = 2.0; tm(1, 1) = 2.0; tm(1, 2) = 9.0;
    tm(2, 0) = 1.0; tm(2, 1) = 1.0; tm(2, 2) = 9.0;
    Matrix m = tm;

    std::vector<int> expected = { 2, 1, 0 };

    EXPECT_EQ(ThriftyStrategy(m), expected);
}

TEST(ThriftyStrategy, StrategyCorrectnessM4x4) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    Matrix m = tm;

    std::vector<int> expected = { 0, 1, 2, 3 };

    EXPECT_EQ(ThriftyStrategy(m), expected);
}