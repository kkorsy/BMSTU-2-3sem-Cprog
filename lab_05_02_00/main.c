#include "find_num.h"

int main(int argc, char **argv)
{
    FILE *f;
    int code_return = OK;
    double res, avg;

    if (argc != 2)
        code_return = ERR_ARGC;
    else
    {
        f = fopen(argv[1], "r");
        if (!f)
            code_return = ERR_FILE;
        else
        {
            if (average(f, &avg))
                code_return = NO_DATA;
            else
            {
                rewind(f);
                code_return = find_num(f, &res, avg);
                fclose(f);

                if (!code_return)
                    printf("%lf\n", res);
            }
        }
    }

    return code_return;
}