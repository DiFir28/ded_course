#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct match_res{
    unsigned comand1;
    unsigned comand2;
};

char *createTriang(unsigned ind_count, size_t unit_size){
    return (char*)calloc((ind_count+1) * ind_count / 2, unit_size);
}

char *getTriangPtr(char *result_table, size_t unit_size, unsigned first_com_ind, unsigned sec_com_ind){//TODO rename
    assert(result_table != NULL);
    return (result_table + unit_size * ((first_com_ind + 1) * (first_com_ind)  / 2 + sec_com_ind));
}

void writeMatchRes(char *result_table, unsigned first_com_ind, unsigned sec_com_ind, match_res res){
    assert(result_table != NULL);
    if (first_com_ind == sec_com_ind || !first_com_ind || !sec_com_ind){
        return;
    }
    if (first_com_ind < sec_com_ind){
        unsigned buf = first_com_ind;
        first_com_ind = sec_com_ind;
        sec_com_ind = buf;
        buf = res.comand1;
        res.comand1 = res.comand2;
        res.comand2 = buf;
    }
    match_res *match = (match_res *)getTriangPtr(result_table, sizeof(match_res), first_com_ind, sec_com_ind);
    *match = res;
}

void printResTriang(char *result_table, unsigned res_len){
    assert(result_table != NULL);
    
    printf("\t");
    for (unsigned i = 0; i < res_len - 1; i++){
        printf("_:%i\t", i);
    }
    printf("\n");
    for (unsigned i = 1; i < res_len; i++){
        printf("%d:\t", i);
        for (unsigned j = 0; j < i; j++){
            match_res *match = (match_res *)getTriangPtr(result_table, sizeof(match_res), i, j);
            printf("%u:%u\t", match->comand1, match->comand2);
        }
        printf("\n");
    }
}