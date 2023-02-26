#ifndef __FIND_H__
#define __FIND_H__

#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "print.h"
#include "struct.h"

/**
 * \fn int find(struct object *items, int n, char *substr)
 * \brief Поиск структур, название которых начинается с заданной подстроки
 * \param [in] items Массив структур
 * \param [in] substr Подстрока
 * \return Код ошибки
 */
int find(struct object *items, int n, char *substr);

#endif