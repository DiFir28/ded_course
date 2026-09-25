#ifndef __UTILS__
#define __UTILS__

#define sign(num) (num > 0? 1: -1)
#define bool2sign(bool_exp) (bool_exp? 1: -1)

#include <ctype.h>

void swap(void * first, void * second, size_t byte_count);

#endif