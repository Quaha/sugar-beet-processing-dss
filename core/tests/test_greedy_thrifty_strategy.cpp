#include <gtest/gtest.h>

#include "greedy_thrifty_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(GreedyThriftyStrategy, CanUseStrategy) {
    TestableMatrix tm(5);
    tm.v = 0;
    Matrix m = tm;

    EXPECT_NO_THROW(GreedyThriftyStrategy(m));
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM0x0) {
    TestableMatrix tm(0);
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected;

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM1x1No1) {
    TestableMatrix tm(1);
    tm(0, 0) = 1.0;
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected = { 0 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM1x1No2) {
    TestableMatrix tm(1);
    tm(0, 0) = 1.0;
    tm.v = 1;
    Matrix m = tm;

    std::vector<int> expected = { 0 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM2x2No1) {
    TestableMatrix tm(2);
    tm(0, 0) = 4.0; tm(0, 1) = 8.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0;
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected = { 1, 0 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM2x2No2) {
    TestableMatrix tm(2);
    tm(0, 0) = 4.0; tm(0, 1) = 8.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0;
    tm.v = 1;
    Matrix m = tm;

    std::vector<int> expected = { 0, 1 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM2x2No3) {
    TestableMatrix tm(2);
    tm(0, 0) = 4.0; tm(0, 1) = 8.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0;
    tm.v = 2;
    Matrix m = tm;

    std::vector<int> expected = { 0, 1 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM3x3No1) {
    TestableMatrix tm(3);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.5; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected = { 0, 2, 1 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM3x3No2) {
    TestableMatrix tm(3);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.0; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    tm.v = 1;
    Matrix m = tm;

    std::vector<int> expected = { 1, 2, 0 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM3x3No3) {
    TestableMatrix tm(3);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.5; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    tm.v = 2;
    Matrix m = tm;

    std::vector<int> expected = { 1, 0, 2 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM3x3No4) {
    TestableMatrix tm(3);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.5; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    tm.v = 3;
    Matrix m = tm;

    std::vector<int> expected = { 1, 0, 2 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM4x4No1) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected = { 0, 1, 2, 3 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM4x4No2) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    tm.v = 1;
    Matrix m = tm;

    std::vector<int> expected = { 2, 1, 3, 0 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM4x4No3) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    tm.v = 2;
    Matrix m = tm;

    std::vector<int> expected = { 2, 0, 3, 1 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM4x4No4) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    tm.v = 3;
    Matrix m = tm;

    std::vector<int> expected = { 2, 0, 1, 3 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}

TEST(GreedyThriftyStrategy, StrategyCorrectnessM4x4No5) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    tm.v = 4;
    Matrix m = tm;

    std::vector<int> expected = { 2, 0, 1, 3 };

    EXPECT_EQ(GreedyThriftyStrategy(m), expected);
}