#ifndef __Onegin__
#define __Onegin__

#include <stdint.h>
#include "din_arr.h"

#define HASH_LEN 40

struct Hash_ptr{
    char *beg;
    char hash[HASH_LEN];
    uint8_t hash_len;
};

int ptrs_cmp(const void *a_ptr, const void *b_ptr);
int reverse_ptrs_cmp(const void *a_ptr, const void *b_ptr);

int hash_cmp(const void* a_ptr, const void* b_ptr);

void calcHash(mVector *lines_ptrs_arr, char *book, long long start_iter, long long end_iter, bool reverse_flag);

#endif