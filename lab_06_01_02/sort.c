#include "sort.h"

int comparator(struct object *item1, struct object *item2)
{
    if (density(*item1) > density(*item2))
        return 1;
    else
        return 0;
}

double density(struct object item)
{
    return item.mass / item.volume;
}

// density(items[j]) > density(temp)

int sort(struct object *items, int n, int (*comparator)(struct object *, struct object *))
{
    int cr = OK;
    struct object temp;

    for (int i = 1; i < n; i++)
    {
        temp = items[i];
        for (int j = i - 1; j >= 0; j--)
            if ((*comparator)(&items[j], &temp))
            {
                items[j + 1] = items[j];
                items[j] = temp;
            }
    }

    return cr;
}
