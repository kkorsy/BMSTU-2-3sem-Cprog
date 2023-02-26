#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>
#include "struct.h"

/**
 * \fn void print_all(struct object *items, int n)
 * \brief Вывод массива структур на экран
 * \param [in] items Массив структур
 */
void print_all(struct object *items, int n);

/**
 * \fn void print_struct(struct object item)
 * \brief Вывод одной структуры
 * \param [in] item Выводимая структура
 */
void print_struct(struct object item);

#endif