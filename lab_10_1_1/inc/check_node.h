#ifndef __CHECK_NODE_H__
#define __CHECK_NODE_H__

#include <check.h>
#include "node.h"

void data_check_eq(data_t *data, data_t *expect);

Suite* data_read_suite(Suite *s);
Suite* data_init_suite(Suite *s);

#endif