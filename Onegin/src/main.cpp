#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "strings.hpp"
#include "sorts.hpp"
#include "din_arr.h"
#include "file_handler.h"
#include "Onegin.h"

#define BEAUTY_QUICK_SORT_SHOW 0

clock_t doLineBookSort(char* bookText, size_t letters_read, bool print_flag){
    clock_t start_time = clock();
    mVector lines_ptrs = createVector(0, Line_ptr);
    mVector reverse_lines_ptrs = createVector(0, Line_ptr);
    caclLines(&lines_ptrs, &reverse_lines_ptrs, bookText, letters_read);   
    quickSort(lines_ptrs.beg, lines_ptrs.len - 1, lines_ptrs.element_size, ptrs_cmp);
    qsort(reverse_lines_ptrs.beg, reverse_lines_ptrs.len - 1, reverse_lines_ptrs.element_size, reverse_ptrs_cmp);
    
    clock_t end_time = clock();
    if (print_flag)    
        printf("Ptr time: \033[33m%llu\n\033[0m", end_time - start_time);
    writeOutputLine("OutputLine.txt", &lines_ptrs, &reverse_lines_ptrs, bookText);
    destructVector(&lines_ptrs);
    destructVector(&reverse_lines_ptrs);
    return (end_time - start_time);
}

clock_t doHashBookSort(char* bookText, size_t letters_read, bool print_flag){
    clock_t start_time = clock();
    mVector hash_ptrs = createVector(0, Hash_ptr);
    mVector reverse_hash_ptrs = createVector(0, Hash_ptr);    
    calcHash(&hash_ptrs, bookText, 1, letters_read, false); 
    calcHash(&reverse_hash_ptrs, bookText, letters_read, letters_read, true);    
    qsort(hash_ptrs.beg, hash_ptrs.len, hash_ptrs.element_size, hash_cmp);
    quickSort(reverse_hash_ptrs.beg, reverse_hash_ptrs.len, hash_ptrs.element_size, hash_cmp);

    clock_t end_time = clock();
    if (print_flag)  
        printf("Hash time: \033[33m%llu\n\033[0m", end_time - start_time);
    writeOutputHash("OutputHash.txt", &hash_ptrs, &reverse_hash_ptrs, bookText);
    destructVector(&hash_ptrs);
    destructVector(&reverse_hash_ptrs);
    return (end_time - start_time);
}


int main(int argc, const char *argv[]){

    #if BEAUTY_QUICK_SORT_SHOW
    int arr[] = {1403, 223, 1000, 654, 8523, 321};
    quickSortInt(arr, 6, 0, arr, 6);
    return 0;
    #endif //BEAUTY_QUICK_SORT_SHOW
    
    size_t letters_read = 0;
    char *bookText = 0;
    if (argc > 2){
        printf("\033[31mWRONG CLI PARAM\n\033[0m");
        return -1;
    }
    if (argc > 1){ 
        bookText = readTextFile(argv[1], &letters_read);
    }else{  
        bookText = readTextFile("Onegin.txt", &letters_read);
    }
    if (bookText == NULL){
        return 1;
    }

    doLineBookSort(bookText, letters_read, true);
    doHashBookSort(bookText, letters_read, true);

    free(bookText);
    printf("\033[32mFinish\n\033[0m");
}

