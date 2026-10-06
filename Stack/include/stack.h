#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include "malloc.h"

#define CAFEDUDE 0xCAFED00D
#define DABBADOO 0xDABBAD00

#if STACK_DEBUG == 1
#define createStack(name, capacity) stack_t name = {}; _createStack(&name, capacity, #name, __FILE__, __LINE__)
#define resizeStack(stack, new_size) _resizeStack(stack, new_size, __FILE__, __LINE__)
#define pushBack(stack_ptr, val) _pushBack(stack_ptr, val, __FILE__, __LINE__)
#define popBack(stack_ptr) _popBack(stack_ptr, __FILE__, __LINE__)
#define destroyStack(stack_ptr) _destroyStack(stack_ptr, __FILE__, __LINE__)
#define stkdump(dump, ...) if(dump != NULL) fprintf(dump, __VA_ARGS__)
#define checkStack(...) _checkStack( __VA_ARGS__)
#else
#define createStack(name, size) stack_t name = _createStack(size)
#define resizeStack(stack, new_size) _resizeStack(stack, new_size)
#define pushBack(stack_ptr, val) _pushBack(stack_ptr, val)
#define popBack(stack_ptr) _popBack(stack_ptr)
#define destroyStack(stack_ptr) _destroyStack(stack_ptr)
#define stkdump(dump, ...)  
#define checkStack(...)  
#endif

#if STACK_CANARY == 1
    #define BIRDIE_BYTES  16   
#else
    #define BIRDIE_BYTES 0
#endif
#define BIRDIE_OFFSET (BIRDIE_BYTES / 2)
#define MALLOC_END_BIRDIE_PTR(ptr, capacity) (ptr + capacity  * sizeof(stack_elem_t) + BIRDIE_OFFSET)

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

#define setError(errmask, err) errmask |= (1 << err);
#define resetError(errmask, err) errmask ^= (1 << err);
#define isError(errmask, err) ((errmask & (1 << err)) != 0)
    
enum error_type{
    STACKOK,
    MEMORY_ERROR,
    STACK_UNDERFLOW,
    STACK_PTR_ERROR,
    INC_CORECRT_LEN,
    BIRDIE_ERROR,
    HASH_MISMATCH,
    DUMP_ERROR
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

char _createStack(stack_t *stack, size_t size
    #ifdef STACK_DEBUG
        , const char *name, const char *file, int line
    #endif
    ){
    size_t start_capacity = 1;
    while (start_capacity < size){
        start_capacity<<=1;
    }

    stack->ptr = (char*)malloc(start_capacity * sizeof(stack_elem_t) + BIRDIE_BYTES);
    if (stack->ptr == NULL){
        stack->error |= 1 << MEMORY_ERROR;
        return stack->error;
    }
    stack->data = (stack_elem_t*)(stack->ptr + BIRDIE_OFFSET);
    
    stack->len = 0;
    stack->capacity = start_capacity;
    
    #if STACK_CANARY == 1
        stack->birdie_beg = CAFEDUDE;
        stack->birdie_end = CAFEDUDE;
        *(uint32_t*)stack->ptr = DABBADOO;
        *(uint32_t*)MALLOC_END_BIRDIE_PTR(stack->ptr, stack->capacity) = DABBADOO;
    #endif
        
    for (size_t i = 0; i < start_capacity; i++){
        stack->data[i] = STACK_POISON;
    }
    #ifdef STACK_DEBUG
        stack->info.name = name;
        stack->info.file = file;
        stack->info.line = line;
        FILE *dump_file = fopen(DUMP_DIR, "w");
        if (dump_file != NULL){
            stack->info.dump_file = dump_file;
        }else{
            setError(stack->error, DUMP_ERROR);
        }
    #endif
    hashStack(stack);
    return stack->error;
}


char isDinMem(stack_t *stack){
    setError(stack->error, STACK_PTR_ERROR);
    _HEAPINFO heap_info;
    heap_info._pentry = NULL;
    while(_heapwalk(&heap_info) == _HEAPOK){
        if (heap_info._useflag == _USEDENTRY && (void*)heap_info._pentry ==  (void*)stack->ptr){
            resetError(stack->error, STACK_PTR_ERROR);
            break;
        }
    }
    if (!isError(stack->error, STACK_PTR_ERROR)){
        if (_msize(stack->ptr) != (stack->capacity + BIRDIE_BYTES)){
            setError(stack->error, STACK_PTR_ERROR);
        }
    }
    return stack->error;
}

char _checkStack(stack_t *stack){
    if (stack->ptr == NULL){
        setError(stack->error, MEMORY_ERROR);
        return stack->error;
    }
    if (stack->capacity <= stack->len){
        setError(stack->error, INC_CORECRT_LEN);
    }

    isDinMem(stack);
    #if STACK_CANARY == 1
        if (stack->birdie_beg != CAFEDUDE || stack->birdie_end != CAFEDUDE || 
            *(uint32_t*)stack->ptr != DABBADOO || *(uint32_t*)MALLOC_END_BIRDIE_PTR(stack->ptr, stack->capacity) != DABBADOO){
            setError(stack->error, BIRDIE_ERROR);
        }
    #endif
    uint32_t tmp_data_hash = stack->data_hash, tmp_stk_hash = stack->stk_hash;
    hashStack(stack);
    if (tmp_data_hash != stack->data_hash || tmp_stk_hash != stack->stk_hash){
        setError(stack->error, HASH_MISMATCH);
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
    
    stack_elem_t *buff = (stack_elem_t*)realloc(stack->ptr, new_size + BIRDIE_BYTES);
    if (buff == NULL){
        setError(stack->error, MEMORY_ERROR);
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
        setError(stack->error, STACK_UNDERFLOW);
        stkdump(stack->info.dump_file, " ERROR: stack underflow\n");
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
    if (isError(stack->error, STACK_PTR_ERROR)){
        stkdump(stack->info.dump_file, "Destroy %s in %s at %d break with ERROR(%d)\n", stack->info.name, file, line, stack->error);
        return stack->error;
    }
    stkdump(stack->info.dump_file, "Destroy %s in %s at %d ", stack->info.name, file, line);
    for (size_t i = 0; i < stack->capacity; i++){
        stack->data[i] = STACK_POISON;
    }
    free(stack->ptr);
    stkdump(stack->info.dump_file, "Cmpl\n");
    if (!isError(stack->error, DUMP_ERROR)){
        fclose(stack->info.dump_file);
    }
    return stack->error;
}

void dumpStack(stack_t *stack){
    #ifdef STACK_DEBUG
        stkdump(stack->info.dump_file, "Stack %s created in %s:%d {\n", stack->info.name, stack->info.file, stack->info.line);  
    #endif
    stkdump(stack->info.dump_file, "\tLen - %d\tCapacity - %d, ERROR CODE(%d)\n", stack->len, stack->capacity, stack->error);
    if(stack->error == STACKOK){
    stkdump(stack->info.dump_file, "\tdata\n\t{\n");
        for (unsigned i = 0; i < stack->len; i++){
            stkdump(stack->info.dump_file, "\t[%d] <" STACK_PRINT ">,\n", i, stack->data[i]);
        }
        stkdump(stack->info.dump_file, "\t}\n");
    }
    #ifdef STACK_DEBUG
         stkdump(stack->info.dump_file, "}\n");
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
                printf("Memory error: NULL srtuct or can not realoc data");
                break;
            case STACK_UNDERFLOW:
                printf("Stack underflow\n");
                break;
            case STACK_PTR_ERROR:
                printf("Wrong pointer on data was given\n");
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