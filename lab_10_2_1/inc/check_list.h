#ifndef __CHECK_LIST_H__
#define __CHECK_LIST_H__

#include <check.h>
#include "node.h"

void check_node_eq(node_t *node_exp, node_t *node);
void check_list_eq(node_t *head_exp, node_t *head);

Suite* add_tail_suite(Suite *s);
Suite* copy_suite(Suite *s);
Suite* del_suite(Suite *s);
Suite* find_prev_suite(Suite *s);

#endif