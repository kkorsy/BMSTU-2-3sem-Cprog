#ifndef __ITEM_ARR_H__
#define __ITEM_ARR_H__

#include "errors.h"
#include "item.h"

/**
 * Создает массив структур: выделяет память, инициализирует
 * \param [in] f Файловая переменная: откуда считывать данные
 * \param [out] items Массив структур
 * \param [out] n Количество элементов
 * \return Код ошибки
 */
int item_arr_create(FILE *f, struct object **items, size_t *n);

/**
 * Освобождает память из-под массива структур
 * \param [in] items Массив структур
 * \param [in] n Количество элементов
 */
void item_arr_free(struct object *items, size_t n);

/**
 * Считывает массив структур из файла
 * \param [in] f Файловая переменная: откуда считывать данные
 * \param [in] n Количество элементов
 * \param [out] arr Массив структур
 */
void item_arr_read(FILE *f, struct object *arr, size_t n);

/**
 * Выводит на экран все структуры из массива
 * \param [in] items Массив структур
 * \param [in] n Количество элементов
 */
void print_all(struct object *items, int n);

/**
 * Считает количество структур в файле
 * \param [in] f Файловая переменная: откуда считывать данные
 * \param [out] n Количество элементов
 * \return Код ошибки
 */
int items_count(FILE *f, size_t *n);

#endif