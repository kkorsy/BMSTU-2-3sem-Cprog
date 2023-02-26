#ifndef __FIND_NUM_H__
#define __FIND_NUM_H__

#include <stdio.h>
#define OK 0
#define ERR_ARGC -1
#define ERR_FILE -2
#define NO_DATA -3

int average(FILE *f, double *avg);
int find_num(FILE *f, double *res, double avg);

#endif