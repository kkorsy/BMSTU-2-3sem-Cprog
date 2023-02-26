#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define OK 0
#define SURN_LEN 25
#define N_LEN 10
#define M 4

int sort_bin(char *file_name, int *n);
void print_file(char *file_name, int n);
void print_struct(FILE *f, int pos);

#endif