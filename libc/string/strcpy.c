#include <string.h>

char *strcpy(char *dst, const char *src) {
  char *p = dst;
  while ((*p++ = *src++) != '\0')
    ;
  return dst;
}