#include "strings.cpp"
#include <assert.h>

#define COMANDS_COUNT 5

struct match_res{
    unsigned comand1;
    unsigned comand2;
};

match_res result_table[(COMANDS_COUNT+1) * COMANDS_COUNT / 2] = {};

match_res *getRes(match_res *result_table, unsigned first_com_ind, unsigned sec_com_ind){
    assert(result_table != NULL);
    return (match_res *)((char*)result_table + sizeof(match_res) * ((first_com_ind + 1) * (first_com_ind)  / 2 + sec_com_ind));
}

void writeRes(match_res *result_table, unsigned first_com_ind, unsigned sec_com_ind, match_res res){
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
    match_res *match = getRes(result_table, first_com_ind, sec_com_ind);
    *match = res;
}


void printRes(match_res *result_table, unsigned res_len){
    assert(result_table != NULL);
    printf("\t");
    for (unsigned i = 0; i < res_len - 1; i++){
        printf(" %i\t", i);
    }
    printf("\n");
    for (unsigned i = 1; i < res_len; i++){
        printf("%d:\t", i);
        for (unsigned j = 0; j < i; j++){
            match_res *match = getRes(result_table, i, j);
            printf("%u:%u\t", j, match->comand1, match->comand2);
        }
        printf("\n");
    }
}

int arr[] = {};
int i = 1;

int main(){
    writeRes(result_table, 1, 2, {0, 5});
    printRes(result_table, COMANDS_COUNT);

    // char str[10] = "Hello";
    // char dir[10] = "Helol";
    // // putS(dir);
    // // char *res = strStr(str, dir);
    // // strNCat(str, dir, 2);
    // char *res = strrChr(str, 'b');
    // // if (res != NULL){
    // if(res != NULL){
    //     printf("%s\n", res);
    // }else{
    //     printf("R");
    // }
    // }
    // printf("%c\n", *strChr(dir, 'd'));
    // printf("%d\n", arr[100]);
}