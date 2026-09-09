#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int quickSort(int *arr, size_t len);

int quickSort(int *arr, size_t len){
    if (len <= 1){
        return 0;
    }
    unsigned pivot_ind = len - 1;
    int pivot = arr[pivot_ind];

    unsigned left_len = 0;
    unsigned right_len = 0;

    for (int i = 0; i < len; i++){
        if (arr[i] <= pivot){
            int temp = arr[left_len];
            arr[left_len++] = arr[i];
            arr[i] = temp;
        }
    }

    int temp = arr[left_len];
    arr[left_len] = arr[len - 1];
    arr[len - 1] = temp;
    quickSort(arr, left_len);
    quickSort(arr + left_len + 1, len - 1 - left_len); 
    return 0;
}