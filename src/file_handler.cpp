#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "din_arr.h"
#include "str_alpha_encode.h"

char *readTextFile(const char *file_name, size_t *len){
    struct stat info;
    if (stat(file_name, &info) == -1){
        printf("\033[31mFILE ERROR");
        return NULL;
    }
    char *mainText = (char*)calloc(info.st_size + 3, sizeof(char));

    mainText[0] = '\n'; //* Set file start from \n for reverse ptr based sort
    int descr = open(file_name, O_RDONLY);
    ssize_t readed = read(descr, mainText + 1, info.st_size);
    close(descr);
    *len =  readed;
    // printf("File size %d readed: %d\n", info.st_size, readed);
    char* buf = (char*)realloc(mainText, readed + 3);
    if (buf == NULL){
        printf("\033[31mERROR: NO MEMORY FOR FILE DATA");
        return NULL;
    }
    mainText[readed + 1] = '\n'; //* Set file start from \n for direct ptr based sort
    return mainText;
}

void writeHashArrInFile(FILE *file, mVector *hash_arr){
    for (unsigned print_iter = 0; print_iter < hash_arr->len; print_iter++){
        Line_ptr buf = {};
        getElement(hash_arr, print_iter, &buf);
        unsigned i = 0;
        while (buf.beg[i] != '\n' && buf.beg[i] != '\0'){
            // printf("%c", buf.beg[i]);
            fputc(buf.beg[i], file);
            i++;
        }
        fputc(buf.beg[i], file);
    }
}

void writeOutput(const char *ouput_name, mVector *hash_arr,  mVector *hash_arr2, char *mainText){
    FILE *output = fopen("output.txt", "w");
    if (output == NULL){
        printf("\033[31mNo output available\n\033[0m");
        return;
    }
    writeHashArrInFile(output, hash_arr);
    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    writeHashArrInFile(output, hash_arr2);
    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    fputs((mainText), output);
}