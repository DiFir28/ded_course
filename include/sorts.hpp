#ifndef __MY_SORTS__
#define __MY_SORTS__

#include <stdio.h>

void bubbleSort(void *arr, size_t elem_size, size_t len, int (*compare)(const void*, const void*));
int quickSort(void *arr, size_t elem_size, size_t len, int (*compare)(const void*, const void*));
int quickSortInt(int *arr, size_t len, int lvl, int *base, int base_len);

#endif