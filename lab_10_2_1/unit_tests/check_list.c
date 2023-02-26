#include "check_list.h"
#include "list.h"
#include <stdlib.h>

void check_node_eq(node_t *node_exp, node_t *node)
{
    ck_assert_int_eq(node_exp->k, node->k);
    ck_assert_int_eq(node_exp->p, node->p);
}

void check_list_eq(node_t *head_exp, node_t *head)
{
    while (head_exp != NULL && head != NULL)
    {
        check_node_eq(head_exp, head);
        head_exp = head_exp->next;
        head = head->next;
    }
}

// Добавление в пустой список
START_TEST(test_add_empty)
{
    node_t *head = NULL;
    node_t elem = { 1, 1, NULL };

    head = list_add_tail(head, &elem);
    check_list_eq(&elem, head);
}
END_TEST

// Добавление в непустой список
START_TEST(test_add_not_empty)
{
    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };
    node_t head = { 1, 1, &middle };

    node_t elem = { 4, 4, NULL };

    node_t *res = list_add_tail(&head, &elem);

    node_t elem_exp = { 4, 4, NULL };
    node_t tail_exp = { 3, 3, &elem_exp };
    node_t middle_exp = { 2, 2, &tail_exp };
    node_t head_exp = { 1, 1, &middle_exp };

    check_list_eq(&head_exp, res);
}
END_TEST

Suite* add_tail_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_add_empty);
    tcase_add_test(tc_pos, test_add_not_empty);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Сложение списков
START_TEST(test_copy_not_empty)
{
    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };
    node_t head_1 = { 1, 1, &middle };

    node_t *head = malloc(sizeof(node_t));
    head->k = 0;
    head->p = 0;
    head->next = NULL;

    head = list_copy(&head_1, head);

    node_t new_head = { 0, 0, &head_1};
    check_list_eq(&new_head, head);

    list_free(head);
}
END_TEST

// Копирование пустого списка
START_TEST(test_copy_null)
{
    node_t *head_exp = NULL;

    node_t *head = NULL;
    head = list_copy(head_exp, head);

    check_list_eq(head_exp, head);
}
END_TEST

// Копирование одного элемента
START_TEST(test_copy_one_elem)
{
    node_t head_exp = { 1, 1, NULL };

    node_t *head = NULL;
    head = list_copy(&head_exp, head);

    check_list_eq(&head_exp, head);
    list_free(head);
}
END_TEST

// Обычный тест копирования
START_TEST(test_copy_simple)
{
    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };
    node_t head_exp = { 1, 1, &middle };

    node_t *head = NULL;
    head = list_copy(&head_exp, head);

    check_list_eq(&head_exp, head);
    list_free(head);
}
END_TEST

Suite* copy_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_copy_null);
    tcase_add_test(tc_pos, test_copy_one_elem);
    tcase_add_test(tc_pos, test_copy_simple);
    tcase_add_test(tc_pos, test_copy_not_empty);


    suite_add_tcase(s, tc_pos);

    return s;
}

// Обычное удаление
START_TEST(test_del_simple)
{
    node_t *node_3 = node_create(3, 3);
    node_t *node_2 = node_create(2, 2);
    node_t *node_1 = node_create(1, 1);

    node_3->next = NULL;
    node_2->next = node_3;
    node_1->next = node_2;

    node_1 = list_del_elem(node_1, node_2);

    node_t tail = { 3, 3, NULL };
    node_t head_exp = { 1, 1, &tail };

    check_list_eq(&head_exp, node_1);
    list_free(node_1);
}
END_TEST

// Удаление последнего
START_TEST(test_del_tail)
{
    node_t *node_3 = node_create(3, 3);
    node_t *node_2 = node_create(2, 2);
    node_t *node_1 = node_create(1, 1);

    node_3->next = NULL;
    node_2->next = node_3;
    node_1->next = node_2;

    node_1 = list_del_elem(node_1, node_3);

    node_t middle = { 2, 2, NULL };
    node_t head_exp = { 1, 1, &middle };

    check_list_eq(&head_exp, node_1);
    list_free(node_1);
}
END_TEST

// Удаление первого
START_TEST(test_del_head)
{
    node_t *node_3 = node_create(3, 3);
    node_t *node_2 = node_create(2, 2);
    node_t *node_1 = node_create(1, 1);

    node_3->next = NULL;
    node_2->next = node_3;
    node_1->next = node_2;

    node_1 = list_del_elem(node_1, node_1);

    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };

    check_list_eq(&middle, node_1);
    list_free(node_1);
}
END_TEST

Suite* del_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_del_simple);
    tcase_add_test(tc_pos, test_del_tail);
    tcase_add_test(tc_pos, test_del_head);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Поиск предыдущего у хвоста
START_TEST(test_fp_tail)
{
    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };
    node_t head = { 1, 1, &middle };

    node_t *find = list_find_prev(&head, &tail);
    check_node_eq(find, &middle);
}
END_TEST

// Поиск предыдущего у головы
START_TEST(test_fp_head)
{
    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };
    node_t head = { 1, 1, &middle };

    node_t *find = list_find_prev(&head, &head);
    ck_assert_ptr_null(find);
}
END_TEST

// Обычный поиск предыдущего
START_TEST(test_fp_simple)
{
    node_t tail = { 3, 3, NULL };
    node_t middle = { 2, 2, &tail };
    node_t head = { 1, 1, &middle };

    node_t *find = list_find_prev(&head, &middle);
    check_node_eq(find, &head);
}
END_TEST

Suite* find_prev_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_fp_tail);
    tcase_add_test(tc_pos, test_fp_head);
    tcase_add_test(tc_pos, test_fp_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}