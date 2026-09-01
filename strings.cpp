#include <stdio.h>
#include <assert.h>

unsigned strLen(const char *str){
    assert(str != NULL);
    unsigned i = 0;
    for (; *(str + i) != '\0'; i++);
    return i;
}

int putS(const char *str){
    assert(str != NULL);
    unsigned i = 0;
    int back = 0;
    for (; *(str + i) != '\0' && back >= 0; i++){
        back = putchar(*(str + i));
    }
    putchar('\n');
    return back;
}

char *strCpy(char *dst, const char *src){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned i = 0;
    for (; *(src + i) != '\0' && *(dst + i) != '\0'; i++){
        *(dst + i) = *(src + i);
    }
    assert(*(dst + i) != '\0');
    *(dst + i) = *(src + i);
    return dst;
}

char *strNCpy(char *dst, const char *src, unsigned n){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned i = 0;
    for (; *(src + i) != '\0' && *(dst + i) != '\0' && i < n; i++){
        *(dst + i) = *(src + i);
    }
    assert(*(dst + i) != '\0' && i == n);
    return dst;
}

char *strChr(char *str, char C){
    unsigned i = 0;
    for (; *(str + i) != '\0' && *(str + i) != C; i++);
    if (C != '\0' && *(str+i) == '\0'){
        return NULL;
    }else
    {
        return (str+i);
    }
}

char *strCat(char *dst, const char *src){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned j = 0;
    for (; *(dst + j) != '\0'; j++);
    unsigned i = 0;
    for (; *(src + i) != '\0'; i++){
        *(dst + i + j) = *(src + i);
    }
    *(dst + i + j) = *(src + i);
    return dst;
}

int strCmp(const char *str1, const char *str2){
    assert(str1 != NULL);
    assert(str2 != NULL);
    unsigned i = 0;
    for (; *(str1 + i) == *(str2 + i) && *(str1 + i) != '\0'; i++);
    if (*(str1 + i) == *(str2 + i))
    {
        return 0;
    }else
    {
        return (*(str1 + i) > *(str2 + i))? 1 : -1;
    }
}

int arr[] = {};
int i = 1;

int main(){
    char str[10] = "First";
    char dir[10] = "Second";
    // strNCpy(dir, str, 3);
    putS(dir);
    printf("%c\n", arr[100000]);
    // printf("%c\n", *strChr(dir, 'd'));
    // printf("%d\n", arr[100]);
}