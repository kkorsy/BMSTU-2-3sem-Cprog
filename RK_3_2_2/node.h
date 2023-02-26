#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>

typedef struct node
{
    int x;
    struct node *next;
} node_t;

node_t *node_create(int x);
void node_free(node_t *node);
void node_print(const node_t *node);

#endif