#include "strings.hpp"
#include <stdio.h>
#include <math.h>

void swap(void * first, void * second, size_t byte_count){
    char *first_ptr = (char *)first;
    char *second_ptr = (char *)second;
    char temp = '\0'; 
    // printf("Input : %d %d\n",*(int*)first, *(int*)second);
    for (unsigned i = 0; i < byte_count; i++){
        // printf("Before %d %d", *first_ptr, *second_ptr);
        temp = *(first_ptr + i);
        *(first_ptr + i) = *(second_ptr + i);
        *(second_ptr + i) = temp;
        // printf("after %d %d\n", *first_ptr, *second_ptr);  
    }
}

void bableSort(void *arr, size_t elem_size, size_t len, int (*compare)(void*, void*)){
    char *arr_ptr = (char*)arr;
    for (unsigned i = 0; i < len - 1; i++){
        for (unsigned j = 0, end_j = len - i - 1; j < end_j; j++){
            if (compare(arr_ptr + elem_size * j, arr_ptr + elem_size * (j + 1)) < 0){
                swap(arr_ptr + elem_size * j, arr_ptr + elem_size * (j + 1), elem_size);
            }
        }
    }
}

int quickSort(void *arr, size_t elem_size, size_t len, int (*compare)(void*, void*)){
    if (len <= 1){
        return 0;
    }
    char *arr_ptr = (char*)arr;
    unsigned pivot_ind = len/2;
    char* pivot = (char *)calloc(1, elem_size);
    memCpy(pivot, arr_ptr + (len / 2) * elem_size, elem_size);
    
    unsigned left_len = 0;
    unsigned right_len = len;

    while(left_len < right_len){
        // printf("left ptr on: %d pivot: %d\n", *(int*)(arr + left_len * elem_size), *(int*)pivot);
        if (compare(arr_ptr + left_len * elem_size, pivot) >= 0){
            do{ 
            right_len--;
            }while ((compare(arr_ptr + right_len * elem_size, pivot) > 0) && right_len > left_len);
            if (right_len == left_len){
                break;
            }
            // printf("Need to swap: %d %d %d\n", left_len, right_len, *pivot);
            swap(arr_ptr + left_len * elem_size, arr_ptr + right_len * elem_size, elem_size);           
            // printf("Right");
        }else{
            left_len++;
            // printf("Left");
        }
        // printf("%d %d\n", left_len, right_len);
    }
    // for (int i = 0; i < 6; i++){
    //     printf("%d\t", *(int*)(arr_ptr + i*elem_size));
    // }
    // printf("\n");
    // printf("END %d %d pivot = %d last elem = %d\n", len, left_len, *(int*)pivot, *(int*)(arr_ptr + (len - 1) * elem_size));
    // getchar();
    quickSort(arr_ptr, elem_size, left_len, compare);
    // printf("!!!\n");
    quickSort(arr_ptr + left_len * elem_size + elem_size, elem_size, len - 1 - left_len, compare); 
    return 0;
}

int quickSort(int *arr, size_t len){
    if (len <= 1){
        return 0;
    }
    unsigned pivot_ind = len/2;
    int pivot = arr[pivot_ind];

    unsigned left_len = 0;
    unsigned right_len = len;

    while(left_len < right_len){
        if (arr[left_len] >= pivot){
            do{ 
            right_len--;
            }while (arr[right_len] > pivot && right_len > left_len);
            if (right_len == left_len){
                break;
            }
            printf("Need to swap: %d %d\n", left_len, right_len);
            swap(arr + left_len, arr + right_len, sizeof(arr[0]));           
            // printf("Right");
        }else{
            left_len++;
        // printf("Left");
        }
        // printf("%d %d\n", left_len, right_len);
    }
    quickSort(arr, left_len);
    quickSort(arr + left_len + 1, len - 1 - left_len); 
    return 0;
}
