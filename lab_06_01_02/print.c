#include "print.h"

void print_all(struct object *items, int n)
{
    for (int i = 0; i < n; i++)
        print_struct(items[i]);
}

void print_struct(struct object item)
{
    printf("%s\n", item.name);
    printf("%lf\n", item.mass);
    printf("%lf\n", item.volume);
}
