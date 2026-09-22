#include "utils.h"
#include <ctype.h>

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