#include "errors.h"
#include "read.h"
#include "print.h"
#include "find.h"
#include "sort.h"

int main(int argc, char **argv)
{
    int n, cr = OK;
    struct object items[N];

    if (argc == 3 || argc == 2)
    {
        FILE *f = fopen(argv[1], "r");
        if (f == NULL)
            cr = OPEN_ERROR;
        else if (!(cr = read_file(f, items, &n)))
        {
            fclose(f);
            if (argc == 3 && !strcmp(argv[2], "ALL"))
                print_all(items, n);
            else if (argc == 3)
                cr = find(items, n, argv[2]);
            else
            {
                cr = sort(items, n, comparator);
                print_all(items, n);
            }
        }
    }
    else
        cr = ARGS_ERROR;

    return cr;
}
