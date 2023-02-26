#include "operations.h"
#include <stdlib.h>
#include <math.h>

int calc(node_t *head, int a)
{
    int res = 0;

    while (head != NULL)
    {
        res += head->k * pow(a, head->p);
        head = head->next;
    }
    
    return res;
}

node_t *derive(node_t *head)
{
    node_t *cur = head;
    while (cur != NULL)
    {
        cur->k = cur->k * cur->p;
        (cur->p)--;
        
        if (cur->p < 0)
        {
            node_t *tmp = cur->next;
            head = list_del_elem(head, cur);
            cur = tmp;
        }
        else if (cur != NULL)
            cur = cur->next;
    }

    return head;
}

node_t *summation(node_t *head_1, node_t *head_2)
{
    node_t *cur_1 = head_1, *cur_2 = head_2;
    node_t *res = NULL;
    
    while (cur_1 != NULL && cur_2 != NULL)
    {
        node_t *tmp;
        if (cur_1->p > cur_2->p)
        {
            tmp = node_create(cur_1->k, cur_1->p);
            if (!tmp)
            {
                list_free(res);
                return NULL;
            }
            res = list_add_tail(res, tmp);
            cur_1 = cur_1->next;
        }
        else if (cur_1->p < cur_2->p)
        {
            tmp = node_create(cur_2->k, cur_2->p);
            if (!tmp)
            {
                list_free(res);
                return NULL;
            }
            res = list_add_tail(res, tmp);
            cur_2 = cur_2->next;
        }
        else
        {
            tmp = node_create(cur_1->k + cur_2->k, cur_1->p);
            if (!tmp)
            {
                list_free(res);
                return NULL;
            }
            res = list_add_tail(res, tmp);
            cur_1 = cur_1->next;
            cur_2 = cur_2->next;
        }
    }

    res = list_copy(cur_1, res);
    res = list_copy(cur_2, res);

    return res;
}

void separation(node_t *head_src, node_t **head_even, node_t **head_odd)
{
    node_t *head_even_tmp = NULL;
    node_t *head_odd_tmp = NULL;

    node_t *cur = head_src, *next;

    while (cur != NULL)
    {
        next = cur->next;

        cur->next = NULL;
        if (abs(cur->p) % 2 == 0)
            head_even_tmp = list_add_tail(head_even_tmp, cur);
        else
            head_odd_tmp = list_add_tail(head_odd_tmp, cur);
        
        cur = next;
    }

    *head_even = head_even_tmp;
    *head_odd = head_odd_tmp;
}

