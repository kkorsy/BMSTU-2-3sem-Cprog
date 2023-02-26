#include "find.h"

int find_bin(char *src, char *dst, char *substr)
{
    int n, cr = OK;
    FILE *f_src = fopen(src, "rb");

    cr = (check_bin(f_src, &n)) || (strcmp(src, dst) == 0);
    if (cr && cr != OPEN_ERROR)
        fclose(f_src);
    else if (!cr)
    {
        FILE *f_dst = fopen(dst, "wb");
        if (f_dst == NULL)
            cr = OPEN_ERROR;
        else
        {
            struct student pers;
            size_t size;

            for (int i = 0; !cr && i < n; i++)
            {
                cr = get_pers_by_pos(f_src, i, &pers);
                if (!cr && strstr(pers.surname, substr) == pers.surname)
                    if (fwrite(&pers, sizeof(struct student), 1, f_dst) != 1)
                        cr = WRITE_ERROR;
            }
            cr = get_size(f_dst, &size);
            if (size / sizeof(struct student) < 1)
                cr = NO_DATA;
            fclose(f_dst);
        }
        fclose(f_src);
    }

    return cr;
}