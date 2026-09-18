#include <stdio.h>
#include <ctype.h>

// #include <stdlib.h>
#include "strings.hpp"
#include "sorts.hpp"
#include "din_arr.h"
#include "triangarr.cpp"
#include "str_alpha_encode.h"

int comp(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int main(){
    int arr[] = {1403, 223, 1000, 654, 8523, 321};
    quickSortInt(arr, 6, 0, arr, 6);
    return 0;
    FILE *Onegin_book = fopen("Onegin.txt", "r");
    if (Onegin_book == NULL){
        printf("\033[31mNo book file ಥ_ಥ\n\033[0m");
        return 1;
    }
    char *Onegin = (char*)calloc(MAX_LETTERS_IN_BOOK, sizeof(char));
    *Onegin = '\n';

    if (Onegin == NULL){
        printf("\033[31mNo enought memory available ಥ_ಥ\n\033[0m");
        return 2;
    }

    size_t letters_read = fread(Onegin, sizeof(char), MAX_LETTERS_IN_BOOK, Onegin_book);
    fclose(Onegin_book);
    Onegin = (char*)realloc(Onegin, letters_read + 1);
    mVector lines_ptrs = createVector(0, Line_ptr);
    mVector reverse_lines_ptrs = createVector(0, Line_ptr);
  
    calcHash(&lines_ptrs, Onegin, 1, 1, letters_read, false);
    calcHash(&reverse_lines_ptrs, Onegin, letters_read, - 1, letters_read + 1, true);

    qsort(lines_ptrs.beg, lines_ptrs.len, lines_ptrs.element_size, Line_cmp);
    quickSort(reverse_lines_ptrs.beg, reverse_lines_ptrs.element_size, reverse_lines_ptrs.len, Line_cmp);

    FILE *output = fopen("output.txt", "w");
    if (output == NULL){
        printf("\033[31mNo output available ಥ_ಥ\n\033[0m");
        return 3;
    }

    for (unsigned print_iter = 0; print_iter < lines_ptrs.len; print_iter++){
        Line_ptr buf = {};
        getElement(&lines_ptrs, print_iter, &buf);
        unsigned i = 0;
        while (buf.beg[i] != '\n' && buf.beg[i] != '\0'){
            // printf("%c", buf.beg[i]);
            fputc(buf.beg[i], output);
            i++;
        }
        fputc(buf.beg[i], output);
    }

    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    for (unsigned print_iter = 0; print_iter < lines_ptrs.len; print_iter++){
        Line_ptr buf = {};
        getElement(&reverse_lines_ptrs, print_iter, &buf);
        unsigned i = 0;
        while (buf.beg[i] != '\n' && buf.beg[i] != '\0'){
            // printf("%c", buf.beg[i]);
            fputc(buf.beg[i], output);
            i++;
        }
        fputc(buf.beg[i], output);
    }

    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    fputs((Onegin), output);
    printf("Finish");

    free(Onegin);
    free(lines_ptrs.beg);
}