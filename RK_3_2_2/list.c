#include "list.h"
#include "errs.h"

int list_read(FILE *f, node_t **head)
{
    node_t *head_tmp = NULL;
    int x;

    while (fscanf(f, "%d", &x) == 1)
    {
        node_t *node = node_create(x);
        if (node == NULL)
        {
            list_free(head_tmp);
            return ALLOC_ERROR;
        }
        head_tmp = list_add_tail(head_tmp, node);
    }
    
    *head = head_tmp;

    return OK;
}

node_t *list_add_tail(node_t *head, node_t *node)
{
    if (head == NULL)
        return node;
    
    node_t *cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    
    cur->next = node;

    return head;
}

void list_free(node_t *head)
{
    node_t *next;
    while (head != NULL)
    {
        next = head->next;
        node_free(head);
        head = next;
    }
}

void list_print(const node_t *head)
{
    if (head == NULL)
        printf("Empty list");
    
    while (head != NULL)
    {
        node_print(head);
        head = head->next;
    }
    printf("\n");
}

void list_sep(node_t *head_src, node_t **head_even, node_t **head_not_even)
{
    node_t *head_even_tmp = NULL;
    node_t *head_not_even_tmp = NULL;

    node_t *cur = head_src, *next;
    int i = 1;
    while (cur != NULL)
    {
        next = cur->next;

        cur->next = NULL;
        if (i % 2 == 0)
            head_even_tmp = list_add_tail(head_even_tmp, cur);
        else
            head_not_even_tmp = list_add_tail(head_not_even_tmp, cur);
        
        cur = next;
        i++;
    }

    *head_even = head_even_tmp;
    *head_not_even = head_not_even_tmp;
}

