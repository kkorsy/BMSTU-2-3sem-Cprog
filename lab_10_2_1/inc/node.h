#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

typedef struct node node_t;
struct node
{
    int k;
    int p;
    node_t *next;
};

/**
 * \brief Создает узел списка
 * \param [in] k Число для поля k узла
 * \param [in] p Число для поля p узла
 * \return Указатель на созданную переменную
 */
node_t *node_create(int k, int p);

/**
 * \brief Освобождает память из-под узла списка
 * \param [in] node Указатель на узел
 */
void node_free(node_t *node);

/**
 * \brief Выводит содержимое узла на экран
 * \param [in] node Указатель на узел
 */
void node_print(const node_t *node);

#endif