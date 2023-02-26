#include "node.h"
#include <stdlib.h>

node_t *node_create(int k, int p)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->k = k;
        node->p = p;
        node->next = NULL;
    }

    return node;
}

void node_free(node_t *node)
{
    free(node);
}

void node_print(const node_t *node)
{
    printf("%d %d ", node->k, node->p);
}
