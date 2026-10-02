#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include "malloc.h"

#define CAFEDUDE 3405697037
#define DABBADOO 3669732608
#define MALLOC_END_BIRDIE_PTR(ptr, capa) (ptr + capa  * sizeof(stack_elem_t) + 8)

#if STACK_DEBUG == 1
    #define createStack(name, capacity, dump) stack_t name = _createStack(capacity, #name, __FILE__, __LINE__, dump)
    #define resizeStack(stack, new_size) _resizeStack(stack, new_size, __FILE__, __LINE__)
    #define pushBack(stack_ptr, val) _pushBack(stack_ptr, val, __FILE__, __LINE__)
    #define popBack(stack_ptr) _popBack(stack_ptr, __FILE__, __LINE__)
    #define destroyStack(stack_ptr) _destroyStack(stack_ptr, __FILE__, __LINE__)
    #define stkdump(dump, ...) fprintf(dump, __VA_ARGS__)
#else
    #define createStack(name, size) stack_t name = _createStack(size)
    #define resizeStack(stack, new_size) _resizeStack(stack, new_size)
    #define pushBack(stack_ptr, val) _pushBack(stack_ptr, val)
    #define popBack(stack_ptr) _popBack(stack_ptr)
    #define destroyStack(stack_ptr) _destroyStack(stack_ptr)
    #define stkdump(dump, ...)  
#endif

#if STACK_CANARY == 1
    #define BIRDIE_OFFSET  16
#else
    #define BIRDIE_OFFSET 0
#endif

#if STACK_HASH == 1
    #define hashStack(...) _hashStack(__VA_ARGS__)
#else
    #define hashStack(...)  
#endif

#if STACK_TYPE == STACK_INT
    #define STACK_POISON (stack_elem_t)(102)
    #define STACK_PRINT "%d"
    typedef int stack_elem_t;
#elif STACK_TYPE == STACK_CHAR
    #define STACK_POISON (stack_elem_t)('\0')
    #define STACK_PRINT "%c"
    typedef char stack_elem_t;
#elif STACK_TYPE == STACK_DOUBLE
    #define STACK_POISON nan  
    #define STACK_PRINT "%lg"
    typedef double stack_elem_t;
#else
    #define STACK_POISON NULL
    #define STACK_PRINT "%p"
    typedef char* stack_elem_t;
#endif
    
enum error_type{
    STACKOK = 0,
    MEMORY_ERROR = 1,
    STACK_UNDERFLOW = 2,
    STACK_PTR_ERROR = 3,
    INC_CORECRT_LEN = 4,
    BIRDIE_ERROR = 5,
    HASH_MISMATCH = 6
};

struct stack_info{
    const char *name;
    const char *file;
    int line;
    FILE *dump_file;
};

struct stack_t
{   
    #if STACK_CANARY == 1
        uint32_t birdie_beg;
    #endif
    char *ptr;
    stack_elem_t *data;
    size_t capacity;
    size_t len;
    char error;
    #if STACK_DEBUG == 1
        stack_info info;
    #endif
    #if STACK_HASH == 1
        uint32_t stk_hash;
        uint32_t data_hash;
    #endif
    #if STACK_CANARY == 1
        uint32_t birdie_end;
    #endif
};

static void _hashStack(stack_t *stack){
    stack->stk_hash = 0;
    stack->data_hash = 0;
    uint32_t hash = 5381;
    for (unsigned i = 0; i < sizeof(stack); i++){
        hash = ((hash << 5) + hash) + ((char*)stack)[i]; 
    }
    stack->stk_hash = hash;

    hash = 5381;
    for (unsigned i = 0; i < stack->len; i++){
        hash = ((hash << 5) + hash) + ((char*)stack->data)[i]; 
    }
    stack->data_hash = hash;
}

