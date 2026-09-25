#include "file_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

#include "din_arr.h"
#include "Onegin.h"

char *readTextFile(const char *file_name, size_t *len){
    struct stat info;
    if (stat(file_name, &info) == -1){
        int file_error_code = errno;
        printf("\033[31mFILE ERROR with code: %d\n\033[0m", file_error_code);
        return NULL;
    }
    char *mainText = (char*)calloc(info.st_size + RESERVED_MEMORY, sizeof(char));
    if (mainText== NULL){
        printf("\033[31mERROR: NO MEMORY FOR FILE DATA\n\033[0m");
        return NULL;
    }

    mainText[0] = '\n'; //* Set file start from \n for reverse ptr based sort
    int descr = open(file_name, O_RDONLY);
    ssize_t readed = read(descr, mainText + 1, info.st_size);
    close(descr);
    *len =  readed;
    char* buff= (char*)realloc(mainText, readed + 3);
    if (buff== NULL){
        printf("\033[31mERROR: NO MEMORY FOR FILE DATA\n\033[0m");
        return NULL;
    }
    mainText = buff;
    mainText[readed + 1] = '\n'; //* Set file start from \n for direct ptr based sort
    mainText[readed + 2] = '\0';
    return mainText;
}

void writeLineArrInFile(FILE *file, mVector *hash_arr){
    assert(file != NULL);
    assert(hash_arr != NULL);
    for (int i = 0; i < hash_arr->len - 1; i++){
        Line_ptr* prev_buff = (Line_ptr*)(getElementPtr(hash_arr,i));
        int j = 0;
        while ((prev_buff->beg)[j] != '\n'){
            putc((prev_buff->beg)[j], file);
            j++;
        }
        putc((prev_buff->beg)[j], file);
    }
}

void writeHashArrInFile(FILE *file, mVector *hash_arr){
    assert(file != NULL);
    assert(hash_arr != NULL);
    for (unsigned print_iter = 0; print_iter < hash_arr->len; print_iter++){
        Hash_ptr buff= {};
        getElement(hash_arr, print_iter, &buff);
        unsigned i = 0;
        while (buff.beg[i] != '\n' && buff.beg[i] != '\0'){
            fputc(buff.beg[i], file);
            i++;
        }
        fputc(buff.beg[i], file);
    }
}

void writeOutputLine(const char *output_name, mVector *hash_arr1,  mVector *hash_arr2, char *mainText){
    assert(hash_arr1 != NULL);
    assert(hash_arr2 != NULL);
    assert(mainText != NULL);

    FILE *output = fopen(output_name, "w");
    if (output == NULL){
        printf("\033[31mNo output available\n\033[0m");
        return;
    }
    writeLineArrInFile(output, hash_arr1);
    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    writeLineArrInFile(output, hash_arr2);
    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    fputs((mainText), output);
    fclose(output);
}

void writeOutputHash(const char *output_name, mVector *hash_arr1,  mVector *hash_arr2, char *mainText){
    assert(hash_arr1 != NULL);
    assert(hash_arr2 != NULL);
    assert(mainText != NULL);

    FILE *output = fopen(output_name, "w");
    if (output == NULL){
        printf("\033[31mNo output available\n\033[0m");
        return;
    }
    writeHashArrInFile(output, hash_arr1);
    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    writeHashArrInFile(output, hash_arr2);
    fputs("\n//////////////////////////////////////////////////////////\n\n", output);
    fputs((mainText), output);
    fclose(output);
}