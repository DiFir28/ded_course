#include <stdio.h>
#include <assert.h>

unsigned strLen(const char *str){
    assert(str != NULL);
    unsigned i = 0;
    for (; *(str + i) != '\0'; i++);
    return i;
}

unsigned strNLen(const char *str, unsigned n){
    assert(str != NULL);
    unsigned i = 0;
    for (; *(str + i) != '\0' && i < n; i++);
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

char *strDup(char *str){
    char *new_str = (char*)calloc(strLen(str) + 1, sizeof(char));
    if (new_str == NULL){
        return NULL;
    }
    strNCpy(new_str, str, strLen(str));
    return new_str;
}

char *strNDup(char *str, unsigned n){
    char *new_str = (char*)calloc(n + 1, sizeof(char));
    if (new_str == NULL){
        return NULL;
    }
    strNCpy(new_str, str, n);
    return new_str;
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

char *strrChr(char *str, char C){
    unsigned i = 0;
    char *ptr = NULL;
    for (; *(str + i) != '\0'; i++){
        if (*(str + i) == C){
            ptr = str + i;
        }
    }
    if (*(str + i) == C){
            ptr = str + i;
    }
    if (ptr == NULL){
        return NULL;
    }else
    {
        return (ptr);
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
    *(dst + i + j) = '\0';
    return dst;
}

char *strNCat(char *dst, const char *src, unsigned n){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned j = 0;
    for (; *(dst + j) != '\0'; j++);
    unsigned i = 0;
    for (; *(src + i) != '\0' && i < n; i++){
        *(dst + i + j) = *(src + i);
    }
    *(dst + i + j) = '\0';
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

int strNCmp(const char *str1, const char *str2, unsigned n){
    assert(str1 != NULL);
    assert(str2 != NULL);
    n--;
    unsigned i = 0;
    for (; *(str1 + i) == *(str2 + i) && *(str1 + i) != '\0' && i < n; i++);
    if (*(str1 + i) == *(str2 + i))
    {
        return 0;
    }else
    {
        return (*(str1 + i) > *(str2 + i))? 1 : -1;
    }
}

char *strStr(char *src, char *trg){
    unsigned len = strLen(trg);
    char *beg = strChr(src, *(trg));
    while (beg != NULL){
        char buf = *(beg + len);
        *(beg + len)  = '\0';
        if (strCmp(beg, trg) == 0){
            *(beg + len) == buf;
            return beg;
        }
        *(beg + len) == buf;
        beg = strChr(beg + 1, *(trg));
    }
    return NULL;
}

ssize_t getLine(char **strptr, size_t *len, FILE *input){
    assert(input != NULL);
    size_t cur_len = 8;
    char *str =  (char *)malloc(cur_len);
    *len = 0;
    unsigned char buf = getc(input); 
    *len++;
    while (buf != NULL && buf != '\n' && buf != '\0'){
        if (*len >= cur_len){
            cur_len += 8;
            str = (char*)realloc(str, cur_len);
        }
        buf = getc(input); 
        *len++;
    }
    if (*len > cur_len){
        str = (char*)realloc(str, *len);
    }
    strptr = &str;
}
