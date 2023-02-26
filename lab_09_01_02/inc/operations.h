#ifndef __ITEM_OP_H__
#define __ITEM_OP_H__

#include <string.h>
#include "errors.h"

/**
 * Считает плотность объекта по значениям из структуры
 * \param [in] item Структура, из которой берутся данные
 * \return Значение плотности
 */
double density(struct object item);

/**
 * Сортирует массив структур по плотности
 * \param [in] items Массив структур
 * \param [in] n Количество элементов
 * \param [out] items Отсортированный массив структур 
 */
void sort(struct object *items, size_t n);

/**
 * Ищет и выводит на экран структуры, которые начинаются с заданной подстроки
 * \param [in] items Массив структур
 * \param [in] n Количество элементов
 * \param [in] substr Заданная подстрока
 * \return Код ошибки
 */
int find(struct object *items, size_t n, char *substr);

#endif