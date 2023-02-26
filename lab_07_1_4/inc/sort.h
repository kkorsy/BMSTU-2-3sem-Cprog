#ifndef __SORT_H__
#define __SORT_H__

#include "stdio.h"
#include "errors.h"

/**
 * Универсальная сортировка массива
 * \param [in] base Указатель на начало массива
 * \param [in] n Количество элементов в массиве
 * \param [in] elem_size Размер каждого элемента
 * \param [in] cmp Указатель на функцию сравнения
 */
void mysort(void *base, size_t n, size_t elem_size, int (*cmp)(const void *, const void *));

/**
 * Сравнение целых чисел
 * \param [in] pl Указатель на первый элемент
 * \param [in] pr Указатель на второй элемент
 * \return Результат сравнения
 */
int cmp(const void *pl, const void *pr);

/**
 * Перестановка двух элементов
 * \param [in] pl Указатель на первый элемент
 * \param [in] pr Указатель на второй элемент
 * \param [in] elem_size Размер элементов
 */
void swap(void *pl, void *pr, size_t elem_size);

#endif
