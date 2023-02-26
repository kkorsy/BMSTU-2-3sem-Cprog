#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "list.h"

/**
 * \brief Вычисляет значение P(a)
 * \param [in] head Исходный список
 * \param [in] a Число, для которого необходимо посчитать значение
 * \return Значение P(a)
 */
int calc(node_t *head, int a);

/**
 * \brief Считает производную P(x)
 * \param [in] head Исходный список
 * \return Указатель на исходный список, значения которого были изменены
 */
node_t *derive(node_t *head);

/**
 * \brief Складывает 2 полинома
 * \param [in] head_1 Первый полином
 * \param [in] head_2 Второй полином
 * \return Указатель на новый список-сумму
 */
node_t *summation(node_t *head_1, node_t *head_2);

/**
 * \brief Разделяет полином на 2 списка
 * \param [in] head_src Исходный список
 * \param [out] head_even Список четных элементов
 * \param [out] head_odd Список нечетных элементов
 */
void separation(node_t *head_src, node_t **head_even, node_t **head_odd);

#endif