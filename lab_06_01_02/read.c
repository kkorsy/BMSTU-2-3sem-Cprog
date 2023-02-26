#include "read.h"

int read_file(FILE *f, struct object *items, int *n)
{
    int cr = OK;
    int i = 0;

    while (!cr && !feof(f))
    {
        if (i < N)
        {
            cr = read_item(f, items + i);
            i++;
        }
        else
            cr = ARR_OVERFLOW;
    }

    if (!cr && i > 0)
        *n = i;

    return cr;
}

int read_item(FILE *f, struct object *item)
{
    char s[LEN_MAX + 2];
    size_t len;
    double mass, volume;

    if (!fgets(s, sizeof(s), f))
        return READ_ERROR;

    len = strlen(s);
    if (len && s[len - 1] == '\n')
    {
        s[len - 1] = '\0';
        len--;
    }

    if (!len || len > LEN_MAX)
        return STR_OVERFLOW;

    if (fscanf(f, "%lf\n%lf\n", &mass, &volume) != 2)
        return READ_ERROR;

    if (mass <= 0 || volume <= 0)
        return DATA_ERROR;

    strcpy(item->name, s);
    item->mass = mass;
    item->volume = volume;

    return OK;
}
