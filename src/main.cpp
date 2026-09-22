#include <stdio.h>
#include <ctype.h>

// #include <stdlib.h>
#include "strings.hpp"
#include "sorts.hpp"
#include "din_arr.h"
#include "triangarr.cpp"
#include "file_handler.cpp"
#include "str_alpha_encode.h"

void writeHashArrInFile(FILE *file, mVector *hash_arr);

int main(int argc, char *argv[]){
    // int arr[] = {1403, 223, 1000, 654, 8523, 321};
    // quickSortInt(arr, 6, 0, arr, 6);
    // return 0;
    
    size_t letters_read = 0;
    char *bookText = 0;
    if (argc > 1){
        bookText = readTextFile(argv[1], &letters_read);
    }else{  
        bookText = readTextFile("Onegin.txt", &letters_read);
    }
    mVector lines_ptrs = createVector(0, Line_ptr);
    mVector reverse_lines_ptrs = createVector(0, Line_ptr);
  
    calcHash(&lines_ptrs, bookText, 1, 1, letters_read, false);
    calcHash(&reverse_lines_ptrs, bookText, letters_read, - 1, letters_read + 1, true);

    qsort(lines_ptrs.beg, lines_ptrs.len, lines_ptrs.element_size, Line_cmp);
    quickSort(reverse_lines_ptrs.beg, reverse_lines_ptrs.element_size, reverse_lines_ptrs.len, Line_cmp);

    writeOutput("Output.txt", &lines_ptrs, &reverse_lines_ptrs, bookText);
    
    free(bookText);
    free(lines_ptrs.beg);
    free(reverse_lines_ptrs.beg);
    printf("Finish");
}

