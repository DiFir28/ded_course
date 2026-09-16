#ifndef __MY_SORTS__
#define __MY_SORTS__

#include <stdio.h>

void swap(void *first, void *second, size_t byte_count);
void bableSort(void *arr, size_t elem_size, size_t len, int (*compare)(void*, void*));
int quickSort(void *arr, size_t elem_size, size_t len, int (*compare)(void*, void*));

#endif