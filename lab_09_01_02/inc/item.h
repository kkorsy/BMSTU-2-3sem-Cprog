#ifndef __ITEM_H__
#define __ITEM_H__

#include <stdio.h>
#include "stdlib.h"
#include "errors.h"

struct object
{
    char *name;
    double mass;
    double volume;
};

/**
 * Считывает одну структуру из файла
 * \param [in] f Файловая переменная: откуда считывать данные
 * \param [out] item Указатель на структуру, куда будет записан результат
 * \return Код ошибки
 */
int item_read(FILE *f, struct object *item);

/**
 * Инициализирует структуру значениями
 * \param [in] name Строка, которая будет записана в структуру
 * \param [in] mass Значение массы, которое будет записано в структуру
 * \param [in] volume Значение объема, которое будет записано в структуру
 * \param [out] item Указатель на структуру для инициализации
 * \return Код ошибки
 */
int item_init(struct object *item, char *name, double mass, double volume);

/**
 * Освобождает память из-под динамической строки, находящейся в структуре
 * \param [in] item Указатель на структуру
 */
void item_free(struct object *item);

/**
 * Выводит на экран одну структуру
 * \param [in] item Структура, которая будет выведена
 */
void item_print(struct object *item);

#endif