#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

#define STACK_INT    1
#define STACK_CHAR   2
#define STACK_DOUBLE 3
#define STACK_PTR    4

#define STACK_TYPE STACK_CHAR
#define STACK_DEBUG 1
#define STACK_CANARY 1
#define STACK_HASH 1

#include "stack.h"



int main(){
    FILE *dump = fopen("dump.txt", "w");
    createStack(myStack, 10, dump);
    checkStack(&myStack);
    pushBack(&myStack, '1');
    pushBack(&myStack, '2');
    pushBack(&myStack, '3');
    popBack(&myStack);
    popBack(&myStack);
    popBack(&myStack);
    popBack(&myStack);

    printStack(&myStack);
    printStackError(myStack.error);
    destroyStack(&myStack);
    fclose(dump);
    return 0;
}