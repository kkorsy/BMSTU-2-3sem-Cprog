#include <string.h>
#include "matrix_io.h"
#include "matrix_alloc.h"
#include "matrix_op.h"

int main(int argc, char **argv)
{
    int cr = OK;
    double **a, **b, **c, **res_coll;
    size_t a_n, a_m, b_n, b_m, c_n, c_m;

    if (argc != 5 && argc != 4)
        return ARGS_ERR;

    if (argc == 4) 
    {
        if (!strcmp(argv[1], "o"))
        {
            if ((cr = matrix_create(argv[2], &a, &a_n, &a_m)) == OK)
            {
                cr = gauss_solving(a, a_n, a_m, &res_coll);
                if (cr == OK)
                {
                    cr = matrix_print(argv[3], res_coll, a_n, 1);
                    matrix_free(res_coll, a_n);
                }
                matrix_free(a, a_n);
            }
        }
        else
            cr = ARGS_ERR;
    }  
    else if (argc == 5)
    {
        if ((cr = matrix_create(argv[2], &a, &a_n, &a_m)) == OK)
        {
            if ((cr = matrix_create(argv[3], &b, &b_n, &b_m)) == OK)
            {
                if (!strcmp(argv[1], "a"))
                    cr = matrix_sum(a, a_n, a_m, b, b_n, b_m, &c, &c_n, &c_m);
                else if (!strcmp(argv[1], "m"))
                    cr = matrix_mult(a, a_n, a_m, b, b_n, b_m, &c, &c_n, &c_m);
                else
                    cr = ARGS_ERR;
                
                if (cr == OK)
                {
                    cr = matrix_print(argv[4], c, c_n, c_m);
                    matrix_free(c, c_n);
                }

                matrix_free(b, b_n);
            }
            matrix_free(a, a_n);
        }
    }

    return cr;
}
