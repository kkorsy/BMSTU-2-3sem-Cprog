#ifndef __LIST_H__
#define __LIST_H__

#include "node.h"

int list_read(FILE *f, node_t **head);
node_t *list_add_tail(node_t *head, node_t *node);
void list_free(node_t *head);
void list_print(const node_t *head);
void list_sep(node_t *head_src, node_t **head_even, node_t **head_not_even);

#endif