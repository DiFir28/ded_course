#include "utils.h"
#include <ctype.h>

void swap(void * first, void * second, size_t byte_count){
    char *first_ptr = (char *)first;
    char *second_ptr = (char *)second;
    char temp = '\0'; 
    for (size_t i = 0; i < byte_count; i++){
        temp = *(first_ptr + i);
        *(first_ptr + i) = *(second_ptr + i);
        *(second_ptr + i) = temp;
    }
}