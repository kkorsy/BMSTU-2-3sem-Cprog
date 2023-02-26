#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include "errors.h"
#include "struct.h"

/**
 * \fn double density(struct object item)
 * \brief Вычисление плотности предмета
 * \param [in] item Структура
 * \return Значение плотности
 */
double density(struct object item);

/**
 * \fn int sort(struct object *items, int n)
 * \brief Сортировка массива структур по плотности
 * \param [in] items Массив структур
 * \param [out] items Отсортированный массив структур
 * \return Код ошибки
 */
int sort(struct object *items, int n, int (*comparator)(struct object *, struct object *));

int comparator(struct object *item1, struct object *item2);

#endif