#include "check_operations.h"
#include "operations.h"
#include "check_node.h"
#include "check_list.h"
#include "list.h"
#include <stdlib.h>

// Все элементы списка одинаковы
START_TEST(test_rm_equal)
{
    data_t data_tail = { 15, 139.99 };
    node_t *ptail = malloc(sizeof(node_t));
    ptail->data = &data_tail;
    ptail->next = NULL;
    data_t data_middle = { 15, 139.99 };
    node_t *pmiddle = malloc(sizeof(node_t));
    pmiddle->data = &data_middle;
    pmiddle->next = ptail;
    data_t data_head = { 15, 139.99 };
    node_t *phead = malloc(sizeof(node_t));
    phead->data = &data_head;
    phead->next = pmiddle;

    remove_duplicates(&phead, comparator);

    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, NULL };

    list_check_eq(phead, &head_exp);
    list_free(phead, node_free);
}
END_TEST

// Каждый элемент повторяется 2 раза
START_TEST(test_rm_twice)
{
    data_t data_tail2 = { 15, 139.99 };
    node_t *ptail2 = malloc(sizeof(node_t));
    ptail2->data = &data_tail2;
    ptail2->next = NULL;

    data_t data_tail1 = { 15, 139.99 };
    node_t *ptail1 = malloc(sizeof(node_t));
    ptail1->data = &data_tail1;
    ptail1->next = ptail2;

    data_t data_middle2 = { 20, 320.50 };
    node_t *pmiddle2 = malloc(sizeof(node_t));
    pmiddle2->data = &data_middle2;
    pmiddle2->next = ptail1;

    data_t data_middle1 = { 20, 320.50 };
    node_t *pmiddle1 = malloc(sizeof(node_t));
    pmiddle1->data = &data_middle1;
    pmiddle1->next = pmiddle2;

    data_t data_head2 = { 25, 78.0 };
    node_t *phead2 = malloc(sizeof(node_t));
    phead2->data = &data_head2;
    phead2->next = pmiddle1;

    data_t data_head1 = { 25, 78.0 };
    node_t *phead1 = malloc(sizeof(node_t));
    phead1->data = &data_head1;
    phead1->next = phead2;

    remove_duplicates(&phead1, comparator);

    data_t data_tail_exp = { 15, 139.99 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 320.50 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 25, 78.0 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead1, &head_exp);
    list_free(phead1, node_free);
}
END_TEST

