#ifndef __LIST_H__
#define __LIST_H__

#include "node.h"
#include "errors.h"

/**
 * \brief Освобождает память из-под списка
 * \param [in] head Указатель на голову списка
 * \param [in] free_type Указатель на функцию освобождения памяти из-под узла
 */
void list_free(node_t *head, void (*free_type)(void *));

/**
 * \brief Записывает список в файл
 * \param [in] f Файловая переменная, куда записать список
 * \param [in] head Указатель на голову списка
 */
void list_print(FILE *f, const node_t *head);

/**
 * \brief Создает список чтением из файла
 * \param [in] f Файловая переменная, откуда читать данные
 * \param [in] head Указатель на указатель на голову списка
 * \return Код ошибки
 */
int list_create(FILE *f, node_t **head);

/**
 * \brief Создает копию списка
 * \param [in] src Список, копию которого нужно создать
 * \return Указатель на голову созданного списка
 */
node_t *list_copy(node_t *src);

/**
 * \brief Добавляет элемент в конец списка
 * \param [in] head Указатель на голову списка
 * \param [in] node Указатель на элемент, который нужно добавить
 * \return Указатель на голову списка
 */
node_t *list_add_end(node_t *head, node_t *node);

#endif