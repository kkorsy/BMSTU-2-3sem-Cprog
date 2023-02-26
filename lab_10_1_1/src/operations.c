#include "operations.h"
#include <stdlib.h>
#include <string.h>
#include "math.h"

#define EPS 1e-07

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;
    
    data_t *elem = (*head)->data;
    *head = del_elem(*head, *head);

    return elem;
}

node_t *del_elem(node_t *head, node_t *elem)
{
    int rc = OK;
    node_t *prev;

    rc = find_prev(head, &prev, elem);
    if (!rc)
    {
        if (prev == NULL)
            head = head->next;
        else
            prev->next = elem->next;
        
        node_free(elem);
    }

    return head;
}

int find_prev(node_t *head, node_t **prev, node_t *elem)
{
    if (head == NULL)
        return EMPTY_LIST_ERROR;
    int find = 1;
    node_t *cur = head;
    *prev = NULL;

    if (cur == elem)
        return OK;

    while (cur->next != elem && cur->next != NULL)
        cur = cur->next;
    
    if (cur->next == NULL)
        find = 0;
    if (!find)
        return NOT_FOUND_ERROR;
    
    *prev = cur;
    
    return OK;
}

node_t *find_elem(node_t *head, double price)
{
    for (node_t *cur = head; cur; cur = cur->next)
    {
        data_t *data_cur = cur->data;
        if (fabs(data_cur->price - price) < EPS)
            return cur;
    }

    return NULL;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    int rc = OK;
    node_t *prev;

    rc = find_prev(*head, &prev, before);
    if (!rc)
    {
        elem->next = before;
        if (prev == NULL)
            *head = elem;
        else
            prev->next = elem;
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *sorted = NULL, *cur = head;

    while (cur != NULL)
    {
        node_t *next = cur->next;
        sorted_insert(&sorted, cur, comparator);
        cur = next;
    }

    return sorted;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (*head == NULL || comparator((*head)->data, element->data) > 0)
    {
        element->next = *head;
        *head = element;
    }
    else
    {
        node_t *cur = *head;
        while (cur->next != NULL && comparator(cur->next->data, element->data) < 0)
            cur = cur->next;
        
        element->next = cur->next;
        cur->next = element;
    }
}

int comparator(const void *l, const void *r)
{
    const data_t *data_l = l, *data_r = r;
    
    double temp = data_l->price - data_r->price;
    if (temp > EPS)
        return 1;
    if (temp < -EPS)
        return -1;
    return 0;
}

node_t *del_elem_extra(node_t *head, node_t *prev, node_t *elem)
{
    if (prev == NULL)
        head = head->next;
    else
        prev->next = elem->next;
    
    node_free(elem);

    return head;
}

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *))
{
    if (*head == NULL)
        return;
    
    node_t *cur = *head;

    while (cur->next != NULL)
    {
        if (comparator(cur->data, cur->next->data) == 0)
        {
            *head = del_elem_extra(*head, cur, cur->next);
            continue;
        }
        cur = cur->next;
    }
}
