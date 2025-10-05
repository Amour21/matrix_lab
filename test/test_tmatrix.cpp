#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m1(3);
    m1[0][0] = 1;
    m1[1][1] = 2;
    m1[2][2] = 3;
    TDynamicMatrix<int> m2(m1);
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 5;
    TDynamicMatrix<int> m2(m1);
    m2[0][0] = 10;
    EXPECT_NE(m1[0][0], m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);
    EXPECT_EQ(m.size(), 4); 
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    m[1][2] = 42;
    EXPECT_EQ(m[1][2], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m.at(-1).at(0) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m.at(3).at(0) = 5);
    ASSERT_ANY_THROW(m.at(0).at(5) = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 7;
    m = m;  
    EXPECT_EQ(m[0][0], 7);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 9;
    TDynamicMatrix<int> m2(2);
    m2 = m1;
    EXPECT_EQ(m1, m2);
    EXPECT_NE(&m1[0][0], &m2[0][0]); 
}
TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);
    m2 = m1;   
    EXPECT_EQ(m2.size(), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 42;
    TDynamicMatrix<int> m2(3);
    m2 = m1;
    EXPECT_EQ(m2.size(), m1.size());
    EXPECT_EQ(m2[0][0], 42);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);
    m1[0][0] = 5;
    m2[0][0] = 5;
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(2);
    m[1][1] = 99;
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);
    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m2[0][0] = 2;
    TDynamicMatrix<int> res = m1 + m2;
    EXPECT_EQ(res[0][0], 3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    EXPECT_THROW(m1 + m2, std::out_of_range);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[1][1] = 5; m2[1][1] = 3;
    TDynamicMatrix<int> res = m1 - m2;
    EXPECT_EQ(res[1][1], 2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    EXPECT_THROW(m1 - m2, std::out_of_range);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> A(2), B(2);
    A[0][0] = 1; A[0][1] = 2; A[1][0] = 3; A[1][1] = 4;
    B[0][0] = 2; B[0][1] = 0; B[1][0] = 1; B[1][1] = 2;

    TDynamicMatrix<int> C = A * B;
    EXPECT_EQ(C[0][0], 4); // 1*2 + 2*1 = 4
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
    TDynamicMatrix<int> A(2);
    A[0][0] = 1; A[0][1] = 2; A[1][0] = 3; A[1][1] = 4;
    TDynamicVector<int> v(2);
    v[0] = 5; v[1] = 6;

    TDynamicVector<int> r = A * v;
    EXPECT_EQ(r[0], 1 * 5 + 2 * 6);
}

TEST(TDynamicMatrix, multiply_by_identity_returns_same)
{
    TDynamicMatrix<int> M(3);
    for (size_t i = 0; i < 3; i++) for (size_t j = 0; j < 3; j++) M[i][j] = (int)(i * 3 + j + 1);
    TDynamicMatrix<int> I(3);
    for (size_t i = 0; i < 3; i++) I[i][i] = 1;

    TDynamicMatrix<int> R = M * I;
    EXPECT_EQ(R[2][1], M[2][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
    TDynamicMatrix<int> M(2);
    M[0][0] = 2;
    TDynamicMatrix<int> R = M * 3;
    EXPECT_EQ(R[0][0], 6);
}
TEST(TDynamicMatrix, default_elements_are_zero)
{
    TDynamicMatrix<int> M(2);
    EXPECT_EQ(M[0][0], 0); // элементы должны быть нулевыми по умолчанию
}

TEST(TDynamicMatrix, operator_index_returns_row_reference)
{
    TDynamicMatrix<int> M(2);
    M[0][1] = 123;
    EXPECT_EQ(M[0][1], 123);
}
TEST(TDynamicMatrix, addition_does_not_modify_operands)
{
    TDynamicMatrix<int> A(2), B(2);
    A[0][0] = 7; B[0][0] = 8;
    TDynamicMatrix<int> C = A + B;
    EXPECT_EQ(A[0][0], 7); // A не меняется
}
TEST(TDynamicMatrix, io_roundtrip_preserves_values)
{
    TDynamicMatrix<int> M(2);
    M[0][0] = 1; M[0][1] = 2; M[1][0] = 3; M[1][1] = 4;

    std::stringstream ss;
    ss << M;

    TDynamicMatrix<int> N(2);
    ss >> N;

    EXPECT_EQ(M, N);
}