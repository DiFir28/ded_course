#include "sorts.hpp"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "strings.hpp"
#include "utils.h"

void bubbleSort(void *arr, size_t elem_size, size_t len, int (*compare)(const void*, const void*)){
    assert(arr != NULL);
    assert(compare != NULL);
    char *arr_ptr = (char*)arr;
    for (unsigned i = 0; i < len - 1; i++){
        for (unsigned j = 0, end_j = len - i - 1; j < end_j; j++){
            if (compare(arr_ptr + elem_size * j, arr_ptr + elem_size * (j + 1)) < 0){
                swap(arr_ptr + elem_size * j, arr_ptr + elem_size * (j + 1), elem_size);
            }
        }
    }
}

int quickSort(void *arr, size_t len, size_t elem_size, int (*compare)(const void*, const void*)){
    assert(arr != NULL);
    assert(compare != NULL);

    if (len <= 1){
        return 0;
    }
    char *arr_ptr = (char*)arr;
    unsigned pivot_ind = len/2;
    char* pivot = (char *)calloc(1, elem_size);
    memCpy(pivot, arr_ptr + (pivot_ind) * elem_size, elem_size);
    
    unsigned left_len = 0;
    unsigned right_len = len;

    while(left_len < right_len){
        if (compare(arr_ptr + left_len * elem_size, pivot) >= 0){
            do{ 
            right_len--;
            }while ((compare(arr_ptr + right_len * elem_size, pivot) > 0) && right_len > left_len);
            if (right_len == left_len){
                break;
            }
            swap(arr_ptr + left_len * elem_size, arr_ptr + right_len * elem_size, elem_size);           
        }else{
            left_len++;
        }
    }
    quickSort(arr_ptr, left_len, elem_size, compare);
    quickSort(arr_ptr + left_len * elem_size + elem_size, len - 1 - left_len, elem_size, compare); 
    free(pivot);
    return 0;
}

int quickSortInt(int *arr, size_t len, int lvl, int *base, int base_len){
    assert(arr != NULL);
    if (len <= 1){
        return 0;
    }
    unsigned pivot_ind = len/2;
    int pivot = arr[pivot_ind];
    for(int l = 0; l < lvl; l++){
            printf("\033[32m--------");
        }
    printf("\033[32mPivot: %d\tLen: %d\n\033", pivot, len);

    unsigned left_len = 0;
    unsigned right_len = len;

    while(left_len < right_len){
        for(int l = 0; l < lvl; l++){
            printf("\033[90m%d\t\033[0m", base[l]);
        }
        for (int i = 0; i < len; i ++) {
            if (i < left_len){
                printf("\033[34m%d\t\033[0m", arr[i]);
                continue;
            }
            if (i == left_len){
                printf("\033[34m%d\t\033[0m", arr[i]);
                continue;
            }
            if (i < right_len){
                printf("%d\t", arr[i]);
                continue;
            }
            if (i == right_len){
                printf("\033[31m%d\t\033[0m", arr[i]);
                continue;
            }
            if (i > right_len){
                printf("\033[31m%d\t\033[0m", arr[i]);
                continue;
            }
        }
        for(int l = len + lvl; l < base_len; l++){
            printf("\033[90m%d\t\033[0m", base[l]);
        }
        printf("\t Left: %d Right: %d\n", left_len, right_len);
        for(int l = 0; l < lvl; l++){
            printf("\t");
        }
        for (int i = 0; i < len; i ++) {
            if (i < left_len){
                printf("\033[34m%d\t\033[0m", i);
                continue;
            }
            if (i == left_len){
                printf("\033[34m%d(L)\t\033[0m", i);
                continue;
            }
            if (i < right_len){
                printf("%d\t", i);
                continue;
            }
            if (i == right_len){
                printf("\033[31m%d(R)\t\033[0m", i);
                continue;
            }
            if (i > right_len){
                printf("\033[31m%d\t\033[0m", i);
                continue;
            }
        }
        printf("\n");

        if (arr[left_len] >= pivot){
            do{ 
            right_len--;
            }while (arr[right_len] > pivot && right_len > left_len);
            if (right_len == left_len){
                break;
            }
            for(int l = 0; l < lvl; l++){
                printf("\t");
            }
            printf("\033[33mSwap: %d %d\n\033[0m", left_len, right_len);
            swap(arr + left_len, arr + right_len, sizeof(arr[0]));
        }else{
            left_len++;
        }
    }
    quickSortInt(arr, left_len, (arr - base), base, base_len);
    quickSortInt(arr + left_len + 1, len - 1 - left_len, arr + left_len + 1 - base, base, base_len); 
    return 0;
}