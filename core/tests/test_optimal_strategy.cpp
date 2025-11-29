#include <gtest/gtest.h>

#include "optimal_strategy.hpp"

#include <vector>

#include "matrix.hpp"

TEST(OptimalStrategy, CanUseStrategy) {
    TestableMatrix tm(5);
    Matrix m = tm;

    EXPECT_NO_THROW(OptimalStrategy(m));
}

TEST(OptimalStrategy, SingleElement)
{
    Matrix m(1);
    m(0, 0) = 42.0;

    auto res = OptimalStrategy(m);

    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], 0);
}

TEST(OptimalStrategy, StrategyCorrectnessM0x0)
{
    TestableMatrix tm(0);
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected;

    EXPECT_EQ(OptimalStrategy(m), expected);
}

TEST(OptimalStrategy, StrategyCorrectnessM1x1No1)
{
    TestableMatrix tm(1);
    tm(0, 0) = 1.0;
    Matrix m = tm;

    std::vector<int> expected = { 0 };

    EXPECT_EQ(OptimalStrategy(m), expected);
}

TEST(OptimalStrategy, StrategyCorrectnessM2x2)
{
    TestableMatrix tm(2);
    tm(0, 0) = 4.0; tm(0, 1) = 8.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0;
    Matrix m = tm;

    std::vector<int> expected = { 1, 0 };

    EXPECT_EQ(OptimalStrategy(m), expected);
}

TEST(OptimalStrategy, StrategyCorrectnessM3x3No1)
{
    TestableMatrix tm(3);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.5; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    Matrix m = tm;

    std::vector<int> expected = { 2, 1, 0 };

    EXPECT_EQ(OptimalStrategy(m), expected);
}

TEST(OptimalStrategy, StrategyCorrectnessM3x3No2)
{
    TestableMatrix tm(3);
    tm(0, 0) = 3.1; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.5; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    Matrix m = tm;

    std::vector<int> expected = { 0, 1, 2 };

    EXPECT_EQ(OptimalStrategy(m), expected);
}

TEST(OptimalStrategy, StrategyCorrectnessM4x4No1)
{
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    tm.v = 0;
    Matrix m = tm;

    std::vector<int> expected = { 3, 1, 0, 2 };

    EXPECT_EQ(OptimalStrategy(m), expected);
}

TEST(OptimalStrategy, StrategyCorrectnessM10x10No1)
{
    TestableMatrix tm(10);
    tm(0, 0) = 5.16;	tm(0, 1) = 2.82;	tm(0, 2) = 9.43;	tm(0, 3) = 4.2;	    tm(0, 4) = 7.8;	    tm(0, 5) = 0.94;    tm(0, 6) = 7.33;    tm(0, 7) = 1.88;    tm(0, 8) = 0.69;	tm(0, 9) = 3.97;
    tm(1, 0) = 6.13;	tm(1, 1) = 8.57;	tm(1, 2) = 0.98;	tm(1, 3) = 2.35;	tm(1, 4) = 7.6;     tm(1, 5) = 9.69;    tm(1, 6) = 6.59;    tm(1, 7) = 5.74;    tm(1, 8) = 2.1;     tm(1, 9) = 8.76;
    tm(2, 0) = 1.55;	tm(2, 1) = 1.57;	tm(2, 2) = 4.12;	tm(2, 3) = 7.17;	tm(2, 4) = 6.25;    tm(2, 5) = 1.23;    tm(2, 6) = 8.81;    tm(2, 7) = 3.86;    tm(2, 8) = 1.64;    tm(2, 9) = 5.41;
    tm(3, 0) = 7.46;	tm(3, 1) = 0.03;	tm(3, 2) = 0.88;	tm(3, 3) = 4.19;	tm(3, 4) = 6.12;	tm(3, 5) = 2.12;    tm(3, 6) = 5.07;    tm(3, 7) = 8.79;    tm(3, 8) = 4.98;    tm(3, 9) = 5.09;
    tm(4, 0) = 4.09;	tm(4, 1) = 7.32;	tm(4, 2) = 9.59;	tm(4, 3) = 4.44;	tm(4, 4) = 3.15;    tm(4, 5) = 3.41;    tm(4, 6) = 2.45;    tm(4, 7) = 3.79;    tm(4, 8) = 3.11;    tm(4, 9) = 5.6;
    tm(5, 0) = 6.01;	tm(5, 1) = 2.48;	tm(5, 2) = 3.77;	tm(5, 3) = 3.69;	tm(5, 4) = 6.21;    tm(5, 5) = 6.45;    tm(5, 6) = 3.28;    tm(5, 7) = 4.54;    tm(5, 8) = 3.14;    tm(5, 9) = 7.48;
    tm(6, 0) = 0.61;	tm(6, 1) = 6.22;	tm(6, 2) = 6.51;	tm(6, 3) = 0.28;	tm(6, 4) = 6.06;    tm(6, 5) = 1.4;     tm(6, 6) = 4.45;    tm(6, 7) = 1.78;    tm(6, 8) = 1.22;    tm(6, 9) = 6.67;
    tm(7, 0) = 3.1;	    tm(7, 1) = 5.31;	tm(7, 2) = 5.25;	tm(7, 3) = 4.39;	tm(7, 4) = 9.09;    tm(7, 5) = 3.57;    tm(7, 6) = 1.88;    tm(7, 7) = 8.21;    tm(7, 8) = 7.46;    tm(7, 9) = 8.02;
    tm(8, 0) = 4.44;	tm(8, 1) = 9.1;	    tm(8, 2) = 1.99;	tm(8, 3) = 7.89;	tm(8, 4) = 4.85;	tm(8, 5) = 4.15;    tm(8, 6) = 6.72;    tm(8, 7) = 5.04;    tm(8, 8) = 7.7;	    tm(8, 9) = 0.81;
    tm(9, 0) = 7.75;	tm(9, 1) = 6.3;	    tm(9, 2) = 7.42;	tm(9, 3) = 2.64;	tm(9, 4) = 3.07;	tm(9, 5) = 7.8;     tm(9, 6) = 5.94;    tm(9, 7) = 2.85;    tm(9, 8) = 9.02;    tm(9, 9) = 6.47;

    Matrix m = tm;

    std::vector<int> expected = { 5, 4, 0, 8, 7, 1, 2, 3, 9, 6 };

    EXPECT_EQ(OptimalStrategy(m), expected);
}