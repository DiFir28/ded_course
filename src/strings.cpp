#include <assert.h>
#include <stdio.h>

unsigned strLen(const char *str){
    assert(str != NULL);
    unsigned i = 0;
    for (; str[i] != '\0'; i++) {;}
    return i;
}

unsigned strNLen(const char *str, unsigned n){
    assert(str != NULL);
    unsigned i = 0;
    for (; str[i] != '\0' && i < n; i++){;}
    return i;
}

int putS(const char *str){
    assert(str != NULL);
    unsigned i = 0;
    int back = 0;
    for (; str[i] != '\0' && back >= 0; i++){
        back = putchar(str[i]);
        if (back == -1){
            return back;
        }
    }
    putchar('\n');
    return back;
}

char *strCpy(char *dst, const char *src){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned i = 0;
    for (; src[i] != '\0' && dst[i] != '\0'; i++){
        dst[i] = src[i];
    }
    assert(dst[i] != '\0');
    dst[i] = src[i];
    return dst;
}

char *strNCpy(char *dst, const char *src, unsigned n){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned i = 0;
    for (; src[i] != '\0' && dst[i] != '\0' && i < n; i++){
        dst[i] = src[i];
    }
    assert(dst[i] != '\0' && i == n);
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
    for (; str[i] != '\0' && str[i] != C; i++){;}
    if (C != '\0' && *(str+i) == '\0'){
        return NULL;
    }else
    {
        return (str + i);
    }
}

char *strrChr(char *str, char C){
    unsigned i = 0;
    char *ptr = NULL;
    for (; str[i] != '\0'; i++){
        if (str[i] == C){
            ptr = str + i;
        }
    }
    if ( C == '\0'){
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
    unsigned dst_i = 0;
    for (; *(dst + dst_i) != '\0'; dst_i++){;}
    unsigned src_i = 0;
    for (; src[src_i] != '\0'; src_i++){
        dst[src_i + dst_i] = src[src_i];
    }
    dst[src_i + dst_i] = '\0';
    return dst;
}

char *strNCat(char *dst, const char *src, unsigned n){
    assert(dst != NULL);
    assert(src != NULL);
    unsigned dst_i = 0;
    for (; *(dst + dst_i) != '\0'; dst_i++){;}
    unsigned src_i = 0;
    for (; src[src_i] != '\0' && src_i < n; src_i++){
        dst[src_i + dst_i] = src[src_i];
    }
    dst[src_i + dst_i] = '\0';
    return dst;
}

int strCmp(const char *str1, const char *str2){
    assert(str1 != NULL);
    assert(str2 != NULL);
    unsigned i = 0;
    for (; str1[i] == str2[i] && str1[i] != '\0'; i++){;}
    if (str1[i] == str2[i])
    {
        return 0;
    }else
    {
        return (str1[i] > str2[i])? 1 : -1;
    }
}

int strNCmp(const char *str1, const char *str2, unsigned n){
    assert(str1 != NULL);
    assert(str2 != NULL);
    n--;
    unsigned i = 0;
    for (; str1[i] == str2[i] && str1[i] != '\0' && i < n; i++){;}
    if (str1[i] == str2[i])
    {
        return 0;
    }else
    {
        return (str1[i] > str2[i])? 1 : -1;
    }
}

char *strStr(char *src, char *trg){
    unsigned len = strLen(trg);
    char *beg = strChr(src, *(trg));
    while (beg != NULL){
        char buf = *(beg + len);
        *(beg + len)  = '\0';
        if (strCmp(beg, trg) == 0){
            *(beg + len) = buf;
            return beg;
        }
        *(beg + len) = buf;
        beg = strChr(beg + 1, *(trg));
    }
    return NULL;
}

ssize_t getLine(char **strptr, size_t *len, FILE *input){
    assert(input != NULL);
    size_t cur_len = 8;
    char *str =  (char *)calloc(cur_len, sizeof(char));
    *len = 0;
    unsigned char buf = getc(input); 
    str[*len] = buf;
    (*len)++;
    while (buf != NULL && buf != '\n' && buf != '\0'){
        if (*len >= cur_len){
            cur_len += 8;
            char *buf = (char*)realloc(str, cur_len * 2);
            if (buf == NULL){
                return NULL;
            }
            str = buf;
        }
        buf = getc(input);
        str[*len] = buf;
        (*len)++;
    }
    *strptr = str;
    return *len;
}
