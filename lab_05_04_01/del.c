#include "del.h"
#include "read_bin_file.h"

int del_bin(char *file_name)
{
    struct student pers;
    double avg, pers_avg;
    int n, cr = OK;
    FILE *f = fopen(file_name, "rb");

    cr = check_bin(f, &n);
    if (cr && cr != OPEN_ERROR)
        fclose(f);
    else if (!cr)
    {
        fclose(f);
        f = fopen(file_name, "rb+");
        cr = average_in_file(f, n, &avg);
        for (int i = 0; !cr && i < n; i++)
        {
            cr = get_pers_by_pos(f, i, &pers);
            if (!cr)
            {
                average(pers.marks, &pers_avg);
                if (pers_avg < avg)
                {
                    cr = deletion(f, file_name, i, &n);
                    i--;
                }
            }
        }
        fclose(f);
    }

    return cr;
}

int average_in_file(FILE *f, int n, double *avg)
{
    int cr = OK;
    struct student temp;
    double pers_avg, sum = 0;

    for (int i = 0; !cr && i < n; i++)
    {
        cr = get_pers_by_pos(f, i, &temp);
        average(temp.marks, &pers_avg);
        sum += pers_avg;
    }
    *avg = sum / n;  

    return cr;  
}

void average(unsigned int *a, double *avg)
{
    double sum = 0;

    for (int i = 0; i < M; i++)
        sum += a[i];
    
    *avg = sum / M;
}

int deletion(FILE *f, char *file_name, int pos, int *n)
{
    int cr = OK;
    struct student temp;

    for (int i = pos + 1; !cr && i < *n; i++)
    {
        cr = get_pers_by_pos(f, i, &temp);
        cr = put_pers_by_pos(f, i - 1, &temp);
    }
    (*n)--;

    if (!cr)
    {
        size_t size = (*n) * sizeof(struct student);
        if (fseek(f, size, SEEK_SET))
            cr = SEEK_ERROR;
        else
            cr = truncate(file_name, ftell(f));
    }

    return cr;
}
