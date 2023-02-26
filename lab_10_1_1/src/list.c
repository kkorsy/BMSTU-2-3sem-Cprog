#include "list.h"
#include <stdlib.h>

int list_create(FILE *f, node_t **head)
{
    int rc = OK;
    node_t *node = NULL, *head_tmp = NULL;
    while (rc == OK)
    {
        node = node_create(f);
        if (node == NULL)
            rc = READ_ERROR;
        else
            head_tmp = list_add_end(head_tmp, node);
    }
    if (rc == OK || feof(f))
    {
        *head = head_tmp;
        rc = OK;
    }
    else
        list_free(head_tmp, node_data_free);

    return rc;
}

node_t *list_copy(node_t *src)
{
    node_t *node = NULL, *dst = NULL;
    while (src != NULL)
    {
        node = malloc(sizeof(node_t));
        if (node == NULL)
        {
            list_free(dst, node_free);
            return NULL;
        }
        node->data = src->data;
        node->next = NULL;
        dst = list_add_end(dst, node);
        
        src = src->next;
    }
    return dst;
}

node_t *list_add_end(node_t *head, node_t *node)
{
    node_t *cur = head;
    if (!head)
        return node;
    
    for (; cur->next; cur = cur->next);
    cur->next = node;

    return head;
}

void list_free(node_t *head, void (*free_type)(void *))
{
    node_t *next;
    for (; head; head = next)
    {
        next = head->next;
        (*free_type)(head);
    }
}

void list_print(FILE *f, const node_t *head)
{
    for (; head; head = head->next)
        data_print(f, head->data);
}
