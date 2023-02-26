#include <stdio.h>
#include <string.h>
#define OK 0

char *find_symb(char symb, const char *str);
char *my_strpbrk(const char *str1, const char *str2);
size_t my_strspn(const char *str1, const char *str2);
size_t my_strcspn(const char *str1, const char *str2);
char *my_strchr(const char *str, int symb);
char *my_strrchr(const char *str, int symb);

int main(void)
{
    int failed = 0;
    
    // обычный тест
    char str1_1[] = "Hello world";
    char str2_1[] = "rdHlo";
    if (strpbrk(str1_1, str2_1) != my_strpbrk(str1_1, str2_1))
        failed++;
    if (strspn(str1_1, str2_1) != my_strspn(str1_1, str2_1))
        failed++;
    if (strcspn(str1_1, str2_1) != my_strcspn(str1_1, str2_1))
        failed++;

    // в str1 нет символов из str2
    char str1_2[] = "Hello world";
    char str2_2[] = "abcf";
    if (strpbrk(str1_2, str2_2) != my_strpbrk(str1_2, str2_2))
        failed++;
    if (strspn(str1_2, str2_2) != my_strspn(str1_2, str2_2))
        failed++;
    if (strcspn(str1_2, str2_2) != my_strcspn(str1_2, str2_2))
        failed++;

    // все символы str1 есть в str2
    char str1_3[] = "Hello world";
    char str2_3[] = "Helowrd ";
    if (strpbrk(str1_3, str2_3) != my_strpbrk(str1_3, str2_3))
        failed++;
    if (strspn(str1_3, str2_3) != my_strspn(str1_3, str2_3))
        failed++;
    if (strcspn(str1_3, str2_3) != my_strcspn(str1_3, str2_3))
        failed++;    

    // обычный тест
    char str1_4[] = "Hello world";
    char symb_4 = 'l';
    if (strchr(str1_4, symb_4) != my_strchr(str1_4, symb_4))
        failed++;
    if (strrchr(str1_4, symb_4) != my_strrchr(str1_4, symb_4))
        failed++;

    // символа нет в строке
    char str1_5[] = "Hello world";
    char symb_5 = 'a';
    if (strchr(str1_5, symb_5) != my_strchr(str1_5, symb_5))
        failed++;
    if (strrchr(str1_5, symb_5) != my_strrchr(str1_5, symb_5))
        failed++;

    // первый символ
    char str1_6[] = "Hello world";
    char symb_6 = 'H';
    if (strchr(str1_6, symb_6) != my_strchr(str1_6, symb_6))
        failed++;
    if (strrchr(str1_6, symb_6) != my_strrchr(str1_6, symb_6))
        failed++;

    // последний символ
    char str1_7[] = "Hello world";
    char symb_7 = 'd';
    if (strchr(str1_7, symb_7) != my_strchr(str1_7, symb_7))
        failed++;
    if (strrchr(str1_7, symb_7) != my_strrchr(str1_7, symb_7))
        failed++;

    // строка состоит из одинаковых букв
    char str1_8[] = "aaaaaaaa a a; a";
    char symb_8 = 'a';
    if (strchr(str1_8, symb_8) != my_strchr(str1_8, symb_8))
        failed++;
    if (strrchr(str1_8, symb_8) != my_strrchr(str1_8, symb_8))
        failed++;

     // искомый символ - нулевой
    char str1_9[] = "Hello world";
    char symb_9 = '\0';
    if (strchr(str1_9, symb_9) != my_strchr(str1_9, symb_9))
        failed++;
    if (strrchr(str1_9, symb_9) != my_strrchr(str1_9, symb_9))
        failed++;

    printf("%d\n", failed);

    return OK;
}

// есть ли символ в строке
char *find_symb(char symb, const char *str)
{
    char *p = NULL;
    int i, find = 0;
    for (i = 0; str[i] != '\0' && !find; i++)
        if (symb == str[i])
            find = 1;

    if (find)
        p = (char *) str + i - 1;

    return p;
}

char *my_strpbrk(const char *str1, const char *str2)
{
    int find = 0;
    char *p = NULL;
    for (int i = 0; str1[i] != '\0' && !find; i++)
        if (find_symb(str1[i], str2))
        {
            p = (char *) str1 + i;
            find = 1;
        }
    
    return p;
}

size_t my_strspn(const char *str1, const char *str2)
{
    size_t len;
    int i, end = 0;
    for (i = 0; str1[i] != '\0' && !end; i++)
        if (!find_symb(str1[i], str2))
            end = 1;

    if (!end)
        len = i;
    else
        len = i - 1;

    return len;
}

size_t my_strcspn(const char *str1, const char *str2)
{
    size_t len;
    int i, end = 0;
    for (i = 0; str1[i] != '\0' && !end; i++)
        if (find_symb(str1[i], str2))
            end = 1;

    if (!end)
        len = i;
    else
        len = i - 1;

    return len;
}

char *my_strchr(const char *str, int symb)
{
    char *p = NULL;
    p = find_symb(symb, str);

    if (symb == '\0')
        p = (char *) str + strlen(str);

    return p;
}

char *my_strrchr(const char *str, int symb)
{
    char *p = NULL;
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == symb)
            p = (char *) str + i;
    }

    if (symb == '\0')
        p = (char *) str + i;

    return p;
}
