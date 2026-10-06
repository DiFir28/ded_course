#ifndef __DIN_ARR__
#define __DIN_ARR__
#include <ctype.h>

#define createVector(len, element_type) createVectorSys(len, sizeof(element_type));

struct mVector{
    void *beg;
    size_t element_size;
    unsigned len;
    unsigned max_len;
};

mVector createVectorSys(unsigned len, size_t element_size);
int pushBack(mVector *vec, void *val);
void writeElement(mVector *vec, unsigned ind, void *val);
void getElement(mVector *vec, unsigned ind, void *des);
void *getElementPtr(mVector *vec, unsigned ind);
void swapElement(mVector *vec, unsigned ind1, unsigned ind2);
void indexRemove(mVector *vec, unsigned ind);
void destructVector(mVector *vec);

#endif