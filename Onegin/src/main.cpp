#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "strings.hpp"
#include "sorts.hpp"
#include "din_arr.h"
#include "file_handler.h"
#include "Onegin.h"

unsigned long doLineBookSort(char* bookText, size_t letters_read, bool write_flag, bool print_flag){
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
    return (unsigned long)(end_time - start_time);
}

unsigned long doHashBookSort(char* bookText, size_t letters_read, bool write_flag, bool print_flag){
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
    if (write_flag)
        writeOutputHash("OutputHash.txt", &hash_ptrs, &reverse_hash_ptrs, bookText);
    destructVector(&hash_ptrs);
    destructVector(&reverse_hash_ptrs);
    return (unsigned long)(end_time - start_time);
}

unsigned runBenchMark( unsigned long (*test)(char*, size_t, bool, bool), char* bookText, size_t letters_read, long test_times){
    unsigned long*measurments = (unsigned long*)calloc(test_times, sizeof(unsigned long));
    if (measurments == NULL){
        printf("Too many test\n");
    }
    unsigned long min_time = -1;
    unsigned long max_time = 0;
    unsigned long sum_time = 0;

    for (long i = 0; i < test_times; i++){
        unsigned long cur_time = test(bookText, letters_read, false, false);
        measurments[i] = cur_time;
        sum_time += (cur_time);
        min_time = __min(cur_time, min_time);
        max_time = __max(cur_time, max_time);
    }
    double ave_time = ((double)sum_time)/test_times;
    double sigma = 0;
    for (long i = 0; i < test_times; i++){
        double longdelta = (measurments[i] > ave_time) ? ((double)measurments[i] - ave_time):((double)ave_time - measurments[i]);
        sigma += (pow(longdelta,2) / (test_times - 1));
    }
    double deviation = sigma / sqrt(test_times);
    printf("By \033[32m%d\033[0m measure:\n  Min time: %d Max time: %d\n  Average time: \033[33m%lg\n\033[0m  deviation: %lg\n", test_times, min_time, max_time, ave_time, deviation);
    return ave_time;
}

int main(int argc, const char *argv[]){
    
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

    runBenchMark(doLineBookSort, bookText, letters_read, 1000);
    runBenchMark(doHashBookSort, bookText, letters_read, 1000);

    doLineBookSort(bookText, letters_read, true, false);
    doHashBookSort(bookText, letters_read, true, false);

    free(bookText);
    printf("\033[32mFinish\n\033[0m");
}

