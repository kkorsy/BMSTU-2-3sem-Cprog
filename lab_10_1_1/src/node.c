#include "node.h"
#include <stdlib.h>
#include <string.h>

#define EPS 1e-7

node_t *node_create(FILE *f)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        data_t *elem = malloc(sizeof(data_t));
        if (!elem)
        {
            free(node);
            return NULL;
        }
        if (!data_read(f, elem))
        {
            node->data = elem;
            node->next = NULL;
        }
        else
        {
            free(elem);
            free(node);
            node = NULL;
        }
    }

    return node;
}

int data_read(FILE *f, data_t *elem)
{
    int count;
    double price;
    if (fscanf(f, "%d\n", &count) != 1 || fscanf(f, "%lf\n", &price) != 1 || count <= 0 || price <= EPS)
        return DATA_ERROR;
    
    data_init(elem, count, price);
    
    return OK;
}

void data_init(data_t *elem, int count, double price)
{   
    elem->count = count;
    elem->price = price;
}

void node_free(void *node)
{
    free(node);
}

void node_data_free(void *node)
{
    node_t *n = node;
    free(n->data);
    free(n);
}

void data_print(FILE *f, const data_t *data)
{
    fprintf(f, "%d\n", data->count);
    fprintf(f, "%lf\n", data->price);
}
