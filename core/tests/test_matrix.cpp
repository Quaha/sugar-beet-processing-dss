#include <gtest/gtest.h>

#include "matrix.hpp"
#include "utils.hpp"

TEST(Matrix, CanCreateCorrectMatrix) {
    EXPECT_NO_THROW(TestableMatrix(5));
}

TEST(Matrix, CantCreateIncorrectMatrix) {
    EXPECT_ANY_THROW(TestableMatrix(-4));
}

TEST(Matrix, CanAccessElement) {
    TestableMatrix m(3);

    EXPECT_NO_THROW(m(1, 1));
}

TEST(Matrix, CantAccessElementWithIncorrectIndex) {
    TestableMatrix m(3);

    EXPECT_ANY_THROW(m(3, 1));
    EXPECT_ANY_THROW(m(1, 3));
    EXPECT_ANY_THROW(m(-1, 0));
    EXPECT_ANY_THROW(m(0, -1));
}

TEST(Matrix, CanModifyElement) {
    TestableMatrix m(2);

    EXPECT_NO_THROW(m(0, 0) = 5.0);
    EXPECT_NEAR(m(0, 0), 5.0, EPS);
}

TEST(Matrix, CantModifyElementWithIncorrectIndex) {
    TestableMatrix m(2);

    EXPECT_ANY_THROW(m(2, 0) = 3.0);
    EXPECT_ANY_THROW(m(0, 2) = 3.0);
    EXPECT_ANY_THROW(m(-1, 0) = 3.0);
    EXPECT_ANY_THROW(m(0, -1) = 3.0);
}

TEST(Matrix, CanGetSize) {
    TestableMatrix m(3);

    EXPECT_EQ(m.size(), 3);
}

TEST(Matrix, CanFillMatrix) {
    EXPECT_TRUE(false);
}

TEST(Matrix, CanGetAlphaMin) {
	Matrix m(2);

    EXPECT_NEAR(0.12, m.getAlphaMin(), EPS);
}

TEST(Matrix, CanGetAlphaMax) {
    Matrix m(2);

    EXPECT_NEAR(0.22, m.getAlphaMax(), EPS);
}

TEST(Matrix, CanGetBeta1) {
    Matrix m(2);

    EXPECT_NEAR(0.85, m.getBeta1(), EPS);
}

TEST(Matrix, CanGetBeta2) {
    Matrix m(2);

    EXPECT_NEAR(1.00, m.getBeta2(), EPS);
}

TEST(Matrix, CanGetConcentratedStatus) {
    Matrix m(2);

    EXPECT_FALSE(m.isConcentrated());
}

TEST(Matrix, CanGetMaturationStatus) {
    Matrix m(2);

    EXPECT_FALSE(m.hasMaturation());
}

TEST(Matrix, CanGetInorganicStatus) {
    Matrix m(2);

    EXPECT_FALSE(m.isInorganic());
}

TEST(Matrix, CanGetV) {
    Matrix m(2);

    EXPECT_EQ(0, m.getV());
}

TEST(Matrix, CanGetBetaMax) {
    Matrix m(2);

    EXPECT_NEAR(1.15, m.getBetaMax(), EPS);
}
