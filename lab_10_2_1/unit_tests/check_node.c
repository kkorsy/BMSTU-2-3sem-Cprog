#include "check_node.h"
#include "node.h"

// Присваиваются нулевые значения
START_TEST(test_nc_zero)
{
    node_t *node = node_create(0, 0);

    ck_assert_int_eq(node->k, 0);
    ck_assert_int_eq(node->p, 0);
    ck_assert_ptr_null(node->next);

    node_free(node);
}
END_TEST

// Обычный тест
START_TEST(test_nc_simple)
{
    node_t *node = node_create(-4, 12);
    
    ck_assert_int_eq(node->k, -4);
    ck_assert_int_eq(node->p, 12);
    ck_assert_ptr_null(node->next);

    node_free(node);
}
END_TEST

Suite* node_create_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_nc_zero);
    tcase_add_test(tc_pos, test_nc_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
