#include "strings.cpp"

int arr[] = {};
int i = 1;

int main(){
    char str[10] = "Hello";
    char dir[10] = "Helol";
    // putS(dir);
    // char *res = strStr(str, dir);
    // strNCat(str, dir, 2);
    char *res = strrChr(str, 'b');
    // if (res != NULL){
    if(res != NULL){
        printf("%s\n", res);
    }else{
        printf("R");
    }
    // }
    // printf("%c\n", *strChr(dir, 'd'));
    // printf("%d\n", arr[100]);
}