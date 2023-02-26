#include "snprintf.h"
#include "str.h"
#include <stdarg.h>

int my_snprintf(char *restrict buf, size_t num, const char *restrict format, ...)
{
    if ((buf == NULL && num != 0) || format == NULL)
        return -1;

    size_t written = 0, cur = 0;
    char *substr;
    unsigned int x;

    va_list vl;
    va_start(vl, format);

    while (format[cur] != '\0')
    {
        while (format[cur] != '%' && format[cur] != '\0')
        {
            if (num && buf && written < num - 1)
                buf[written] = format[cur];
            written++;
            cur++;
        }
        if (format[cur] == '\0')
            break;
        cur++;
        
        size_t n = (num && written < num) ? (num - written - 1) : 0;
        
        char *str_cut = (buf) ? (buf + written) : buf;

        if (format[cur] == 's')
        {
            substr = va_arg(vl, char *);
            written += write_str(str_cut, n, substr);
        }
        else if (format[cur] == 'o')
        {
            x = va_arg(vl, unsigned int);
            written += write_oct(str_cut, n, convert_to_oct(x));
        }
        else if (num && format[cur] == '%')
            buf[written++] = '%';
        else
        {
            va_end(vl);
            return -1;
        }
        cur++;
    }
    
    if (num && buf && written > num - 1)
        buf[num - 1] = '\0';
    else if (num && buf)
        buf[written] = '\0';

    va_end(vl);

    return written;
}
