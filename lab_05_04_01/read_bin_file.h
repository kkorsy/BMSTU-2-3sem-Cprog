#ifndef __READ_BIN_FILE_H__
#define __READ_BIN_FILE_H__

#include <stdio.h>
#include <stdbool.h>

#define OK 0
#define READ_ERROR -1
#define OPEN_ERROR 1
#define NO_DATA 2
#define GET_SIZE_ERROR 3
#define WRITE_ERROR 4
#define SEEK_ERROR 5
#define SURN_LEN 25
#define N_LEN 10
#define M 4

struct student
{
    char surname[SURN_LEN + 1];
    char name[N_LEN + 1];
    int unsigned marks[M];
};

int check_bin(FILE *f, int *n);
int get_size(FILE *f, size_t *size);
int get_pers_by_pos(FILE *f, int pos, struct student *pers);
int put_pers_by_pos(FILE *f, int pos, struct student *pers);

#endif