// В списке нет повторений
START_TEST(test_rm_no_repeats)
{
    data_t data_tail = { 15, 139.99 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 320.50 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 25, 78.0 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;

    remove_duplicates(&phead, comparator);

    data_t data_tail_exp = { 15, 139.99 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 320.50 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 25, 78.0 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

Suite* remove_duplicates_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_rm_equal);
    tcase_add_test(tc_pos, test_rm_twice);
    tcase_add_test(tc_pos, test_rm_no_repeats);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Первый элемент больше второго
START_TEST(test_cmp_more)
{
    data_t left = { 1, 1.001 };
    data_t right = { 1, 1 };

    int rc = comparator(&left, &right);
    ck_assert_int_eq(rc, 1);
}
END_TEST

// Первый элемент меньше второго
START_TEST(test_cmp_less)
{
    data_t left = { 1, 5 };
    data_t right = { 1, 10 };

    int rc = comparator(&left, &right);
    ck_assert_int_eq(rc, -1);
}
END_TEST

// Элементы равны
START_TEST(test_cmp_equal)
{
    data_t left = { 1, 1.5 };
    data_t right = { 1, 1.5 };

    int rc = comparator(&left, &right);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite* comparator_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_cmp_more);
    tcase_add_test(tc_pos, test_cmp_less);
    tcase_add_test(tc_pos, test_cmp_equal);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Вставка в пустой список
START_TEST(test_sorted_insert_empty)
{
    node_t *head = NULL;

    data_t data_ins = { 1, 10 };
    node_t ins = { &data_ins, NULL };
    
    sorted_insert(&head, &ins, comparator);

    data_t data_head_exp = { 1, 10 };
    node_t head_exp = { &data_head_exp, NULL };

    list_check_eq(head, &head_exp);
}
END_TEST

// Вставка в конец упорядоченного списка
START_TEST(test_sorted_insert_end)
{
    data_t data_tail = { 2, 100 };
    node_t tail = { &data_tail, NULL };
    data_t data_head = { 1, 50 };
    node_t head = { &data_head, &tail };

    data_t data_ins = { 3, 150 };
    node_t ins = { &data_ins, NULL };

    node_t *phead = &head;
    
    sorted_insert(&phead, &ins, comparator);

    data_t data_tail_exp = { 3, 150 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 2, 100 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 1, 50 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

// Вставка в начало упорядоченного списка
START_TEST(test_sorted_insert_head)
{
    data_t data_tail = { 3, 150 };
    node_t tail = { &data_tail, NULL };
    data_t data_head = { 2, 100 };
    node_t head = { &data_head, &tail };

    data_t data_ins = { 1, 50 };
    node_t ins = { &data_ins, NULL };

    node_t *phead = &head;

    sorted_insert(&phead, &ins, comparator);

    data_t data_tail_exp = { 3, 150 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 2, 100 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 1, 50 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(&ins, &head_exp);
}
END_TEST

// Вставка в список, состоящий из одинаковых элементов
START_TEST(test_sorted_insert_equal)
{
    data_t data_tail = { 1, 10 };
    node_t tail = { &data_tail, NULL };
    data_t data_head = { 1, 10 };
    node_t head = { &data_head, &tail };

    data_t data_ins = { 1, 10 };
    node_t ins = { &data_ins, NULL };

    node_t *phead = &head;
    
    sorted_insert(&phead, &ins, comparator);

    data_t data_tail_exp = { 1, 10 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 1, 10 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 1, 10 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

Suite* sorted_insert_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sorted_insert_empty);
    tcase_add_test(tc_pos, test_sorted_insert_end);
    tcase_add_test(tc_pos, test_sorted_insert_head);
    tcase_add_test(tc_pos, test_sorted_insert_equal);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Обычный тест сортировки
START_TEST(test_sort_simple)
{
    data_t data_tail = { 25, 100 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 50};
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 150 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;
    phead = sort(phead, comparator);

    data_t data_tail_exp = { 15, 150 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 25, 100 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 20, 50 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

// Список отсортирован
START_TEST(test_sort_sorted)
{
    data_t data_tail = { 15, 150 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 25, 100 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 20, 50 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;
    phead = sort(phead, comparator);

    data_t data_tail_exp = { 15, 150 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 25, 100 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 20, 50 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

// Список отсортирован в обратном порядке
START_TEST(test_sort_reversed)
{
    data_t data_tail = { 20, 50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 25, 100 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 150 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;
    phead = sort(phead, comparator);

    data_t data_tail_exp = { 15, 150 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 25, 100 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 20, 50 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

// В списке 1 элемент
START_TEST(test_sort_one_elem)
{
    data_t data_head = { 15, 100 };
    node_t head = { &data_head, NULL };

    node_t *phead = &head;
    phead = sort(phead, comparator);

    data_t data_head_exp = { 15, 100 };
    node_t head_exp = { &data_head_exp, NULL };

    list_check_eq(phead, &head_exp);
}
END_TEST

Suite* sort_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_simple);
    tcase_add_test(tc_pos, test_sort_sorted);
    tcase_add_test(tc_pos, test_sort_reversed);
    tcase_add_test(tc_pos, test_sort_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Вставка в пустой список
START_TEST(test_insert_empty)
{
    node_t *head = NULL;

    data_t data_ins = { 5, 1 };
    node_t ins = { &data_ins, NULL };

    insert(&head, &ins, NULL);
    
    ck_assert_ptr_null(head);
}
END_TEST

// Вставка до головы списка
START_TEST(test_insert_before_head)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    data_t data_ins = { 5, 1 };
    node_t ins = { &data_ins, NULL };

    node_t *phead = &head;

    insert(&phead, &ins, &head);

    data_t data_tail_exp = { 25, 320.50 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 78.0 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, &middle_exp };
    data_t data_ins_exp = { 5, 1 };
    node_t ins_exp = { &data_ins_exp, &head_exp };

    list_check_eq(phead, &ins_exp);
}
END_TEST

// Обычный тест вставки
START_TEST(test_insert_simple)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    data_t data_ins = { 5, 1 };
    node_t ins = { &data_ins, NULL };

    node_t *phead = &head;

    insert(&phead, &ins, &middle);

    data_t data_tail_exp = { 25, 320.50 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 78.0 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_ins_exp = { 5, 1 };
    node_t ins_exp = { &data_ins_exp, &middle_exp };
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, &ins_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

// Некорректный указатель на элемент, перед которым нужно вставить новый
START_TEST(test_insert_err)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    data_t data_ins = { 5, 1 };
    node_t ins = { &data_ins, NULL };

    node_t *phead = &head;

    insert(&phead, &ins, NULL);

    data_t data_tail_exp = { 25, 320.50 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 78.0 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

Suite* insert_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_insert_err);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_insert_simple);
    tcase_add_test(tc_pos, test_insert_before_head);
    tcase_add_test(tc_pos, test_insert_empty);

    suite_add_tcase(s, tc_pos);

    return s;
}

// В списке один элемент
START_TEST(test_find_one_elem)
{
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, NULL };

    node_t *prev;
    int rc = find_prev(&head, &prev, &head);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(prev);

    node_t *find = find_elem(&head, data_head.price);
    ck_assert_ptr_eq(find, &head);
}
END_TEST

// Поиск предыдущего у головы списка
START_TEST(test_find_head)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    node_t *prev;
    int rc = find_prev(&head, &prev, &head);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_null(prev);
}
END_TEST

// Обычный поиск
START_TEST(test_find_simple)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    node_t *prev;
    int rc = find_prev(&head, &prev, &middle);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_eq(prev, &head);

    node_t *find = find_elem(&head, data_middle.price);
    ck_assert_ptr_eq(find, &middle);
}
END_TEST

// Элемент не найден
START_TEST(test_find_err)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    data_t data = { 5, 1 };
    node_t node = { &data, NULL };

    node_t *prev;
    int rc = find_prev(&head, &prev, &node);
    ck_assert_int_eq(rc, NOT_FOUND_ERROR);

    node_t *find = find_elem(&head, data.price);
    ck_assert_ptr_null(find);
}
END_TEST

Suite* find_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_find_err);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_simple);
    tcase_add_test(tc_pos, test_find_head);
    tcase_add_test(tc_pos, test_find_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Список пустой
START_TEST(test_del_empty)
{
    node_t *head = NULL;
    data_t data_elem = { 5, 1 };
    node_t elem = { &data_elem, NULL };

    head = del_elem(head, &elem);
    ck_assert_ptr_null(head);
}
END_TEST

// В списке 1 элемент
START_TEST(test_del_one_elem)
{
    data_t data_head = { 15, 139.99 };
    node_t *phead = malloc(sizeof(node_t));
    phead->data = &data_head;
    phead->next = NULL;

    phead = del_elem(phead, phead);

    ck_assert_ptr_null(phead);
}
END_TEST

// Удаление первого элемента списка
START_TEST(test_del_head)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };
    data_t data_head = { 15, 139.99 };
    node_t *phead = malloc(sizeof(node_t));
    phead->data = &data_head;
    phead->next = &middle;

    phead = del_elem(phead, phead);

    data_t data_tail_exp = { 25, 320.50 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_middle_exp = { 20, 78.0 };
    node_t middle_exp = { &data_middle_exp, &tail_exp };

    list_check_eq(phead, &middle_exp);
}
END_TEST

// Удаление последнего элемента списка
START_TEST(test_del_tail)
{
    data_t data_tail = { 25, 320.50 };
    node_t *ptail = malloc(sizeof(node_t));
    ptail->data = &data_tail;
    ptail->next = NULL;
    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, ptail };
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, &middle };

    node_t *phead = &head;
    phead = del_elem(phead, ptail);

    data_t data_middle_exp = { 20, 78.0 };
    node_t middle_exp = { &data_middle_exp, NULL };
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, &middle_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

// Обычное удаление
START_TEST(test_del_middle)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };
    data_t data_middle = { 20, 78.0 };
    node_t *pmiddle = malloc(sizeof(node_t));
    pmiddle->data = &data_middle;
    pmiddle->next = &tail;
    data_t data_head = { 15, 139.99 };
    node_t head = { &data_head, pmiddle };

    node_t *phead = &head;
    phead = del_elem(phead, pmiddle);

    data_t data_tail_exp = { 25, 320.50 };
    node_t tail_exp = { &data_tail_exp, NULL };
    data_t data_head_exp = { 15, 139.99 };
    node_t head_exp = { &data_head_exp, &tail_exp };

    list_check_eq(phead, &head_exp);
}
END_TEST

Suite* del_elem_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_del_empty);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_del_one_elem);
    tcase_add_test(tc_pos, test_del_head);
    tcase_add_test(tc_pos, test_del_tail);
    tcase_add_test(tc_pos, test_del_middle);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Список пустой
START_TEST(test_pop_empty)
{
    data_t *data_1 = pop_front(NULL);

    node_t *head = NULL;
    data_t *data_2 = pop_front(&head);
    
    ck_assert_ptr_null(data_1);
    ck_assert_ptr_null(data_2);
}
END_TEST

// Обычный тест
START_TEST(test_pop_simple)
{
    data_t data_tail = { 25, 320.50 };
    node_t tail = { &data_tail, NULL };

    data_t data_middle = { 20, 78.0 };
    node_t middle = { &data_middle, &tail };

    data_t data_head = { 15, 139.99 };

    node_t *phead = malloc(sizeof(node_t));
    phead->data = &data_head;
    phead->next = &middle;

    data_t *data_res = pop_front(&phead);

    data_check_eq(data_res, &data_head);
    list_check_eq(phead, &middle);
}
END_TEST

// В списке 1 элемент
START_TEST(test_pop_one_elem)
{
    data_t data_head = { 15, 329.99 };
    node_t *phead = malloc(sizeof(node_t));
    phead->data = &data_head;
    phead->next = NULL;

    data_t *data_res = pop_front(&phead);

    data_check_eq(data_res, &data_head);
    ck_assert_ptr_null(phead);
}
END_TEST

Suite* pop_front_suite(Suite *s)
{
    TCase *tc_neg, *tc_pos;

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_pop_empty);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_pop_simple);
    tcase_add_test(tc_pos, test_pop_one_elem);

    suite_add_tcase(s, tc_pos);

    return s;
}