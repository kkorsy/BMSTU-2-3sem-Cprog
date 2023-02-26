#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "array_io.h"
#include "filter.h"
#include "sort.h"

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
                cr = key(pb_src, pe_src, &pb_dst, &pe_dst);
                arr = pb_dst;
                n = pe_dst - pb_dst;
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
