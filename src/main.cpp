#include <stdio.h>
#include "strings.hpp"
#include "sorts.hpp"
#include "triangarr.cpp"

<<<<<<< HEAD
int arr[] = {};
int i = 1;
=======
 int comp(void* a, void* b){
    return *(int*)a - *(int*)b;
 }
>>>>>>> c5b95df (Refactror, Fix: quickSort, Add: bableSort, swap func, memCpy, independently type sorts, compare func)

int main(){

    int testarr[] = {456, 8295, 6257, 76, 9878, 6257};
    quickSort(testarr, sizeof(testarr[0]), 6, comp);
    // quickSort(testarr, 6);

    // bableSort( testarr, sizeof(testarr[0]), 6, comp);
    for (int i = 0; i < 6; i++){
        printf("%d\n", testarr[i]);
    }
}