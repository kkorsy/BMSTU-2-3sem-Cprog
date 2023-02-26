#ifndef __CHECK_LIST_H__
#define __CHECK_LIST_H__

#include <check.h>
#include "node.h"

void list_check_eq(node_t *list, node_t *expect);

Suite* list_create_suite(Suite *s);
Suite* list_copy_suite(Suite *s);
Suite* list_add_end_suite(Suite *s);

#endif