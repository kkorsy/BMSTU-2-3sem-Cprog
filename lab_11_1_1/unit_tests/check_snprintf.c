#include <stdio.h>
#include "check_snprintf.h"
#include "snprintf.h"
#include <stdlib.h>

// Размер буфера больше строки
START_TEST(test_sn_big_buf)
{
    char *buf = malloc(20);
    char *buf_exp = malloc(20);
    char str[] = "some string";

    int w1 = my_snprintf(buf, 20, "%s", str);
    int w2 = snprintf(buf_exp, 20, "%s", str);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Размер буфера равен размеру строки
START_TEST(test_sn_eq_buf)
{
    char *buf = malloc(3);
    char *buf_exp = malloc(3);
    unsigned int x = 9;

    int w1 = my_snprintf(buf, 3, "%o", x);
    int w2 = snprintf(buf_exp, 3, "%o", x);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// В строке форматирования только спецификаторы
START_TEST(test_sn_only_spec)
{
    char *buf = malloc(10);
    char *buf_exp = malloc(10);
    char s1[] = "s1", s2[] = "s2", s3[] = "s3";
    unsigned int x1 = 1, x2 = 32;

    int w1 = my_snprintf(buf, 10, "%s%o  %o%s %s", s1, x1, x2, s2, s3);
    int w2 = snprintf(buf_exp, 10, "%s%o  %o%s %s", s1, x1, x2, s2, s3);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Нет ни одного спецификатора
START_TEST(test_sn_no_spec)
{
    char *buf = malloc(15);
    char *buf_exp = malloc(15);

    int w1 = my_snprintf(buf, 15, "test no spec");
    int w2 = snprintf(buf_exp, 15, "test no spec");

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// В строке форматирования и символы и спецификаторы
START_TEST(test_sn_symb_spec)
{
    char *buf = malloc(30);
    char *buf_exp = malloc(30);
    char s1[] = "s1", s2[] = "s2s";
    unsigned int x = 151;

    int w1 = my_snprintf(buf, 30, "test %o!!!    %s end %s\n", x, s1, s2);
    int w2 = snprintf(buf_exp, 30, "test %o!!!    %s end %s\n", x, s1, s2);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Запись пустой строки
START_TEST(test_sn_empty_str)
{
    char *buf = malloc(5);
    char *buf_exp = malloc(5);
    char s[] = "";

    int w1 = my_snprintf(buf, 5, "%s", s);
    int w2 = snprintf(buf_exp, 5, "%s", s);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Строка обрезается
START_TEST(test_sn_cut)
{
    char *buf = malloc(10);
    char *buf_exp = malloc(10);
    unsigned int x = 1000;

    int w1 = my_snprintf(buf, 3, "%o", x);
    int w2 = snprintf(buf_exp, 3, "%o", x);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Размер буфера 0
START_TEST(test_sn_zero_buf)
{
    char *buf = malloc(10);
    char *buf_exp = malloc(10);
    char str[] = "string";

    int w1 = my_snprintf(buf, 0, "%s", str);
    int w2 = snprintf(buf_exp, 0, "%s", str);

    ck_assert_int_eq(w1, w2);

    free(buf);
    free(buf_exp);
}
END_TEST

// Максимальное число
START_TEST(test_sn_max_unsigned)
{
    char buf[10];
    char buf_exp[10];
    unsigned int x = -1;

    int w1 = my_snprintf(buf, 10, "%o", x);
    int w2 = snprintf(buf_exp, 10, "%o", x);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);
}
END_TEST

// Обрезается строка форматирования
START_TEST(test_sn_cut_str_form)
{
    char *buf = malloc(10);
    char *buf_exp = malloc(10);
    char str[] = "a";
    char str_form[] = "AAAAAAAAA%s";

    int w1 = my_snprintf(buf, 3, str_form, str);
    int w2 = snprintf(buf_exp, 3, str_form, str);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// В строке форматирования только строки
START_TEST(test_sn_only_str)
{
    char *buf = malloc(20);
    char *buf_exp = malloc(20);
    char s1[] = "abc", s2[] = "def", s3[] = "ghi";
    char str_form[] = "%s %s %s";

    int w1 = my_snprintf(buf, 20, str_form, s1, s2, s3);
    int w2 = snprintf(buf_exp, 20, str_form, s1, s2, s3);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Записывается 1 символ
START_TEST(test_sn_one_symb)
{
    char *buf = malloc(2);
    char *buf_exp = malloc(2);
    char s[] = "abcd";
    char str_form[] = "%s";

    int w1 = my_snprintf(buf, 2, str_form, s);
    int w2 = snprintf(buf_exp, 2, str_form, s);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Размер буфера 1
START_TEST(test_sn_buf_one)
{
    char *buf = malloc(1);
    char *buf_exp = malloc(1);
    char s[] = "abcd";
    char str_form[] = "%s";

    int w1 = my_snprintf(buf, 1, str_form, s);
    int w2 = snprintf(buf_exp, 1, str_form, s);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);

    free(buf);
    free(buf_exp);
}
END_TEST

// Буфер null
START_TEST(test_sn_null_buf)
{
    char *buf = NULL;
    char str_form[] = "%s %o";

    int w1 = my_snprintf(buf, 3, str_form, "ab", 8);
    ck_assert_int_eq(w1, -1);

    w1 = my_snprintf(buf, 0, "abcdef");
    int w2 = snprintf(buf, 0, "abcdef");
    ck_assert_int_eq(w1, w2);

    w1 = my_snprintf(buf, 0, str_form, "ab", 8);
    w2 = snprintf(buf, 0, str_form, "ab", 8);
    ck_assert_int_eq(w1, w2);
}
END_TEST

// Строка форматирования null
START_TEST(test_sn_null_form)
{
    char buf[10];
    char *str_form = NULL;

    int w1 = my_snprintf(buf, 10, str_form);
    ck_assert_int_eq(w1, -1);
}
END_TEST

// Строка-параметр null
START_TEST(test_sn_null_str)
{
    char buf[10];
    char buf_exp[10];
    char *s = NULL;
    char str_form[] = "%s abcd";

    int w1 = my_snprintf(buf, 10, str_form, s);
    int w2 = snprintf(buf_exp, 10, str_form, s);

    ck_assert_int_eq(w1, w2);
    ck_assert_str_eq(buf, buf_exp);
}
END_TEST

// Строка форматирования пустая
START_TEST(test_sn_empty_form)
{
    char buf[10];
    char str_form[] = "";

    int w1 = my_snprintf(buf, 10, str_form);

    ck_assert_int_eq(w1, 0);
}
END_TEST

// Один знак процента
START_TEST(test_sn_one_percent)
{
    char *buf = malloc(10);
    char str_form[] = "abc %";

    int w1 = my_snprintf(buf, 10, str_form);

    ck_assert_int_eq(w1, -1);

    free(buf);
}
END_TEST

Suite* my_snprintf_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sn_big_buf);
    tcase_add_test(tc_pos, test_sn_eq_buf);
    tcase_add_test(tc_pos, test_sn_only_spec);
    tcase_add_test(tc_pos, test_sn_no_spec);
    tcase_add_test(tc_pos, test_sn_symb_spec);
    tcase_add_test(tc_pos, test_sn_empty_str);
    tcase_add_test(tc_pos, test_sn_cut);
    tcase_add_test(tc_pos, test_sn_zero_buf);
    tcase_add_test(tc_pos, test_sn_max_unsigned);
    tcase_add_test(tc_pos, test_sn_cut_str_form);
    tcase_add_test(tc_pos, test_sn_only_str);
    tcase_add_test(tc_pos, test_sn_one_symb);
    tcase_add_test(tc_pos, test_sn_buf_one);
    tcase_add_test(tc_pos, test_sn_null_buf);
    tcase_add_test(tc_pos, test_sn_null_form);
    tcase_add_test(tc_pos, test_sn_null_str);
    tcase_add_test(tc_pos, test_sn_empty_form);
    tcase_add_test(tc_pos, test_sn_one_percent);

    suite_add_tcase(s, tc_pos);

    return s;
}