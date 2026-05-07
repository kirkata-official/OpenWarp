#ifndef OW_STDLIB_H
#define OW_STDLIB_H

#include "stdint.h"
#include "stddef.h"

static inline char *itoa(int32_t n, char *buf, uint8_t base)
{
    char    tmp[33];
    char   *p   = tmp + sizeof(tmp) - 1;
    uint8_t neg = 0;
    uint32_t u;

    *p = '\0';

    if (base == 10 && n < 0) { neg = 1; u = (uint32_t)(-(n + 1)) + 1u; }
    else                      { u = (uint32_t)n; }

    if (u == 0) { *--p = '0'; }
    else {
        while (u) {
            uint8_t d = (uint8_t)(u % base);
            *--p = (char)(d < 10 ? '0' + d : 'a' + d - 10);
            u /= base;
        }
    }
    if (neg) *--p = '-';

    char *out = buf;
    while (*p) *out++ = *p++;
    *out = '\0';
    return buf;
}

static inline int32_t atoi(const char *s)
{
    int32_t  result = 0;
    uint8_t  neg    = 0;

    while (*s == ' ' || *s == '\t') s++;
    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') { s++; }

    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return neg ? -result : result;
}

static inline void *memset(void *dst, int val, size_t n)
{
    uint8_t *p = (uint8_t *)dst;
    while (n--) *p++ = (uint8_t)val;
    return dst;
}

static inline void *memcpy(void *dst, const void *src, size_t n)
{
    uint8_t       *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (n--) *d++ = *s++;
    return dst;
}

static inline int memcmp(const void *a, const void *b, size_t n)
{
    const uint8_t *p = (const uint8_t *)a;
    const uint8_t *q = (const uint8_t *)b;
    while (n--) {
        if (*p != *q) return (int)*p - (int)*q;
        p++; q++;
    }
    return 0;
}

static inline size_t strlen(const char *s)
{
    size_t n = 0;
    while (*s++) n++;
    return n;
}

static inline char *strcpy(char *dst, const char *src)
{
    char *out = dst;
    while ((*dst++ = *src++))
        ;
    return out;
}

static inline int strcmp(const char *a, const char *b)
{
    while (*a && *a == *b) { a++; b++; }
    return (int)(unsigned char)*a - (int)(unsigned char)*b;
}

static inline char *strncpy(char *dst, const char *src, size_t n)
{
    char *out = dst;
    while (n && (*dst++ = *src++)) n--;
    while (n--) *dst++ = '\0';
    return out;
}

static inline int strncmp(const char *a, const char *b, size_t n)
{
    while (n && *a && *a == *b) { a++; b++; n--; }
    if (n == 0) return 0;
    return (int)(unsigned char)*a - (int)(unsigned char)*b;
}

#endif