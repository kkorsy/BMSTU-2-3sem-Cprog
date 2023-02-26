#ifndef __CHECK_MAIN_H__
#define __CHECK_MAIN_H__

#include <check.h>

/**
 * \fn int array_cmp(void *a1, size_t a_n, void *b1, size_t b_n, int (*cmp)(const void *, const void *), size_t s)
 * \brief Проверка массивов на равенство
 * \param [in] a1 Указатель на первый массив
 * \param [in] a_n Количество элементов первого массива
 * \param [in] b1 Указатель на второй массив
 * \param [in] b_n Количество элементов второго массива
 * \param [in] cmp Указатель на функцию сравнения
 * \param [in] s Размер одного элемента массива
 * \return Результат проверки
 */
int array_cmp(void *a1, size_t a_n, void *b1, size_t b_n, int (*cmp)(const void *, const void *), size_t s);

/**
 * \fn int cmp_double(const void *pl, const void *pr)
 * \brief Сравнение вещественных чисел
 * \param [in] pl Указатель на первый элемент
 * \param [in] pr Указатель на второй элемент
 * \return Результат сравнения
 */
int cmp_double(const void *pl, const void *pr);

/**
 * \fn int cmp_char(const void *pl, const void *pr)
 * \brief Сравнение символов
 * \param [in] pl Указатель на первый элемент
 * \param [in] pr Указатель на второй элемент
 * \return Результат сравнения
 */
int cmp_char(const void *pl, const void *pr);

#endif
