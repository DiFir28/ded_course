#include <stdio.h>
#include "strings.cpp"
#include "triangarr.cpp"
#include "sorts.cpp"

int arr[] = {};
int i = 1;

int main(){

    int testarr[] = {458, 8295, 6257, 76, 9878};
    quickSort(testarr, 5);
    for (int i = 0; i < 5; i++){
        printf("%d\n", testarr[i]);
    }
}