#include <stdio.h>
#include <unistd.h>

#include "din_arr.h"

#define RESERVED_MEMORY 3

char *readTextFile(const char *file_name, size_t *len);
void writeHashArrInFile(FILE *file, mVector *hash_arr);

void writeOutput(const char *output_name, mVector *hash_arr1,  mVector *hash_arr2, char *mainText);