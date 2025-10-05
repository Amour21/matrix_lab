#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int arr[7] = { 10, 6, 19, 83, 21, 12, 98 };
	TDynamicVector<int> v1(arr, 7);
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int arr[7] = { 10, 6, 19, 83, 21, 12, 98 };
	TDynamicVector<int> v1(arr, 7);
	TDynamicVector<int> v2(v1);

	EXPECT_NE(v1.data (), v2.data());
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
 TDynamicVector<int> v(4);
 v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	v[0] = 4;
	ASSERT_ANY_THROW ( v.at(-2));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	v[0] = 4;
	ASSERT_ANY_THROW (v.at(4));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(4);
	v1 = v;
	EXPECT_EQ(v1,v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(6);
	v1 = v;
	EXPECT_EQ(4, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(6);
	v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(4);
	for (size_t i = 0; i < v.size(); i++) {
		v.data()[i] = i;
	}
	TDynamicVector<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		v1.data()[i] = i;
	}
	EXPECT_EQ(v1==v, true) ;
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{ 
	TDynamicVector<int> v(4);
	for (size_t i = 0; i < v.size(); i++) {
		v.data()[i] = i;
	}
	EXPECT_EQ(v == v, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> v1(7);
	EXPECT_NE(v1 == v, true);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(548);
	v[147] = 32;
	v = v + 15;
	EXPECT_EQ(v[147], 47);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(548);
	v[517] = 32;
	v = v - 23;
	EXPECT_EQ(v[517], 9);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(327);
	v[153] = 15;
	v = v * 3;
	EXPECT_EQ(v[153], 45);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	v2[3] = 5;
	v1[3] = 10;
	v = v1 + v2;
	EXPECT_EQ(v[3], 15);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(17);
	TDynamicVector<int> v2(16);
	ASSERT_ANY_THROW(v1+v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	v2[3] = 45;
	v1[3] = 9;
	v = v2 - v1;
	EXPECT_EQ(v[3], 36);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(27);
	TDynamicVector<int> v2(26);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{ 
	int res;
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 4;
	v1[3] = 1;
	v2[0] = 2;
	v2[1] = 1;
	v2[2] = 0;
	v2[3] = 7;
	// res = 1*2 + 2*1 + 4*0 + 7*1 = 11
	res = v2 * v1;
	EXPECT_EQ(res, 11);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(27);
	TDynamicVector<int> v2(26);
	ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVectorMove, move_constructor_transfers_pointer) {
	int arr[] = { 1,2,3 };
	TDynamicVector<int> src(arr, 3);
	int* ptr = src.data();
	TDynamicVector<int> moved(std::move(src));
	EXPECT_EQ(moved.data(), ptr);
}

TEST(TDynamicVectorMove, move_constructor_resets_source_pointer) {
	int arr[] = { 1,2,3 };
	TDynamicVector<int> src(arr, 3);
	TDynamicVector<int> moved(std::move(src));
	EXPECT_EQ(src.data(), nullptr);
}

TEST(TDynamicVectorMove, move_constructor_transfers_size) {
	int arr[] = { 1,2,3 };
	TDynamicVector<int> src(arr, 3);
	size_t oldSize = src.size();
	TDynamicVector<int> moved(std::move(src));
	EXPECT_EQ(moved.size(), oldSize);
}

TEST(TDynamicVectorMove, move_assignment_transfers_pointer) {
	int arr[] = { 4,5,6 };
	TDynamicVector<int> src(arr, 3);
	int* srcPtr = src.data();
	TDynamicVector<int> dest(5);
	dest = std::move(src);
	EXPECT_EQ(dest.data(), srcPtr);
}

TEST(TDynamicVectorMove, move_assignment_resets_source_pointer) {
	int arr[] = { 4,5,6 };
	TDynamicVector<int> src(arr, 3);
	TDynamicVector<int> dest(5);
	dest = std::move(src);
	EXPECT_EQ(src.data(), nullptr);
}

TEST(TDynamicVectorMove, move_assignment_clear_memory) {
	int arr[] = { 7,8,9 };
	TDynamicVector<int> src(arr, 3);
	TDynamicVector<int> last(4);
	int* oldPtr = last.data();
	last = std::move(src);
	EXPECT_NE(last.data(), oldPtr);
}

TEST(TDynamicVectorMove, self_move_assignment_is_safe) {
	int arr[] = { 10,11,12 };
	TDynamicVector<int> v(arr, 3);
	int* beforePtr = v.data();
	v = std::move(v);
	EXPECT_EQ(v.data(), beforePtr);
}

// создание из временного (move-from-temporary) корректно инициализирует значения
TEST(TDynamicVectorMove, move_from_temporary_initializes_values) {
	int arr[] = { 16,17,18 };
	TDynamicVector<int> v = TDynamicVector<int>(arr, 3); 
	EXPECT_EQ(v[0], 16);
}

//  перемещение и деструктор не приводят к двойному free (тест проверяет отсутствие аварии)
TEST(TDynamicVectorMove, MoveThenDestructDoesNotCrash) {
	int arr[] = { 19,20 };
	{
		TDynamicVector<int> a(arr, 2);
		TDynamicVector<int> b(std::move(a));
	}
	SUCCEED(); 
}

TEST(TDynamicVector_IO, output_format_space_separated) {
	int arr[] = { 10, 6, 19, 83, 21, 12, 98 };
	TDynamicVector<int> v(arr, 7);

	std::ostringstream oss;
	oss << v;

	EXPECT_EQ(oss.str(), "10 6 19 83 21 12 98 ");
}

// Ввод: из потока читаются все элементы вектора (в том же порядке)
TEST(TDynamicVector_IO, input_reads_all_elements) {
	const char* src = "10 6 19 83 21 12 98 ";
	std::istringstream iss(src);
	TDynamicVector<int> v(7);
	iss >> v;
	int arr[] = { 10, 6, 19, 83, 21, 12, 98 };
	TDynamicVector<int> expected(arr, 7); 
	EXPECT_EQ(v, expected);
}
//  (write -> read) сохраняет значения
TEST(TDynamicVector_IO, write_read_working) {
	int arr[] = { 1, 2, 3, 4 };
	TDynamicVector<int> v1(arr, 4);
	std::stringstream ss;
	ss << v1;           // записали
	TDynamicVector<int> v2(4);
	ss >> v2;           // прочитали обратно
	EXPECT_EQ(v1, v2);
}