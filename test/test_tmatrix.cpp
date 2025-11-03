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
	TDynamicMatrix<int> B(3);
	TDynamicMatrix<int > A(B);
	EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> B(3);
	TDynamicMatrix<int> A(3);
	A[1][1] = 2;
	EXPECT_NE(A, B);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> A(3);
	EXPECT_EQ(A.size(), 3);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> A(3);
	ASSERT_NO_THROW(A[1][1] = 2);
	EXPECT_EQ(A[1][1] , 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> A(3);
	ASSERT_ANY_THROW(A.at(2).at(-3) = 2);
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> A(3);
	ASSERT_ANY_THROW(A.at(7).at(1) = 2);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> A(3);
	ASSERT_NO_THROW(A = A);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> A(3);
	TDynamicMatrix<int> B(3);
	ASSERT_NO_THROW(B = A);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> A(5);
	TDynamicMatrix<int> B(3);
	B = A;
	EXPECT_EQ(B.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> A(3);
	TDynamicMatrix<int> B(5);
	ASSERT_NO_THROW(B = A);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> A(3);
	TDynamicMatrix<int> B(3);
	ASSERT_TRUE(B == A);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> A(3);
	ASSERT_TRUE(A == A);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> A(3);
	TDynamicMatrix<int> B(5);
	ASSERT_FALSE(B == A);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(5), b(5), c(5);
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = i; j < 5; j++)
		{
			a[i][j] = i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	ASSERT_NO_THROW(c = a + b);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(5), b(6);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(5), b(5), c(5);
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = i; j < 5; j++)
		{
			a[i][j] = i * 10 + j;
			b[i][j] = (i * 10 + j) * 100;
		}
	ASSERT_NO_THROW(c = b - a);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(5), b(6);
	ASSERT_ANY_THROW(a - b);
}

