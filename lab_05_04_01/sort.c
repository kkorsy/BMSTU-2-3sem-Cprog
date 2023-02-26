#include "sort.h"
#include "read_bin_file.h"

int sort_bin(char *file_name, int *n)
{
    int cr = OK;
    struct student temp, x;
    FILE *f = fopen(file_name, "rb+");

    cr = check_bin(f, n);
    if (cr && cr != OPEN_ERROR)
        fclose(f);
    else if (!cr)
    {
        for (int i = 1; !cr && i < *n; i++)
        {
            cr = get_pers_by_pos(f, i, &temp);
            for (int j = i - 1; !cr && j >= 0; j--)
            {   
                cr = get_pers_by_pos(f, j, &x);
                if (strcmp(x.surname, temp.surname) < 0)
                    break;

                if ((strcmp(x.surname, temp.surname) == 0 && strcmp(x.name, temp.name) > 0)
                    || strcmp(x.surname, temp.surname) > 0)
                {
                    cr = put_pers_by_pos(f, j + 1, &x);
                    cr = put_pers_by_pos(f, j, &temp);
                }
            }
        }
        fclose(f);
    }

    return cr;
}

void print_file(char *file_name, int n)
{
    FILE *f = fopen(file_name, "rb");
    for (int i = 0; i < n; i++)
        print_struct(f, i);
    fclose(f);
}

void print_struct(FILE *f, int pos)
{
    struct student temp;
    get_pers_by_pos(f, pos, &temp);

    printf("%s\n", temp.surname);
    printf("%s\n", temp.name);

    for (int k = 0; k < M; k++)
        printf("%d ", (temp.marks)[k]);
    printf("\n");
}
