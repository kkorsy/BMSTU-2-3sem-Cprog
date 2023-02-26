/*
выбранный целочисленный тип - int
алгоритм сортировки - сортировка вставками
упорядочивание - по возрастанию
*/
#include <stdlib.h>
#include <string.h>
#include "create_fill.h"
#include "print_file.h"
#include "sort.h"

int main(int argc, char **argv)
{
    int code_return = OK;

    if (argc == 4 && !strcmp(argv[1], "c"))
    {
        char *file_name = argv[3];
        int k = atoi(argv[2]);

        if (k < 0)
            code_return = KEY_ERROR;
        else
            code_return = create_file(file_name, k);
    }
    else if (argc == 3 && !strcmp(argv[1], "p"))
    {
        char *file_name = argv[2];
        code_return = print(file_name);
    }
    else if (argc == 3 && !strcmp(argv[1], "s"))
    {
        char *file_name = argv[2];
        code_return = sort(file_name);
    }
    else
        code_return = KEY_ERROR;

    return code_return;
}