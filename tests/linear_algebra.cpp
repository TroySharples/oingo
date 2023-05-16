#include "math/matrix.hpp"

#include <gtest/gtest.h>

#define ASSERT_MATRIX_NEAR(A,B) ASSERT_NEAR(math::norm((A) - (B)), 0, 100*std::numeric_limits<double>::epsilon())

static const auto I = math::identity<double, 3>();

static const math::matrix<double, 3, 3> A = {
    1,  0, -3,
    4, -8, 12,
    3, 15,  0
};

static const math::matrix<double, 3, 3> B = {
    1, 0, 0,
    0, 5, 0,
    0, 0, 5
};

static const math::matrix<double, 3, 3> C = {
    0, -5,  0,
    0,  6,  0,
    0,  1, -5
};

static const auto NONSINGULAR_MATRICIES = { I, A, B };
static const auto SINGULAR_MATRICIES    = { C };

TEST(MatrixInverterTest, Identity)
{
    const auto IINV = math::invert(I);

    ASSERT_MATRIX_NEAR(I, IINV) << "The inverse of the identity matrix should be the identity matrix";
}

TEST(MatrixInverterTest, Singular)
{
    for (const auto& M : SINGULAR_MATRICIES)
        ASSERT_THROW(math::invert(M), std::runtime_error) << "Singular matrix should throw an exception when trying to invert";
}

TEST(MatrixInverterTest, NonSingular)
{
    for (const auto& M : NONSINGULAR_MATRICIES)
    {
        const auto MINV = math::invert(M);
        const auto MMINV = M * MINV;
        ASSERT_MATRIX_NEAR(MMINV, I) << "A matrix multiplied by its inverse should be the identity matrix";
    }
}

TEST(MatrixInverterTest, InvertInvert)
{
    for (const auto& M : NONSINGULAR_MATRICIES)
    {
        const auto MINV = math::invert(M);
        const auto MINVINV = math::invert(MINV);

        ASSERT_MATRIX_NEAR(M, MINVINV) << "The inverse of the inverse of a matrix should be the matrix itself";
    }
}

TEST(MatrixDeterminantTest, Identity)
{
    ASSERT_EQ(math::determinant(I), 1) << "The determinant of the identity matrix should be 1";
}

TEST(MatrixDeterminantTest, Singular)
{
    for (const auto& M : SINGULAR_MATRICIES)
        ASSERT_EQ(math::determinant(M), 0) << "The determinant of a singular matrix should be 0";
}

TEST(MatrixDeterminantTest, NonSingular)
{
    for (const auto& M : NONSINGULAR_MATRICIES)
        ASSERT_NE(math::determinant(M), 0) << "The determinant of a non-singular matrix should not be 0";
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}