#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INT_STRING_LEN 10

int memcmp(const void *, const void *, size_t);
void *memcpy(void *__restrict, const void *__restrict, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
size_t strlen(const char *);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
int itos(int num, char results[]);

#ifdef __cplusplus
}
#endif

#endif
