#ifndef __LIST_H__
#define __LIST_H__

#include "node.h"

/**
 * \brief Создает список, используя стандартный поток ввода
 * \return Указатель на голову, созданного списка
 */
node_t *list_create();

/**
 * \brief Добавляет узел в конец списка
 * \param [in] head Указатель на голову списка
 * \param [in] node Указатель на добавляемый узел
 * \return Указатель на голову списка
 */
node_t *list_add_tail(node_t *head, node_t *node);

/**
 * \brief Копирует список src в конец списка dst
 * \param [in] src Список, который нужно добавить
 * \param [out] dst Список, в который нужно добавить
 * \return Список, в который добавили src
 */
node_t *list_copy(node_t *src, node_t *dst);

/**
 * \brief Удаляет элемент из списка
 * \param [in] head Указатель на голову списка
 * \param [in] elem Элемент, который нужно удалить
 * \return Указатель на голову списка
 */
node_t *list_del_elem(node_t *head, node_t *elem);

/**
 * \brief Ищет предыдущий элемент в списке
 * \param [in] head Указатель на голову списка
 * \param [in] elem Элемент, у которого нужно найти предыдущий
 * \return Указатель на предыдущий элемент
 */
node_t *list_find_prev(node_t *head, node_t *elem);

/**
 * \brief Освобождает память из-под списка
 * \param [in] head Указатель на голову списка
 */
void list_free(node_t *head);

/**
 * \brief Выводит список на экран
 * \param [in] head Указатель на голову списка
 */
void list_print(const node_t *head);

#endif