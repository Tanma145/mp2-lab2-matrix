#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v(5), v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(5), v1(v);
	v[0] = 0;
	v1[0] = 1;
	EXPECT_NE(v, v1);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[6]);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TMatrix<int> v(2);
	v[0] = 0;
	v[1] = 1;
	TMatrix<int> v1(v);
	v = v;
	EXPECT_EQ(v, v1);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TMatrix<int> v(5), v1(5);
	v[0] = 0;
	v1[0] = 1;
	v = v1;
	EXPECT_EQ(v, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TMatrix<int> v(3), v1(5);
	v = v1;
	EXPECT_EQ(v.GetSize(), 5);
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TMatrix<int> v(3), v1(5);
	v = v1;
	EXPECT_EQ(v, v1);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TMatrix<int> v(3), v1(3);
	for (int i = 0; i < 3; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	EXPECT_EQ(v, v1);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TMatrix<int> v(5);
	EXPECT_EQ(v, v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TMatrix<int> v(3), v1(5);
	EXPECT_NE(v, v1);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(5), res(5);
	for (int i = 0; i < 5; i++) {
		v[i] = 0;
		res[i] = 1;
	}
	v = v + 1;
	EXPECT_EQ(v, res);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(5), res(5);
	for (int i = 0; i < 5; i++) {
		v[i] = 1;
		res[i] = 0;
	}
	v = v - 1;
	EXPECT_EQ(v, res);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(5), v1(5);
	for (int i = 0; i < 5; i++) {
		v[i] = 1;
		v1[i] = 2;
	}
	v = v * 2;
	EXPECT_EQ(v, v1);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v(5), v1(5), res(5);
	for (int i = 0; i < 5; i++) {
		v[i] = i;
		v1[i] = 3 * i + 1;
		res[i] = 3 * i + 1 + i;
	}
	EXPECT_EQ(v + v1, res);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> m(3), v(5);
	ASSERT_ANY_THROW(m + v);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v(5), v1(5), res(5);
	for (int i = 0; i < 5; i++) {
		v[i] = 2*i;
		v1[i] = i;
		res[i] = i;
	}
	EXPECT_EQ(v - v1, res);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> m(3), v(5);
	ASSERT_ANY_THROW(m - v);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v(5), v1(5);
	int res = 0;
	for (int i = 0; i < 5; i++) {
		v[i] = 2;
		v1[i] = i;
		res = res + 2 * i;
	}
	EXPECT_EQ(v * v1, res);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(3), v1(5);
	ASSERT_ANY_THROW(v * v1);
}

