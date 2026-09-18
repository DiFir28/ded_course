#include "str_alpha_encode.h"
#include <stdint.h>
#include <ctype.h>
#include "din_arr.h" 
#include "utils.h"

int Line_cmp(const void* a_ptr, const void* b_ptr){
    Line_ptr a = *(Line_ptr*)a_ptr;
    Line_ptr b = *(Line_ptr*)b_ptr;
    unsigned cmp_iter = 0;
    while(uint32_t(a.hash[cmp_iter]) == uint32_t(b.hash[cmp_iter]) && cmp_iter + 8 < HASH_LEN - 1){ //! step by 8
        cmp_iter+=4;
    }
    if (uint32_t(a.hash[cmp_iter]) == uint32_t(b.hash[cmp_iter])){
        return 0;
    }
    return bool2sign(uint32_t(a.hash[cmp_iter]) > uint32_t(b.hash[cmp_iter]));
}

void calcHash(mVector *lines_ptrs_arr, char *book, long long start_iter, long long iter_step, long long end_iter, bool reverse_flag){
    long long iter = start_iter;
    while (iter < end_iter && iter > 0)
    {
        Line_ptr buf = {(book + iter), 0, 0};
        unsigned hash_iter = 0;
        while (iter < end_iter && iter > 0 && *(book + iter) != '\n')
        {
            if (isalpha(*(book + iter)))
            {
                buf.hash[(hash_iter / 8)] |= (toupper(*(book + iter)) & 0x1F) << 3 >> (hash_iter % 8);
                if (hash_iter % 8 > 3){
                    buf.hash[(hash_iter / 8) + 1] |= (toupper(*(book + iter)) & 0x1F) << 11 >> (hash_iter % 8);
                }
                hash_iter += 5;
            }
            buf.hash_len = hash_iter;
            iter+=iter_step;
        }
        if (reverse_flag)
        {
            buf.beg = book + iter + 1;
        }
        iter+=iter_step;
        if (buf.hash_len > 0){
            pushBack(lines_ptrs_arr, &buf);
        }
        // printf("%d %d\n", iter, end_iter);
    }
    // printf("End!");
}