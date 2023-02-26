#include "item.h"
#include <string.h>

int item_read(FILE *f, struct object *item)
{
    char *buf = NULL;
    size_t buf_len = 0;
    ssize_t read;
    double mass, volume;
    int cr = OK;

    if ((read = getline(&buf, &buf_len, f)) == -1)
    {
        free(buf);
        return READ_ERROR;
    }

    if (!read)
        cr = DATA_ERROR;
    else
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';

        if (fscanf(f, "%lf%lf\n", &mass, &volume) == 2)
        {
            if (mass > 0 && volume > 0)
                cr = item_init(item, buf, mass, volume);
            else
                cr = DATA_ERROR;
        }
        else
            cr = READ_ERROR;
    }
    free(buf);
    
    return cr;
}

int item_init(struct object *item, char *name, double mass, double volume)
{
    char *tmp = strdup(name);
    if (tmp == NULL)
        return ALLOC_ERROR;
    
    item->name = tmp;
    item->mass = mass;
    item->volume = volume;

    return OK;
}

void item_free(struct object *item)
{
    if (item != NULL)
        free(item->name);
}

void item_print(struct object *item)
{
    printf("%s\n", item->name);
    printf("%lf\n", item->mass);
    printf("%lf\n", item->volume);
}
