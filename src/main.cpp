#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
// #include <stdlib.h>
#include "strings.hpp"
#include "sorts.hpp"
#include "din_arr.cpp"
#include "triangarr.cpp"

#define MAX_LETTERS_IN_BOOK 200000
#define HASH_LEN 40
#define sing(num) (num > 0?1:-1)

int comp(void* a, void* b){
    return *(int*)a - *(int*)b;
 }

struct Line_ptr{
    char *beg;
    char hash[HASH_LEN];
};

int Line_ptr_cmp(void* a_ptr, void* b_ptr){
    Line_ptr a = *(Line_ptr*)a_ptr;
    Line_ptr b = *(Line_ptr*)b_ptr;
    unsigned cmp_iter = 0;
    while(uint8_t(a.hash[cmp_iter]) == uint8_t(b.hash[cmp_iter]) && cmp_iter < HASH_LEN - 1){ //! TODO step by 8
        cmp_iter+=1;
    }
    int16_t res = (uint8_t(a.hash[cmp_iter]) - uint8_t(b.hash[cmp_iter]));
    if (res == 0){
        return 0;
    }
    return sing(res);
}

// TODO Line_ptr calcHash(char *beg)

int main(){
    FILE *Onegin_book = fopen("Onegin.txt", "r");
    if (Onegin_book == NULL){
        printf("\033[31mNo book file ಥ_ಥ\n\033[0m");
        return 1;
    }
    char *Onegin = (char*)calloc(MAX_LETTERS_IN_BOOK, sizeof(char));
    if (Onegin == NULL){
        printf("\033[31mNo enought memory available ಥ_ಥ\n\033[0m");
        return 2;
    }
    size_t letters_read = fread(Onegin, sizeof(char), MAX_LETTERS_IN_BOOK, Onegin_book);
    fclose(Onegin_book);
    Onegin = (char*)realloc(Onegin, letters_read + 1);
    mVector lines_ptrs = createVector(0, Line_ptr);
    unsigned long long iter = 0;
    while (iter < letters_read){
        Line_ptr buf = {(Onegin + iter), 0};
        unsigned hash_iter = 0;
        while (iter < letters_read && Onegin[iter] != '\n'){
            if (isalpha(Onegin[iter])){

                buf.hash[(hash_iter / 8)] |= (toupper(Onegin[iter]) & 0x1F) << 3 >> (hash_iter % 8);
                if (hash_iter % 8 > 3){
                    buf.hash[(hash_iter / 8) + 1] |=   (toupper(Onegin[iter]) & 0x1F) << 11 >> (hash_iter % 8);
                }
                hash_iter += 5;
            }
            iter++;
        }
        // for (int i = 0; i < 2; i ++){
        //         for (int j = 7; j >=0; j--){
        //             printf("%d", (buf.hash[i] >> j) & 1);
        //         }
        //     }
        //     printf("\n");
        // printf(" %d \n", hash_iter);
        iter++;
        pushBack(&lines_ptrs, &buf);
    }
    // printf("%d\n", Line_ptr_cmp(lines_ptrs.beg + lines_ptrs.element_size, lines_ptrs.beg + 2 *lines_ptrs.element_size));

    printf("%d\n", lines_ptrs.len);
    quickSort(lines_ptrs.beg, lines_ptrs.element_size, lines_ptrs.len, Line_ptr_cmp);
    for (unsigned print_iter = 0; print_iter < lines_ptrs.len; print_iter++){
        Line_ptr buf = {};
        getElement(&lines_ptrs, print_iter, &buf);
        unsigned i = 0;
        while (buf.beg[i] != '\n' && buf.beg[i] != '\0'){
            printf("%c", buf.beg[i]);
            i++;
        }
        printf("\t");
          for (int i = 0; i < 2; i ++){
                for (int j = 7; j >=0; j--){
                    printf("%d", (buf.hash[i] >> j) & 1);
                }
            }
            printf("\n");
    }
}