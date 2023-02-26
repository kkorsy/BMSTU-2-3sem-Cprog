#include "str.h"
#include "math.h"

int write_str(char *buf, size_t num, char *substr)
{
    char *s = substr;
    if (substr == NULL)
    {
        char new_substr[] = "(null)";
        s = new_substr;
    }
    
    size_t i;

    for (i = 0; s[i] != '\0'; i++)
        if (buf && num && i < num)
            buf[i] = s[i];
    
    return i;
}

int write_oct(char *buf, size_t num, unsigned long int oct)
{
    int oct_len = num_len(oct);

    size_t i;
    for (i = 0; oct_len; i++)
    {
        long int k = pow(10, (oct_len - 1));

        if (buf && num && i < num)
            buf[i] = int_to_char(oct / k);

        oct %= k;
        oct_len--;
    }
    
    return i;
}

char int_to_char(int x)
{
    return x + '0';
}

int num_len(unsigned long int num)
{
    if (num == 0)
        return 1;
    
    int i = 0;
    while (num)
    {
        num /= 10;
        i++;
    }

    return i;
}

unsigned long int convert_to_oct(unsigned int num)
{
    long int oct = 0;
    unsigned long int k = 1;
    
    while (num)
    {
        oct += (num % 8) * k;

        k *= 10;
        num /= 8;
    }

    return oct;
}