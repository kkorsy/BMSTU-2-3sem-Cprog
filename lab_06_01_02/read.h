#ifndef __READ_H__
#define __READ_H__

#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "struct.h"

#define N 15

/**
 * \fn int read_file(FILE *f, struct object *items, int *n)
 * \brief Считывание данных из файла в массив структур
 * \param [in] f Файл
 * \param [out] items Считанный массив структур
 * \return Код ошибки
 */
int read_file(FILE *f, struct object *items, int *n);

/**
 * \fn int read_item(FILE *f, struct object *item)
 * \brief Считывание одной структуры
 * \param [in] f Файл
 * \param [out] items Считанная структура
 * \return Код ошибки
 */
int read_item(FILE *f, struct object *item);

#endif