#ifndef __BY_POS_H__
#define __BY_POS_H__

#include <stdio.h>
#include "errors.h"

int get_number_by_pos(FILE *f, int pos, int *num);
int put_number_by_pos(FILE *f, int pos, int num);
int get_size(FILE *f, size_t *size);

#endif