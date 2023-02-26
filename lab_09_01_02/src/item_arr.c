#include "item_arr.h"
#include <string.h>

int item_arr_create(FILE *f, struct object **items, size_t *n)
{
    int cr = OK;
    struct object *tmp;

    cr = items_count(f, n);
    rewind(f);

    if (cr == OK)
    {
        if (*n == 0)
            cr = DATA_ERROR;
        else
        {
            tmp = malloc(*n * sizeof(struct object));
            if (tmp == NULL)
                return ALLOC_ERROR;

            item_arr_read(f, tmp, *n);
            *items = tmp;
        }
    }

    return cr;
}

void item_arr_read(FILE *f, struct object *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        item_read(f, arr + i);
}

void item_arr_free(struct object *items, size_t n)
{
    for (size_t i = 0; i < n; i++)
        item_free(&items[i]);
    free(items);
}

void print_all(struct object *items, int n)
{
    for (int i = 0; i < n; i++)
        item_print(items + i);
}

int items_count(FILE *f, size_t *n)
{
    struct object temp = { NULL, 0, 0 };
    size_t i = 0;
    int cr = OK;

    while (cr == OK)
    {
        cr = item_read(f, &temp);
        if (cr == OK)
        {
            i++;
            item_free(&temp);
        }
    }

    if (cr != OK && feof(f))
        cr = OK;

    *n = i;

    return cr;
}
