#ifndef OW_STDIO_H
#define OW_STDIO_H

#include "stddef.h"
#include "stdarg.h"
#include "stdint.h"

void putchar(char c);

static inline void puts(const char *s)
{
    while (*s) putchar(*s++);
    putchar('\n');
}

static inline void _put_uint(uint32_t n, uint8_t base)
{
    char buf[32];
    int  i = 0;
    if (n == 0) { putchar('0'); return; }
    while (n) {
        uint8_t d = (uint8_t)(n % base);
        buf[i++]  = (char)(d < 10 ? '0' + d : 'a' + d - 10);
        n /= base;
    }
    while (i--) putchar(buf[i]);
}

static inline void printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    while (*fmt) {
        if (*fmt != '%') { putchar(*fmt++); continue; }
        fmt++;
        switch (*fmt) {
            case 'c':
                putchar((char)va_arg(ap, int));
                break;
            case 's': {
                const char *s = va_arg(ap, const char *);
                while (s && *s) putchar(*s++);
                break;
            }
            case 'd': {
                int32_t n = va_arg(ap, int32_t);
                if (n < 0) { putchar('-'); n = -n; }
                _put_uint((uint32_t)n, 10);
                break;
            }
            case 'u':
                _put_uint(va_arg(ap, uint32_t), 10);
                break;
            case 'x':
                _put_uint(va_arg(ap, uint32_t), 16);
                break;
            case '%':
                putchar('%');
                break;
            default:
                putchar('%');
                putchar(*fmt);
                break;
        }
        fmt++;
    }

    va_end(ap);
}

#endif