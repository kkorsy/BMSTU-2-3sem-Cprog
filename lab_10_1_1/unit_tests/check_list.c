#include "check_list.h"
#include "check_node.h"
#include "list.h"
#include <stdlib.h>

void list_check_eq(node_t *list, node_t *expect)
{
    node_t *cur1 = list;
    node_t *cur2 = expect;

    while (cur1 != NULL || cur2 != NULL)
    {
        data_check_eq(cur1->data, cur2->data);

        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    
    if (cur1 != NULL || cur2 != NULL)
        ck_abort();
}

// Создание из файла с некорректными данными
START_TEST(test_create_incorrect)
{
    FILE *f = fopen("func_tests/data/neg_06_in.txt", "r");
    node_t *head = NULL;

    int rc = list_create(f, &head);
    ck_assert_int_eq(rc, READ_ERROR);

    fclose(f);
}
END_TEST

// Создание из пустого файла
START_TEST(test_create_empty)
{
    FILE *f = fopen("func_tests/data/empty.txt", "r");
    node_t *head;

    int rc = list_create(f, &head);
    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(head);

    fclose(f);
}
END_TEST

// Обычное создание
START_TEST(test_create_simple)
{
    FILE *f = fopen("func_tests/data/file_in_1.txt", "r");
    node_t *head = NULL;

    int rc = list_create(f, &head);
    ck_assert_int_eq(rc, OK);

    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head_exp = { &data_head, &middle };
    
    list_check_eq(head, &head_exp);

    list_free(head, node_data_free);
    fclose(f);
}
END_TEST

Suite* list_create_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_create_incorrect);
    tcase_add_test(tc_neg, test_create_empty);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_create_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Обычное копирование
START_TEST(test_copy_simple)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };

    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };

    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    node_t *copy = list_copy(&head);
    list_check_eq(copy, &head);

    list_free(copy, node_free);
}
END_TEST

Suite* list_copy_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_copy_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Добаление в пустой список
START_TEST(test_add_empty)
{
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, NULL };

    node_t *head = NULL;

    head = list_add_end(head, &head_exp);
    list_check_eq(head, &head_exp);
}
END_TEST

// Обычное добавление
START_TEST(test_add_simple)
{
    data_t data_tail_exp = { 25, 320.50 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 78.0 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, NULL };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;

    phead = list_add_end(phead, &tail_exp);
    list_check_eq(phead, &head_exp);
}
END_TEST

// Добавление в список одинаковых элементов
START_TEST(test_add_equal)
{
    data_t data_tail_exp = { 3, 5 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 2, 5 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 1, 5 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    data_t data_middle = { 2, 5 };
    node_t middle = { &data_middle, NULL };
    data_t data_head = { 1, 5 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;

    phead = list_add_end(phead, &tail_exp);
    list_check_eq(phead, &head_exp);
}
END_TEST

Suite* list_add_end_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_add_empty);
    tcase_add_test(tc_pos, test_add_simple);
    tcase_add_test(tc_pos, test_add_equal);

    suite_add_tcase(s, tc_pos);

    return s;
}