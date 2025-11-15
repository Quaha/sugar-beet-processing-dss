#include <gtest/gtest.h>

#include "matrix.hpp"

const double EPSILON = 1e-9;

TEST(Matrix, CanCreateCorrectMatrix) {
    EXPECT_NO_THROW(Matrix(5));
}

TEST(Matrix, CantCreateIncorrectMatrix) {
    EXPECT_ANY_THROW(Matrix(-4));
}

TEST(Matrix, CanAccessElement) {
    Matrix m(3);

    EXPECT_NO_THROW(m(1, 1));
}

TEST(Matrix, CantAccessElementWithIncorrectIndex) {
    Matrix m(3);

    EXPECT_ANY_THROW(m(3, 1));
    EXPECT_ANY_THROW(m(1, 3));
    EXPECT_ANY_THROW(m(-1, 0));
    EXPECT_ANY_THROW(m(0, -1));
}

TEST(Matrix, CanModifyElement) {
    Matrix m(2);

    EXPECT_NO_THROW(m(0, 0) = 5.0);
    EXPECT_NEAR(m(0, 0), 5.0, EPSILON);
}

TEST(Matrix, CantModifyElementWithIncorrectIndex) {
    Matrix m(2);

    EXPECT_ANY_THROW(m(2, 0) = 3.0);
    EXPECT_ANY_THROW(m(0, 2) = 3.0);
    EXPECT_ANY_THROW(m(-1, 0) = 3.0);
    EXPECT_ANY_THROW(m(0, -1) = 3.0);
}
