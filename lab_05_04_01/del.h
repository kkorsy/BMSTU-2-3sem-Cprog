#ifndef __DEL_H__
#define __DEL_H__

#include <stdio.h>
#include <unistd.h>

int del_bin(char *file_name);
int average_in_file(FILE *f, int n, double *avg);
void average(unsigned int *a, double *avg);
int deletion(FILE *f, char *file_name, int pos, int *n);

#endif