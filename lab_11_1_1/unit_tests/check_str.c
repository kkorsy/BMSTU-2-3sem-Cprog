#include "check_str.h"
#include "str.h"

// Обычный тест
START_TEST(test_ws_simple)
{
    char buf[10];
    char substr[] = "string";
    size_t num = 10;

    int c = write_str(buf, num, substr);
    ck_assert_int_eq(c, 6);
    buf[6] = '\0';

    ck_assert_str_eq(buf, substr);
}
END_TEST

// Доступная длина для записи = 0
START_TEST(test_ws_zero_len)
{
    char *buf = NULL;
    char substr[] = "string12";
    size_t num = 0;

    int c = write_str(buf, num, substr);
    ck_assert_int_eq(c, 8);

    ck_assert_ptr_null(buf);
}
END_TEST

// Доступная длина для записи = 1
START_TEST(test_ws_one_len)
{
    char buf[2];
    char substr[] = "string";
    size_t num = 1;

    int c = write_str(buf, num, substr);
    ck_assert_int_eq(c, 6);
    buf[1] = '\0';

    ck_assert_str_eq(buf, "s");
}
END_TEST

// Подстрока пустая
START_TEST(test_ws_empty_substr)
{
    char buf[10];
    char substr[] = "";
    size_t num = 10;

    int c = write_str(buf, num, substr);
    ck_assert_int_eq(c, 0);
    buf[0] = '\0';

    ck_assert_str_eq(buf, substr);
}
END_TEST

// Подстрока больше буфера
START_TEST(test_ws_more_buf)
{
    char buf[10];
    char substr[] = "string789012";
    size_t num = 10;

    int c = write_str(buf, num - 1, substr);
    ck_assert_int_eq(c, 12);
    buf[9] = '\0';

    ck_assert_str_eq(buf, "string789");
}
END_TEST

// Дозапись в конец
START_TEST(test_ws_end)
{
    char buf[10] = "123";
    char substr[] = "string";
    size_t num = 10;

    int c = write_str(buf + 3, num, substr);
    ck_assert_int_eq(c, 6);
    buf[9] = '\0';

    ck_assert_str_eq(buf, "123string");
}
END_TEST

Suite* write_str_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_ws_simple);
    tcase_add_test(tc_pos, test_ws_zero_len);
    tcase_add_test(tc_pos, test_ws_one_len);
    tcase_add_test(tc_pos, test_ws_empty_substr);
    tcase_add_test(tc_pos, test_ws_more_buf);
    tcase_add_test(tc_pos, test_ws_end);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Обычный тест
START_TEST(test_wo_simple)
{
    char buf[10];
    unsigned int oct = 12345;
    size_t num = 10;

    int c = write_oct(buf, num, oct);
    ck_assert_int_eq(c, 5);
    buf[5] = '\0';

    ck_assert_str_eq(buf, "12345");
}
END_TEST

// Запись нуля
START_TEST(test_wo_zero)
{
    char buf[10];
    unsigned int oct = 0;
    size_t num = 10;

    int c = write_oct(buf, num, oct);
    ck_assert_int_eq(c, 1);
    buf[1] = '\0';

    ck_assert_str_eq(buf, "0");
}
END_TEST

Suite* write_oct_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_wo_simple);
    tcase_add_test(tc_pos, test_wo_zero);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Перевод нуля
START_TEST(test_itc_zero)
{
    char x = int_to_char(0);

    ck_assert_int_eq(x, '0');
}
END_TEST

// Перевод 5
START_TEST(test_itc_five)
{
    char x = int_to_char(5);

    ck_assert_int_eq(x, '5');
}
END_TEST

// Перевод 9
START_TEST(test_itc_nine)
{
    char x = int_to_char(9);

    ck_assert_int_eq(x, '9');
}
END_TEST

Suite* int_to_char_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_itc_zero);
    tcase_add_test(tc_pos, test_itc_five);
    tcase_add_test(tc_pos, test_itc_nine);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Длина 1
START_TEST(test_nl_one)
{
    int len = num_len(0);

    ck_assert_int_eq(len, 1);
}
END_TEST

// Длина 2
START_TEST(test_nl_two)
{
    int len = num_len(10);

    ck_assert_int_eq(len, 2);
}
END_TEST

// Длина 10
START_TEST(test_nl_ten)
{
    int len = num_len(1234567890);

    ck_assert_int_eq(len, 10);
}
END_TEST

Suite* num_len_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_nl_one);
    tcase_add_test(tc_pos, test_nl_two);
    tcase_add_test(tc_pos, test_nl_ten);

    suite_add_tcase(s, tc_pos);

    return s;
}

// Перевод нуля
START_TEST(test_convert_zero)
{
    unsigned int oct = convert_to_oct(0);

    ck_assert_uint_eq(oct, 0);
}
END_TEST

// Перевод 1
START_TEST(test_convert_one)
{
    unsigned int oct = convert_to_oct(1);

    ck_assert_uint_eq(oct, 1);
}
END_TEST

// Перевод 64
START_TEST(test_convert_degree)
{
    unsigned int oct = convert_to_oct(64);

    ck_assert_uint_eq(oct, 100);
}
END_TEST

// Обычный тест
START_TEST(test_convert_simple)
{
    unsigned int oct = convert_to_oct(12345);

    ck_assert_uint_eq(oct, 30071);
}
END_TEST

Suite* convert_to_oct_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_convert_zero);
    tcase_add_test(tc_pos, test_convert_one);
    tcase_add_test(tc_pos, test_convert_degree);
    tcase_add_test(tc_pos, test_convert_simple);

    suite_add_tcase(s, tc_pos);

    return s;
}
