#ifndef __CHECK_OPERATIONS_H__
#define __CHECK_OPERATIONS_H__

#include <check.h>

Suite* remove_duplicates_suite(Suite *s);
Suite* comparator_suite(Suite *s);
Suite* sorted_insert_suite(Suite *s);
Suite* sort_suite(Suite *s);
Suite* insert_suite(Suite *s);
Suite* find_suite(Suite *s);
Suite* del_elem_suite(Suite *s);
Suite* pop_front_suite(Suite *s);

#endif