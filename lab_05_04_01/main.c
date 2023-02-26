#include "sort.h"
#include "find.h"
#include "del.h"

#define KEY_ERROR 53

int main(int argc, char **argv)
{
    int n, code_return = OK;

    if (argc == 3 && !strcmp(argv[1], "sb"))
    {
        code_return = sort_bin(argv[2], &n);
        if (!code_return)
            print_file(argv[2], n);
    }
    else if (argc == 5 && !strcmp(argv[1], "fb"))
        code_return = find_bin(argv[2], argv[3], argv[4]);
    else if (argc == 3 && !strcmp(argv[1], "db"))
        code_return = del_bin(argv[2]);
    else
        code_return = KEY_ERROR;

    return code_return;
}