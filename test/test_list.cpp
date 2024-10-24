#include "list.h"

#include <gtest.h>

TEST(List, can_create_list_with_positive_length) 
{
	EXPECT_NO_THROW(List<int> l(5));
}

TEST(List, can_create_list_with_negative_length)
{
	EXPECT_ANY_THROW(List<int> l(-1));
}

TEST(List, can_use_copy_constructor) {
	List<int> l1(1);
	
	EXPECT_NO_THROW(List<int> l2(l1));
}

TEST(List, can_set_and_get_element) {
	List<int> l(5);

	EXPECT_NO_THROW(l[3].value = 3);

	EXPECT_EQ(l[3].value, 3);
}

TEST(List, copied_list_equal_to_source_one) {
	List<int> l1(5);

	for (int i = 0; i < 5; i++) {
		l1[i].value = i;
	}
	
	List<int> l2(l1);
	bool isEqual = true;

	for (int i = 0; i < 5; i++) {
		if (l1[i].value != l2[i].value) isEqual = false;
	}

	EXPECT_TRUE(isEqual);
}

TEST(List, copied_list_has_its_own_memory) {
	List<int> l1(5);

	for (int i = 0; i < 5; i++) {
		l1[i].value = i;
	}

	List<int> l2(l1);
	
	l2[0].value = 10;

	EXPECT_EQ(l1[0].value, 0);  
	EXPECT_EQ(l2[0].value, 10);
}

TEST(List, can_get_size) {
	List<int> l(5);

	EXPECT_EQ(l.size(), 5);
}

TEST(List, can_check_for_emptyness) {
	List<int> l1(5);

	EXPECT_EQ(l1.empty(), 0);

	List<int> l2;

	EXPECT_EQ(l2.empty(), 1);
}

TEST(List, can_use_move_constructor) {
	List<int> l1(5);

	EXPECT_NO_THROW(List<int> l2(std::move(l1)));
}

TEST(List, date_is_erased_after_moving) {
	List<int> l1(5);
	List<int> l2(std::move(l1));

	EXPECT_EQ(l1.empty(), 1);
}

TEST(List, moved_list_is_equal_to_source_one) {
	List<int> l1(5);

	for (int i = 0; i < 5; i++) {
		l1[i].value = i;
	}

	List<int> tmp(l1);
	List<int> l2(std::move(l1));

	bool isEqual = true;

	for (int i = 0; i < 5; i++) {
		if (tmp[i].value != l2[i].value) isEqual = false;
	}

	EXPECT_TRUE(isEqual);
}

TEST(List, can_get_first_element) {
	List<int> l(5);
	l[0].value = 5;

	EXPECT_EQ(l.front()->value, l[0].value);
}

TEST(List, can_insert_front) {
	List<int> l(5);
	l[0].value = 1;
	l.insert_front(2);

	EXPECT_EQ(l.front()->value, 2);
	EXPECT_EQ(l[1].value, 1);
	EXPECT_EQ(l.size(), 6);
}

TEST(List, can_erase_front) {
	List<int> l(5);
	l[0].value = 1;
	l[1].value = 2;
	l.erase_front();

	EXPECT_EQ(l.front()->value, 2);
	EXPECT_EQ(l.size(), 4);
}

TEST(List, can_insert_after) {
	List<int> l(5);
	l[3].value = 1;
	l[4].value = 2;
	l.insert_after(3, &l[3]);

	EXPECT_EQ(l[3].value, 1);
	EXPECT_EQ(l[4].value, 3);
	EXPECT_EQ(l[5].value, 2);
	EXPECT_EQ(l.size(), 6);
}

TEST(List, can_erase_after) {
	List<int> l(5);
	l[2].value = 1;
	l[3].value = 2;
	l[4].value = 3;
	l.erase_after(&l[2]);

	EXPECT_EQ(l[2].value, 1);
	EXPECT_EQ(l[3].value, 3);
	EXPECT_EQ(l.size(), 4);
}

TEST(List, can_find_element) {
	List<int> l(5);

	l[3].value = 10;

	EXPECT_EQ(l.find(10), &l[3]);
	EXPECT_EQ(l.find(9), nullptr);
}