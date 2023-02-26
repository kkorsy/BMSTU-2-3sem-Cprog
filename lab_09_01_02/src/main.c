#include "errors.h"
#include "item_arr.h"
#include "operations.h"

int main(int argc, char **argv)
{
    int cr = OK;
    size_t n;
    struct object *items;

    if (argc != 3 && argc != 2)
        return ARGS_ERROR;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return OPEN_ERROR;

    if (!(cr = item_arr_create(f, &items, &n)))
    {
        if (argc == 3 && !strcmp(argv[2], "ALL"))
            print_all(items, n);
        else if (argc == 3)
            cr = find(items, n, argv[2]);
        else
        {
            sort(items, n);
            print_all(items, n);
        }

        item_arr_free(items, n);
    }
    fclose(f);

    return cr;
}
