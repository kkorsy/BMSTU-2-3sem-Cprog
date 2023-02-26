#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_arr.h"

int main(int argc, char **argv)
{
    int *arr, cr = OK;
    size_t n;
    int *pb_src = NULL, *pe_src;
    int *pb_dst = NULL, *pe_dst;

    if (argc != 4 && argc != 3)
    {
        fprintf(stderr, "app.exe in_file out_file [f]\n");
        return ARGS_ERROR;
    }

    cr = array_read(argv[1], &pb_src, &n);
    if (!cr)
    {
        arr = pb_src;
        pe_src = pb_src + n;
        if (argc == 4)
        {
            if (strcmp(argv[3], "f"))
                cr = ARGS_ERROR;
            else
            {
                if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src)
                    cr = PARAM_ERROR;

                if (!cr)
                {
                    double avg = average(pb_src, pe_src);
                    int n_dst = num_count(pb_src, pe_src, avg);
                    if (n_dst == 0)
                        cr = DATA_ERROR;
                    
                    if (!cr)
                    {
                        pb_dst = malloc(n * sizeof(int));
                        if (pb_dst == NULL)
                            cr = ALLOC_ERROR;

                        if (!cr)
                        {
                            pe_dst = pb_dst + n_dst;

                            key(pb_src, pe_src, pb_dst, avg);
                            arr = pb_dst;
                            n = pe_dst - pb_dst;
                        }
                    }
                }
            }
        }

        if (!cr)
        {
            mysort(arr, n, sizeof(int), cmp);
            cr = array_write(argv[2], arr, arr + n);
        }
        free(pb_dst);
        free(pb_src);
    }
    
    return cr;
}
