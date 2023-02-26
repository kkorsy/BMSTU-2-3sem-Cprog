#include "node.h"
#include <stdlib.h>

node_t *node_create(int x)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;

    node->x = x;
    node->next = NULL;

    return node;
}

void node_free(node_t *node)
{
    free(node);
}

void node_print(const node_t *node)
{
    printf("%d ", node->x);
}