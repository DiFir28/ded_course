#ifndef __Onegin__
#define __Onegin__

#include <stdint.h>
#include "din_arr.h"

#define HASH_LEN 40

struct Line_ptr{
    char *beg;
    size_t len;
};

struct Hash_ptr{
    char *beg;
    char hash[HASH_LEN];
    uint8_t hash_len;
};

int ptrs_cmp(const void *a_ptr, const void *b_ptr);
int reverse_ptrs_cmp(const void *a_ptr, const void *b_ptr);

int hash_cmp(const void* a_ptr, const void* b_ptr);

void caclLines(mVector* lines_ptrs, mVector* reverse_lines_ptrs, char *book, unsigned long long letters_read);
void calcHash(mVector *lines_ptrs_arr, char *book, long long start_iter, long long end_iter, bool reverse_flag);

#endif