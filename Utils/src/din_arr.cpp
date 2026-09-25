#include "din_arr.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "strings.hpp"
#include "utils.h"

mVector createVectorSys(unsigned len, size_t element_size){
    mVector out = {};
    out.len = len;
    (len == 0)? len++:len;
    out.max_len = 2*len;
    out.element_size = element_size;
    out.beg = malloc(out.max_len * element_size);
    return out;
}

int pushBack(mVector *vec, void *val){
    if (vec->len + 1 > vec->max_len){
        vec->max_len = 2 * vec->len;
        vec->beg = realloc(vec->beg, vec->max_len * vec->element_size);
    }
    memCpy((char*)vec->beg + (vec->len) * vec->element_size, val, vec->element_size);
    return (vec->len++);
}

void writeElement(mVector *vec, unsigned ind, void *val){
    if (ind >= vec->max_len){
        printf("\033[33mElement index out off range\n\033[0m");
        return;
    }
    memCpy((char*)vec->beg + ind * vec->element_size, val, vec->element_size);
}

void getElement(mVector *vec, unsigned ind, void *des){
    memCpy((char*)des, (char*)vec->beg + ind * vec->element_size, vec->element_size);
}

void *getElementPtr(mVector *vec, unsigned ind){
    return ((char*)vec->beg + ind * vec->element_size);
}

void swapElement(mVector *vec, unsigned ind1, unsigned ind2){
    swap((char*)vec->beg + vec->element_size * ind1, (char*)vec->beg + vec->element_size * ind2, vec->element_size);
}

void indexRemove(mVector *vec, unsigned ind){
    for(unsigned i = ind; i < vec->len; i++){
        swapElement(vec, i, i + 1);
    }
    vec->len-=1;
}

void destructVector(mVector *vec){
    free(vec->beg);
}