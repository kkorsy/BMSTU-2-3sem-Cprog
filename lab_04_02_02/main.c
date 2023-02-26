#include <stdio.h>
#include <string.h>
#define STR_LEN 256
#define WORD_LEN 16
#define N STR_LEN / 2
#define OK 0
#define ERROR 1

int read_line(char *s);
int count_words(char *str);
int split(char *str, char words[][WORD_LEN + 1], int n);
int end_word_check(char s);
int find_word(char *w, char words[][WORD_LEN + 1], int n);
void str_check(char words1[][WORD_LEN + 1], char words2[][WORD_LEN + 1], int n1, int n2);

int main(void)
{
    int code_return = OK;
    char str1[STR_LEN + 1], str2[STR_LEN + 1];

    if (read_line(str1) || read_line(str2))
        code_return = ERROR;
    else
    {
        int n1 = count_words(str1), n2 = count_words(str2);
        if (n1 == 0 || n1 > N || n2 == 0 || n2 > N)
            code_return = ERROR;
        else
        {
            char words1[N][WORD_LEN + 1], words2[N][WORD_LEN + 1];
            if (split(str1, words1, n1) || split(str2, words2, n2))
                code_return = ERROR;
            else
                str_check(words1, words2, n1, n2);
        }
    }

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

int find_word(char *w, char words[][WORD_LEN + 1], int n)
{
    int res = 0;
    for (int i = 0; i < n && !res; i++)
        if (strcmp(w, words[i]) == 0)
            res = 1;

    return res;
}

void str_check(char words1[][WORD_LEN + 1], char words2[][WORD_LEN + 1], int n1, int n2)
{
    printf("Result: ");
    for (int i = 0; i < n1; i++)
    {
        if (!find_word(words1[i], words1, i))
        {
            if (find_word(words1[i], words2, n2))
                printf("%s yes\n", words1[i]);
            else
                printf("%s no\n", words1[i]);
        }
    }
}

int count_words(char *str)
{
    int k = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (!end_word_check(str[i]) && end_word_check(str[i + 1]))
            k++;

    return k;
}

int split(char *str, char words[][WORD_LEN + 1], int n)
{
    int k = 0, j;
    int overflow = 0;

    for (int i = 0; i < n; i++)
    {
        while (end_word_check(str[k]))
            k++;

        j = 0;
        while (!overflow && !end_word_check(str[k]))
        {
            if (j < WORD_LEN)
                words[i][j++] = str[k++];
            else
                overflow = 1;
        }
        words[i][j] = '\0';
    }

    return overflow;
}

int end_word_check(char s)
{
    int res = 0;
    char symb[] = " ,;:-.!?";
    for (int i = 0; symb[i] != '\0'; i++)
        if (s == symb[i])
            res = 1;

    if (s == '\0' || s == '\n' || s == '\t')
        res = 1;

    return res;
}
