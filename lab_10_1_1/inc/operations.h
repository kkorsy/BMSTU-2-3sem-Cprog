#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include "node.h"

/**
 * \brief Достает данные из головы списка и удаляет этот элемент
 * \param [in] head Указатель на указатель на голову списка
 * \return Указатель на данные
 */
void *pop_front(node_t **head);

/**
 * \brief Удаляет элемент из списка
 * \param [in] head Указатель на голову списка
 * \param [in] elem Указатель на элемент, который нужно удалить
 * \return Указатель на голову списка
 */
node_t *del_elem(node_t *head, node_t *elem);

/**
 * \brief Ищет элемент в списке по полю данных price
 * \param [in] head Указатель на голову списка
 * \param [in] price Значение поля price
 * \return Указатель на найденный элемент
 */
node_t *find_elem(node_t *head, double price);

/**
 * \brief Ищет предыдущий элемент у указанного
 * \param [in] head Указатель на голову списка
 * \param [out] prev Предыдущий элемент
 * \param [in] elem Элемент, у которого нужно найти предыдущий
 * \return Код ошибки
 */
int find_prev(node_t *head, node_t **prev, node_t *elem);

/**
 * \brief Вставляет элемент перед указанным
 * \param [in] head Указатель на голову списка
 * \param [in] elem Элемент, который нужно вставить
 * \param [in] before Элемент, перед которым нужно вставить
 */
void insert(node_t **head, node_t *elem, node_t *before);

/**
 * \brief Сортирует список
 * \param [in] head Указатель на голову списка
 * \param [in] comparator Указатель на функцию сравнения
 * \return Указатель на новую голову списка
 */
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

/**
 * \brief Вставляет элемент в упорядоченный список, не нарушая его упорядоченности
 * \param [in] head Указатель на отсортированный список
 * \param [in] element Элемент, который нужно вставить
 * \param [in] comparator Указатель на функцию сравнения
 */
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

/**
 * \brief Сравнивает данные
 * \param [in] l Указатель на данные (1)
 * \param [in] r Указатель на данные (2)
 * \return Результат сравнения
 */
int comparator(const void *l, const void *r);

/**
 * \brief Убирает из списка повторения каждого элемента
 * \param [in] head Указатель на упорядоченный список
 * \param [in] comparator Указатель на функцию сравнения
 */
void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *));

node_t *del_elem_extra(node_t *head, node_t *prev, node_t *elem);

#endif