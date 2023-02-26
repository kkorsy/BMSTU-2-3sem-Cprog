#include "find.h"

int find(struct object *items, int n, char *substr)
{
    int cr = OK;
    int printed = 0;

    for (int i = 0; i < n; i++)
        if (strstr(items[i].name, substr) == items[i].name)
        {
            print_struct(items[i]);
            printed = 1;
        }

    if (!printed)
        cr = FIND_ERROR;

    return cr;
}
