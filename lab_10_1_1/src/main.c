#include "list.h"
#include "operations.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rc = OK;
    if (argc < 4)
        return ARGS_ERROR;

    FILE *f_in = fopen(argv[1], "r");
    if (f_in == NULL)
        return OPEN_ERROR;

    node_t *head, *data_head;
    rc = list_create(f_in, &head);
    if (!rc)
    {
        data_head = list_copy(head);
        FILE *f_out = fopen(argv[3], "w");
        if (data_head == NULL)
            rc = ALLOC_ERROR;
        else if (f_out == NULL)
            rc = OPEN_ERROR;
        else 
        {
            if (!strcmp(argv[2], "pop"))
            {
                data_t *d = pop_front(&head);
                data_print(f_out, d);
            }
            else if (!strcmp(argv[2], "insert"))
            {
                FILE *f_ins = fopen(argv[4], "r");
                if (!f_ins)
                    rc = OPEN_ERROR;
                else
                {
                    node_t *ins_elem = node_create(f_ins);
                    node_t *ins_before = node_create(f_ins);
                    if (ins_elem == NULL)
                        rc = READ_ERROR;
                    else if (ins_before == NULL)
                    {
                        node_data_free(ins_elem);
                        rc = READ_ERROR;
                    }
                    else
                    {
                        data_t *tmp = ins_before->data; 
                        node_t *before = find_elem(head, tmp->price);
                        if (before == NULL)
                            rc = NOT_FOUND_ERROR;
                        else
                        {
                            insert(&head, ins_elem, before);
                            list_print(f_out, head);
                        }
                        node_data_free(ins_before);
                        free(ins_elem->data);
                    }
                    fclose(f_ins);
                }
            }
            else if (!strcmp(argv[2], "remove"))
            {
                head = sort(head, comparator);
                remove_duplicates(&head, comparator);
                list_print(f_out, head);
            }
            else if (!strcmp(argv[2], "sort"))
            {
                head = sort(head, comparator);
                list_print(f_out, head);
            }
            else
                rc = ARGS_ERROR;
            fclose(f_out);
        }
        list_free(data_head, node_data_free);
        list_free(head, node_free);
    }
    fclose(f_in);

    return rc;
}