stack_t _createStack(size_t size
    #ifdef STACK_DEBUG
        , const char *name, const char *file, int line, FILE *dump_file
    #endif
){
    stack_t output_stack = {};
    size_t max_pow = 0;
    for (size_t i = 0; i < 8 * sizeof(size_t); i++){
        if ((1 << i & size) != 0){
            max_pow = i;
        }
    }
    size_t start_capacity = 1 << (max_pow + 1);
    output_stack.ptr = (char*)malloc(start_capacity * sizeof(stack_elem_t) + BIRDIE_OFFSET);
    if (output_stack.ptr == NULL){
        output_stack.error |= 1 << MEMORY_ERROR;
        return output_stack;
    }
    output_stack.data = (stack_elem_t*)(output_stack.ptr + BIRDIE_OFFSET/2);
    
    output_stack.len = 0;
    output_stack.capacity = start_capacity;
    
    #if STACK_CANARY == 1
        output_stack.birdie_beg = CAFEDUDE;
        output_stack.birdie_end = CAFEDUDE;
        *(uint32_t*)output_stack.ptr = DABBADOO;
        *(uint32_t*)MALLOC_END_BIRDIE_PTR(output_stack.ptr, output_stack.capacity) = DABBADOO;
    #endif
        
    for (size_t i = 0; i < start_capacity; i++){
        output_stack.data[i] = STACK_POISON;
    }
    #ifdef STACK_DEBUG
        output_stack.info.name = name;
        output_stack.info.file = file;
        output_stack.info.line = line;
        output_stack.info.dump_file = dump_file;
    #endif
    hashStack(&output_stack);
    return output_stack;
}


char checkStack(stack_t *stack){
    if (stack->ptr == NULL){
        stack->error |= 1 << MEMORY_ERROR;
        return stack->error;
    }
    #if STACK_CANARY == 1
        if (stack->birdie_beg != CAFEDUDE || stack->birdie_end != CAFEDUDE || 
            *(uint32_t*)stack->ptr != DABBADOO || *(uint32_t*)MALLOC_END_BIRDIE_PTR(stack->ptr, stack->capacity) != DABBADOO){
            stack->error |= 1 << BIRDIE_ERROR;
        }
    #endif
    uint32_t tmp_data_hash = stack->data_hash, tmp_stk_hash = stack->stk_hash;
    hashStack(stack);
    if (tmp_data_hash != stack->data_hash || tmp_stk_hash != stack->stk_hash){
        stack->error |= 1 << HASH_MISMATCH;
    }
    if (stack->capacity <= stack->len){
        stack->error |= 1 << INC_CORECRT_LEN;
    }

    stack->error |= 1 << STACK_PTR_ERROR;
    _HEAPINFO heap_info;
    heap_info._pentry = NULL;
    while(_heapwalk(&heap_info) == _HEAPOK){
        if (heap_info._useflag == _USEDENTRY && (void*)heap_info._pentry ==  (void*)stack->ptr){
            stack->error ^= 1 << STACK_PTR_ERROR;
            break;
        }
    }
    return stack->error;
}

char _resizeStack(stack_t *stack, size_t new_size
    #ifdef STACK_DEBUG
        , const char *file, int line
    #endif
){
    checkStack(stack);
    if (stack->error != STACKOK){
        stkdump(stack->info.dump_file, "\tResize from %llu to %llu %s in %s at %d break with ERROR(%d)\t", stack->capacity, new_size, stack->info.name, file, line, stack->error);
        return stack->error;
    }
    stkdump(stack->info.dump_file, "\tResize from %llu to %llu %s in %s at %d ", stack->capacity, new_size, stack->info.name, file, line);
    
    stack_elem_t *buff = (stack_elem_t*)realloc(stack->ptr, new_size);
    if (buff == NULL){
        stack->error |= 1 << MEMORY_ERROR;
        return stack->error;
    }
    stack->ptr = buff;
    stack->capacity = new_size;

    #if STACK_CANARY == 1
        *(uint32_t*)stack->ptr = DABBADOO;
        *(uint32_t*)MALLOC_END_BIRDIE_PTR(stack->ptr, stack->capacity) = DABBADOO;
    #endif
    hashStack(stack);
    checkStack(stack);
    stkdump(stack->info.dump_file, "Cmpl\t");
    return stack->error;
} 

