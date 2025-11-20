#include <gtest/gtest.h>

#include "matrix.hpp"
#include "utils.hpp"

TEST(Matrix, CanCreateCorrectMatrix) {
    EXPECT_NO_THROW(Matrix(5));
}

TEST(Matrix, CantCreateIncorrectMatrix) {
    EXPECT_ANY_THROW(Matrix(-4));
}

TEST(Matrix, CanAccessElement) {
    Matrix matrix(3);

    EXPECT_NO_THROW(matrix(1, 1));
}

TEST(Matrix, CantAccessElementWithIncorrectIndex) {
    Matrix matrix(3);

    EXPECT_ANY_THROW(matrix(3, 1));
    EXPECT_ANY_THROW(matrix(1, 3));
    EXPECT_ANY_THROW(matrix(-1, 0));
    EXPECT_ANY_THROW(matrix(0, -1));
}

TEST(Matrix, CanModifyElement) {
    Matrix matrix(2);

    EXPECT_NO_THROW(matrix(0, 0) = 5.0);
    EXPECT_NEAR(matrix(0, 0), 5.0, EPS);
}

TEST(Matrix, CantModifyElementWithIncorrectIndex) {
    Matrix matrix(2);

    EXPECT_ANY_THROW(matrix(2, 0) = 3.0);
    EXPECT_ANY_THROW(matrix(0, 2) = 3.0);
    EXPECT_ANY_THROW(matrix(-1, 0) = 3.0);
    EXPECT_ANY_THROW(matrix(0, -1) = 3.0);
}

TEST(Matrix, CanGetSize) {
    Matrix m(3);

    EXPECT_EQ(m.size(), 3);
}
