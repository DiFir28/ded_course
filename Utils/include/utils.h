#ifndef __UTILS__
#define __UTILS__

#include <ctype.h>

#define sign(num) (num > 0? 1: -1)
#define bool2sign(bool_exp) (bool_exp? 1: -1)
#define dumpDir "dump.txt"

void swap(void * first, void * second, size_t byte_count);

#endif