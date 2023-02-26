#include "errs.h"
#include "list.h"

int main(int argc, char **argv)
{
    int rc = OK;
    if (argc != 2)
        return ARGS_ERROR;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return OPEN_ERROR;
    
    node_t *head;
    rc = list_read(f, &head);
    if (!rc)
    {
        node_t *head_even, *head_not_even;
        list_sep(head, &head_even, &head_not_even);

        list_print(head_not_even);
        list_print(head_even);

        list_free(head_even);
        list_free(head_not_even);
    }

    fclose(f);

    return rc;
}