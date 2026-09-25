#include "Onegin.h"

#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include "din_arr.h" 
#include "utils.h"

int ptrs_cmp(const void *a_ptr, const void *b_ptr){
    const char * const first_str = ((Line_ptr*) a_ptr)->beg;
    const char * const second_str = ((Line_ptr*) b_ptr)->beg;
    int first_iter = 0;
    int second_iter = 0;
    while (!isalpha(first_str[first_iter]) && first_str[first_iter] != '\n'){
        first_iter++;
    }
    while (!isalpha(second_str[second_iter]) && second_str[second_iter] != '\n'){
        second_iter++;
    }
    while (toupper(first_str[first_iter]) == toupper(second_str[second_iter]) && first_str[first_iter] != '\n'){
    do{
        first_iter++;
    }while (!isalpha(first_str[first_iter]) && first_str[first_iter] != '\n');
    do{
        second_iter++;
    }while (!isalpha(second_str[second_iter]) && second_str[second_iter] != '\n');
    }
    if (toupper(first_str[first_iter]) == toupper(second_str[second_iter])){
        return 0;
    }
    return bool2sign(toupper(first_str[first_iter]) > toupper(second_str[second_iter]));
}

int reverse_ptrs_cmp(const void *a_ptr, const void *b_ptr){
    const char * const first_str = ((Line_ptr*) a_ptr)->beg;
    const char * const second_str = ((Line_ptr*) b_ptr)->beg;
    
    int first_iter = ((Line_ptr*) a_ptr)->len;
    int second_iter =  ((Line_ptr*) b_ptr)->len;
   
    while (!isalpha(first_str[first_iter])){
        first_iter--;
    }
    while (!isalpha(second_str[second_iter])){
        second_iter--;
    }
    while (toupper(first_str[first_iter]) == toupper(second_str[second_iter]) && first_str[first_iter] != '\n'){
        do{
            first_iter--;
        }while (!isalpha(first_str[first_iter]) && first_str[first_iter] != '\n');
        do{
            second_iter--;
        }while (!isalpha(second_str[second_iter]) && second_str[second_iter] != '\n');
    }
    if (toupper(first_str[first_iter]) == toupper(second_str[second_iter])){
        return 0;
    }
    return bool2sign(toupper(first_str[first_iter]) > toupper(second_str[second_iter]));
}

int hash_cmp(const void* a_ptr, const void* b_ptr){
    Hash_ptr a = *(Hash_ptr*)a_ptr;
    Hash_ptr b = *(Hash_ptr*)b_ptr;
    unsigned cmp_iter = 32;
    while(*(uint64_t*)(&a.hash[cmp_iter]) == *(uint64_t*)(&b.hash[cmp_iter]) && cmp_iter >= 8){ //! step by 8
        cmp_iter-=8;
    }
    if (*(uint64_t*)(&a.hash[cmp_iter]) == *(uint64_t*)(&b.hash[cmp_iter])){
        return 0;
    }
    return bool2sign(*(uint64_t*)(&a.hash[cmp_iter]) > *(uint64_t*)(&b.hash[cmp_iter]));
}

void caclLines(mVector* lines_ptrs, mVector* reverse_lines_ptrs, char *book, unsigned long long letters_read){
    for (int i = 0; i < letters_read + 3; i++){
        if (book[i] == '\n' && book[i + 1] != '\n'){
            Line_ptr buff = {(book + i + 1), 0};
            pushBack(lines_ptrs, &buff);
            if (lines_ptrs->len <= 1){
                continue;
            }
            Line_ptr* prev_buff = (Line_ptr*)getElementPtr(lines_ptrs, lines_ptrs->len - 2);
            prev_buff->len = (book + i + 1 - (char*)prev_buff->beg);
            pushBack(reverse_lines_ptrs, prev_buff);
        }
    }
    pushBack(reverse_lines_ptrs, getElementPtr(lines_ptrs, lines_ptrs->len - 1));
}

void calcHash(mVector *lines_ptrs_arr, char *book, long long start_iter, long long end_iter, bool reverse_flag){
    long long iter = start_iter;
    long long iter_step = -sign(reverse_flag);
    while (iter < end_iter + 1 && iter > 0)
    {
        Hash_ptr buff= {(book + iter), 0, 0};
        unsigned hash_iter = 0;
        while (iter < end_iter + 1 && iter > 0 && *(book + iter) != '\n')
        {
            if (isalpha(*(book + iter)))
            {
                buff.hash[39 - (hash_iter / 8)] |= (toupper(*(book + iter)) & 0x1F) << 3 >> (hash_iter % 8); //* Write 5 bit that placed in curent byte
                if (hash_iter % 8 > 3){
                    buff.hash[38 - (hash_iter / 8)] |= (toupper(*(book + iter)) & 0x1F) << (11 - hash_iter % 8); //* Write 5 bit that don't placed in curent byte
                }
                hash_iter += 5; //* Do step by 5 bits (5 bit per letter of upper alpha) 
            }
            buff.hash_len = hash_iter;
            iter+=iter_step;
        }        
        if (reverse_flag)
        {
            buff.beg = book + iter + 1;
        }
        iter+=iter_step;
        if (buff.hash_len > 0){ //* add only line with more than 0 letters
            pushBack(lines_ptrs_arr, &buff);
        }
    }
}