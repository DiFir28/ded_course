#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

#define DUMP_DIR "dump.txt"

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
    createStack(myStack, 10);
    checkStack(&myStack);
    pushBack(&myStack, 'a');
    pushBack(&myStack, 'b');
    pushBack(&myStack, 'c');

    dumpStack(&myStack);
    printStackError(myStack.error);
    destroyStack(&myStack);
    return 0;
}