char _pushBack(stack_t *stack, stack_elem_t val
    #ifdef STACK_DEBUG
        , const char *file, int line
    #endif
){
    checkStack(stack);
    if (stack->error != STACKOK){
        stkdump(stack->info.dump_file, "Push back " STACK_PRINT " in %s %s at %d break with ERROR(%d)\n", val, stack->info.name, file, line, stack->error);
        return stack->error;
    }
    stkdump(stack->info.dump_file, "Push back " STACK_PRINT " in %s %s at %d", val, stack->info.name, file, line);

    stack->data[stack->len++] = val;
    if (stack->len + 1 == stack->capacity){
       resizeStack(stack, stack->capacity * 2);
    }
    hashStack(stack);
    stkdump(stack->info.dump_file, " Cmpl\n");
    return stack->error;
}

stack_elem_t _popBack(stack_t *stack
    #ifdef STACK_DEBUG
        , const char *file, int line
    #endif
){
    checkStack(stack);
    if (stack->error != STACKOK){
        stkdump(stack->info.dump_file, "Pop back %s in %s at %d break with ERROR(%d)\n", stack->info.name, file, line, stack->error);
        return stack->error;
    }
    stkdump(stack->info.dump_file, "Pop back %s in %s at %d ", stack->info.name, file, line);
    if (stack->len == 0){
        stack->error |= 1 << STACK_UNDERFLOW;
        stkdump(stack->info.dump_file, "stack underflow\n");
        return 0;
    }
    stack_elem_t output = stack->data[--stack->len];
    if (output == STACK_POISON){
        printf("WARN: You maybe address to worn index in stack.");
    }
    stack->data[stack->len + 1] = STACK_POISON;

    hashStack(stack);
    if (stack->capacity / 4 > stack->len){
        resizeStack(stack, stack->capacity / 2);
    }
    stkdump(stack->info.dump_file, "Pop val: " STACK_PRINT " Cmpl\n", output);
    return output;
}

char _destroyStack(stack_t *stack
    #ifdef STACK_DEBUG
        , const char *file, int line
    #endif
){
    checkStack(stack);
    if (stack->error != STACKOK){
        stkdump(stack->info.dump_file, "Destroy %s in %s at %d break with ERROR(%d)\n", stack->info.name, file, line, stack->error);
        return stack->error;
    }
    stkdump(stack->info.dump_file, "Destroy %s in %s at %d ", stack->info.name, file, line);
    for (size_t i = 0; i < stack->capacity; i++){
        stack->data[i] = STACK_POISON;
    }
    free(stack->ptr);
    stkdump(stack->info.dump_file, "Cmpl\n");
    return stack->error;
}

void printStack(stack_t *stack){
    #ifdef STACK_DEBUG
        printf("Stack %s created in %s %d {\n", stack->info.name, stack->info.file, stack->info.line);  
    #endif
    printf("\tLen = %d, Capacity = %d, ERROR CODE(%d)\n", stack->len, stack->capacity, stack->error);
    if(stack->error == STACKOK){
    printf("\tdata\n\t{\n");
        for (unsigned i = 0; i < stack->len; i++){
            printf("\t" STACK_PRINT ",\n", stack->data[i]);
        }
        printf("\t}\n");
    }
    #ifdef STACK_DEBUG
         printf("}\n");
    #endif   
}

void printStackError(char error_code){
    if (error_code == 0){
        printf("Stack totaly fine\n");
    }
    for (int i = 0; i < 8; i++){
        if (((1<<i) & error_code) != 0){
            switch (i)
            {
            case MEMORY_ERROR:
                printf("");
                break;
            case STACK_UNDERFLOW:
                printf("Stack underflow\n");
                break;
            case STACK_PTR_ERROR:
                printf("Wrong pointer was given\n");
                break;
            case INC_CORECRT_LEN:
                printf("Wrong difference between len and capacity, detected external influence.\n");
                break;
            case BIRDIE_ERROR:
                printf("Stack canary missed, detected external influence.\n");
                break;
            case HASH_MISMATCH:
                printf("Stack hash mismatch, detected external influence.\n");
                break;
            default:
                break;
            }
        }
    }
}