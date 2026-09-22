#ifndef __STR_ENCODE__
#define __STR_ENCODE__

#include <stdint.h>
#include "din_arr.h"

#define HASH_LEN 40 //! must devided by 8

struct Line_ptr{
    char *beg;
    char hash[HASH_LEN];
    uint8_t hash_len;
};

int Line_cmp(const void* a_ptr, const void* b_ptr);

void calcHash(mVector *lines_ptrs_arr, char *book, long long start_iter, long long iter_step, long long end_iter, bool reverse_flag);

#endif