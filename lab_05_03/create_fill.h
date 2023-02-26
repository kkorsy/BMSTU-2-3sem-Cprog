#ifndef __CREATE_FILL_H__
#define __CREATE_FILL_H__

#include "errors.h"
#include <stdio.h>

int create_file(char *file_name, int num);
int fill_file(FILE *f, int num);

#endif