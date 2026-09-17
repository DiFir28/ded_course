#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "strings.hpp"

#define createVector(len, element_type) createVectorSys(len, sizeof(element_type));

struct mVector{
    void *beg;
    size_t element_size;
    unsigned len;
    unsigned max_len;
};

mVector createVectorSys(unsigned len, size_t element_size){
    mVector out = {};
    out.len = len;
    (len == 0)? len++:len;
    out.max_len = pow(2, 2 + log2(len));
    out.element_size = element_size;
    out.beg = malloc(out.max_len * element_size);
    return out;
}

int pushBack(mVector *vec, void *val){
    if (vec->len + 1 > vec->max_len){
        vec->max_len = pow(2, 2 + log2(vec->len));
        vec->beg = realloc(vec->beg, vec->max_len * vec->element_size);
    }
    memCpy((char*)vec->beg + (vec->len) * vec->element_size, val, vec->element_size);
    vec->len++;
    return (vec->len - 1);
}

// !void popBeg(mVector *vec){
//     vec->beg += vec->element_size;
//     vec->len--;
// }

void writeElement(mVector *vec, unsigned ind, void *val){
    if (ind >= vec->max_len){
        printf("WARN");
        return;
    }
    memCpy((char*)vec->beg + ind * vec->element_size, val, vec->element_size);
}

void getElement(mVector *vec, unsigned ind, void *des){
    memCpy((char*)des, (char*)vec->beg + ind * vec->element_size, vec->element_size);
}

void swap(mVector *vec, unsigned ind1, unsigned ind2){
    void *buff = malloc(vec->element_size);
    getElement(vec, ind1, buff);
    writeElement(vec, ind1, (char*)vec->beg + ind2 * vec->element_size);
    writeElement(vec, ind2, buff);
    free(buff);
}

void indexRemove(mVector *vec, unsigned ind){
    for(unsigned i = ind; i < vec->len; i++){
        swap(vec, i, i + 1);
    }
    vec->len-=1;
}

// int main(){
//     mVector v = createVector(1, char);
//     char a = 'Y';
//     // memcpy((v.beg + 1), &a, v.element_size);
//     printf("Max len %d\n", (v.len));

//     writeElement(&v, 0, &a);
//     a = 'E';
//     pushBack(&v, &a);
//     a = 'U';
//     pushBack(&v, &a);
//     pushBack(&v, &a);
//     swap(&v, 1, 2);
//     printVec(&v);
// }