#include "item_arr.h"
#include "operations.h"

int find(struct object *items, size_t n, char *substr)
{
    int cr = OK;
    int printed = 0;

    for (size_t i = 0; i < n; i++)
        if (strstr(items[i].name, substr) == items[i].name)
        {
            item_print(items + i);
            printed = 1;
        }

    if (!printed)
        cr = FIND_ERROR;

    return cr;
}

double density(struct object item)
{
    return item.mass / item.volume;
}

/*
void sort(struct object *items, size_t n)
{
    struct object temp;

    for (size_t i = 1; i < n; i++)
    {
        temp = items[i];
        for (size_t j = i - 1; j < n; j--)
            if (density(items[j]) > density(temp))
            {
                items[j + 1] = items[j];
                items[j] = temp;
            }
    }
}
*/

void sort(struct object *items, size_t n)
{
    struct object max, temp;
    size_t ind_max;

    for (size_t i = n - 1; i < n; i--)
    {
        max = items[0];
        ind_max = 0;
        for (size_t j = 0; j <= i; j++)
        {
            if (density(items[j]) >= density(max))
            {
                max = items[j];
                ind_max = j;
            }
        }
        temp = items[i];
        items[i] = max;
        items[ind_max] = temp;
    }
}
