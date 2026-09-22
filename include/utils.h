#ifndef __UTILS__
#define __UTILS__

#define sing(num) (num > 0? 1: -1)
#define bool2sign(bool_exp) (bool_exp? 1: -1)

void swap(void * first, void * second, size_t byte_count);

#endif