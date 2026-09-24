#ifndef __MY_STR__
#define __MY_STR__

#include <stdio.h>

unsigned strLen(const char *str);
unsigned strNLen(const char *str, size_t n);
int putS(const char *str);
char *strCpy(char *dst, const char *src);
char *strNCpy(char *dst, const char *src, size_t n);
void *memCpy(void *dst, const void *src, size_t n);
char *strDup(char *str);
char *strNDup(char *str, size_t n);
char *strChr(char *str, char C);
char *strrChr(char *str, char C);
char *strCat(char *dst, const char *src);
char *strNCat(char *dst, const char *src, size_t n);
int strCmp(const char *str1, const char *str2);
int strNCmp(const char *str1, const char *str2, size_t n);
char *strStr(char *src, char *trg);

ssize_t getLine(char **strptr, size_t *len, FILE *input);

#endif