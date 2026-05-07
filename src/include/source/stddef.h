#ifndef OW_STDDEF_H
#define OW_STDDEF_H

#include "stdint.h"

typedef uint32_t    size_t;
typedef int32_t     ptrdiff_t;

#define NULL        ((void *)0)
#define offsetof(type, member) ((size_t)&((type *)0)->member)

#endif