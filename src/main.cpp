#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "strings.hpp"
#include "sorts.hpp"
#include "din_arr.h"
#include "triangarr.cpp"
#include "file_handler.h"
#include "Onegin.h"

#define BEAUTY_QUICK_SORT_SHOW 0

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

    clock_t start_time = clock();
    mVector lines_ptrs = createVector(0, char**);
    mVector reverse_lines_ptrs = createVector(0, char**);
    for (int i = 0; i < letters_read + 3; i++){
        if (bookText[i] == '\n' && bookText[i + 1] != '\n'){
            char* buff = bookText + i + 1;
            // printf("%c<\n", *buff);
            pushBack(&lines_ptrs, &buff);
            pushBack(&reverse_lines_ptrs, &buff);
        }
    }
    qsort(lines_ptrs.beg, lines_ptrs.len - 1, lines_ptrs.element_size, ptrs_cmp);
    quickSort(reverse_lines_ptrs.beg, reverse_lines_ptrs.len - 1, reverse_lines_ptrs.element_size, reverse_ptrs_cmp);

    clock_t end_time = clock();

    writeOutputLine("OutputLine.txt", &lines_ptrs, &reverse_lines_ptrs, bookText);

    printf("Ptr time: %llu\n", end_time - start_time);

    start_time = clock();
    mVector hash_ptrs = createVector(0, Hash_ptr);
    mVector reverse_hash_ptrs = createVector(0, Hash_ptr);
  
    calcHash(&hash_ptrs, bookText, 1, letters_read, false);    
    calcHash(&reverse_hash_ptrs, bookText, letters_read, letters_read + 1, true);
    
    quickSort(hash_ptrs.beg, hash_ptrs.len, hash_ptrs.element_size, hash_cmp);
    qsort(reverse_hash_ptrs.beg, reverse_hash_ptrs.len, hash_ptrs.element_size, hash_cmp);
    end_time = clock();
    printf("Hash time: %llu\n", end_time - start_time);

    writeOutputHash("OutputHash.txt", &hash_ptrs, &reverse_hash_ptrs, bookText);
    free(bookText);
    destructVector(&hash_ptrs);
    destructVector(&reverse_hash_ptrs);
    printf("Finish");
}

