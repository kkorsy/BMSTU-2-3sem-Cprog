#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define OK 0
#define ERROR 1
#define STR_LEN 256
#define N 12
#define MIN_LEN 7

int read_str(char *s);
int check_date(char *s);
int form_new_s(char *s, char *new_s);
int get_day(const char *s, int *ind);
int get_month(const char *s, int *ind);
int get_year(const char *s, int ind);

int main(void)
{
    int code_return = OK;
    char s[STR_LEN + 1];

    code_return = read_str(s);
    if (!code_return)
    {
        if (check_date(s))
            printf("YES");
        else
            printf("NO");
    }

    return code_return;
}

int read_str(char *s)
{
    int i = 0, code_return = OK;
    char ch;

    while (!code_return && (ch = getchar()) != '\n')
    {
        if (i < STR_LEN)
            s[i++] = ch;
        else
            code_return = ERROR;
    }
    s[i] = '\0';

    return code_return;
}

int check_date(char *s)
{
    int res = 1, ind;
    char new_s[STR_LEN + 1];

    if (form_new_s(s, new_s))
        res = 0;
    else
    {
        long day = get_day(new_s, &ind);
        int month = get_month(new_s, &ind);
        long year = get_year(new_s, ind);

        if (day == -1 || month == -1 || year == -1 || day < 1 || day > 31)
            res = 0;
        else if (month == 4 || month == 6 || month == 9 || month == 11)
            res = (day <= 30);
        else if (month == 2)
        {
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
                res = (day <= 29);
            else
                res = (day <= 28);
        }
    }

    return res;
}

int get_year(const char *s, int ind)
{
    int year, correct = 1;
    char *pend;

    if (s[ind] == '\0')
        correct = 0;
    else
    {
        if (s[ind + 1] == '+')
            correct = 0;
        else
        {
            year = strtol(s + ind, &pend, 10);
            if (year <= 0 || *pend != '\0')
                correct = 0;
        }
    }

    return correct ? year : -1;
}

int get_month(const char *s, int *ind)
{
    char *month_list[N] = { "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december" };
    int correct = 1;
    int n = -1, i, j = 0;
    char month[STR_LEN + 1];

    if (s[*ind] == '\0')
        correct = 0;
    else
    {
        for (i = *ind + 1; s[i] != '\0' && !isspace(s[i]); i++)
            month[j++] = tolower(s[i]);
        month[j] = '\0';
        *ind = i;

        for (j = 0; month[j] != '\0'; j++)
            if (!isalpha(month[j]))
                correct = 0;

        if (correct)
            for (j = 0; j < N; j++)
                if (!strcmp(month, month_list[j]))
                {
                    n = j + 1;
                    break;
                }
    }

    return correct ? n : -1;
}

int get_day(const char *s, int *ind)
{
    int correct = 1;
    int i;
    char day[STR_LEN + 1];

    for (i = 0; s[i] != '\0' && !isspace(s[i]); i++)
        day[i] = s[i];
    day[i] = '\0';
    *ind = i;

    for (int j = 0; day[j] != '\0'; j++)
        if (!isdigit(day[j]))
            correct = 0;

    return correct ? strtol(day, NULL, 10) : -1;
}

int form_new_s(char *s, char *new_s)
{
    int len = strlen(s);
    int j = 0, code_return = OK;

    for (int i = 0; i < len; i++)
        if (!isspace(s[i]) || (i != 0 && !isspace(s[i - 1])))
            new_s[j++] = s[i];

    if (j != 0 && isspace(new_s[j - 1]))
        new_s[j - 1] = '\0';
    else
        new_s[j] = '\0';

    if (strlen(new_s) < MIN_LEN)
        code_return = ERROR;

    return code_return;
}
