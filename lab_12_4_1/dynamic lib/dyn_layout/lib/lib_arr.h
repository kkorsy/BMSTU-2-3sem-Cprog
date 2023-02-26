#ifndef __LIB_ARR_H__
#define __LIB_ARR_H__

#include <stdio.h>
#include "errors.h"

void mysort(void *base, size_t n, size_t elem_size, int (*cmp)(const void *, const void *));
int cmp(const void *pl, const void *pr);
void swap(void *pl, void *pr, size_t elem_size);
void key(const int *pb_src, const int *pe_src, int *const pb_dst, double avg);
int num_count(const int *pb, const int *pe, double avg);
double average(const int *pb, const int *pe);
int array_write(char *file_name, int *pb, int *pe);
int print(FILE *f, int *pb, int *pe);
int array_read(char *file_name, int **arr, size_t *n);
void array_fill(FILE *f, int *pb, int *pe);
int elem_count(FILE *f, size_t *n);

#endif