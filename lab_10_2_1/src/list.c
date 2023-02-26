#include "list.h"
#include <string.h>
#include <stdlib.h>

node_t *list_create()
{
    char *buf = NULL;
    size_t buf_len = 0;
    ssize_t read;
    node_t *node, *head = NULL;
    int k, p;
    int flag = 0;

    if ((read = getline(&buf, &buf_len, stdin)) == -1 || !read)
    {
        free(buf);
        return NULL;
    }

    char *pend, *tmp = NULL;
    k = strtol(buf, &pend, 10);
    p = strtol(pend, &pend, 10);
    while (!flag && pend != NULL)
    {   
        if (*pend == '\n')
            pend = NULL;

        node = node_create(k, p);
        if (!node)
        {
            list_free(head);
            return NULL;
        }
        head = list_add_tail(head, node);
        if (pend != NULL)
        {
            k = strtol(pend, &pend, 10);
            if (*pend == '\n')
                flag = 1;
            else
            {
                tmp = pend;
                p = strtol(pend, &pend, 10);
            }
            if (tmp == pend)
                flag = 1;
        }
    }
    free(buf);

    if (flag)
    {
        list_free(head);
        return NULL;
    }

    return head;
}

node_t *list_add_tail(node_t *head, node_t *node)
{
    if (!head)
        return node;

    node_t *cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = node;

    return head;
}

node_t *list_copy(node_t *src, node_t *dst)
{
    node_t *tmp;
    while (src != NULL)
    {
        tmp = node_create(src->k, src->p);
        if (!tmp)
        {
            list_free(dst);
            return NULL;
        }
        dst = list_add_tail(dst, tmp);
        src = src->next;
    }

    return dst;
}

node_t *list_del_elem(node_t *head, node_t *elem)
{
    node_t *prev = list_find_prev(head, elem);

    if (prev == NULL)
        head = head->next;
    else
        prev->next = elem->next;

    node_free(elem);

    return head;
}

node_t *list_find_prev(node_t *head, node_t *elem)
{
    node_t *cur = head;

    if (cur == elem)
        return NULL;

    while (cur->next != elem && cur->next != NULL)
        cur = cur->next;

    return cur;
}

void list_free(node_t *head)
{
    node_t *tmp;
    while (head != NULL)
    {
        tmp = head->next;
        node_free(head);
        head = tmp;
    }
}

void list_print(const node_t *head)
{
    while (head != NULL)
    {
        node_print(head);
        head = head->next;
    }
    printf("L\n");
}
