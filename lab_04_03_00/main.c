#include <stdio.h>
#include <string.h>
#define STR_LEN 256
#define WORD_LEN 16
#define N STR_LEN / 2
#define OK 0
#define ERROR 1

int read_line(char *s);
int split(char *s, char words[][WORD_LEN + 1], int *n);
int form_res_string(char *res_str, char words[][WORD_LEN + 1], int n);
void convert(char *s);

int main(void)
{
    int n, code_return = OK;
    char s[STR_LEN + 1];
    char words[N][WORD_LEN + 1];

    if (!read_line(s) && !split(s, words, &n))
    {
        char res_str[STR_LEN + 1] = "";
        code_return = form_res_string(res_str, words, n);
        if (code_return == OK)
            printf("Result: %s\n", res_str);
    }
    else
        code_return = ERROR;

    return code_return;
}

void convert(char *s)
{
    int j = 1;
    for (int i = 1; s[i] != '\0'; i++)
        if (s[i] != s[0])
            s[j++] = s[i];
    s[j] = '\0';
}

int form_res_string(char *res_str, char words[][WORD_LEN + 1], int n)
{
    int j = 0, code_return = OK;

    for (int i = n - 2; i >= 0; i--)
        if (strcmp(words[n - 1], words[i]) != 0)
        {
            convert(words[i]);
            strcat(res_str, words[i]);
            strcat(res_str, " ");

            j += strlen(words[i]) + 1;
        }

    if (j == 0)
        code_return = ERROR;
    else
        res_str[j - 1] = '\0';

    return code_return;
}

int split(char *s, char words[][WORD_LEN + 1], int *n)
{
    int code_return = OK;
    char *pword = strtok(s, " ,;:-.!?\n");
    int j, i = 0;

    while (!code_return && pword)
    {
        if (i < N && strlen(pword) < WORD_LEN)
        {
            for (j = 0; pword[j] != '\0'; j++)
                words[i][j] = pword[j];

            words[i++][j] = '\0';
            pword = strtok(NULL, " ,;:-.!?\n");
        }
        else
            code_return = ERROR;
    }

    if (i == 0)
        code_return = ERROR;

    *n = i;

    return code_return;
}

int read_line(char *s)
{
    int i = 0, overflow = 0;
    char ch;
    while (!overflow && (ch = getchar()) != '\n')
    {
        if (i < STR_LEN)
            s[i++] = ch;
        else
            overflow = 1;
    }
    s[i] = '\0';

    return overflow;
}
