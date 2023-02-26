#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include "errors.h"

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};

typedef struct data data_t;
struct data
{
    int count;
    double price;
};

/**
 * \brief Создает узел списка чтением из файла
 * \param [in] f Файловая переменная, откуда читать данные
 * \return Указатель на созданный узел
 */
node_t *node_create(FILE *f);

/**
 * \brief Считывает данные из файла
 * \param [in] f Файловая переменная, откуда читать данные
 * \param [out] elem Указатель на данные
 * \return Код ошибки
 */
int data_read(FILE *f, data_t *elem);

/**
 * \brief Инициализирует данные значениями
 * \param [out] elem Указатель на данные
 * \param [in] count Число для поля count
 * \param [in] price Число для поля price
 */
void data_init(data_t *elem, int count, double price);

/**
 * \brief Освобождает память только из-под узла
 * \param [in] node Указатель на узел
 */
void node_free(void *node);

/**
 * \brief Освобождает паямть из-под данных и из-под узла
 * \param [in] node Указатель на узел
 */
void node_data_free(void *node);

/**
 * \brief Записывает данные в файл
 * \param [in] f Файловая переменная, куда записать данные
 * \param [in] data Указатель на данные
 */
void data_print(FILE *f, const data_t *data);

#endif