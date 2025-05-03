#include <string.h>

int itos(int num, char results[]) {
  int len = 0;
  char temp[INT_STRING_LEN + 1];

  if (num == 0) {
    results[0] = '0';
    return 1;
  }

  for (int i = 0; i < INT_STRING_LEN && num > 0; ++i, ++len) {
    temp[i] = num % 10 + '0', num /= 10;
  }

  for (int i = 0; i < len; ++i) {
    results[i] = temp[len - i - 1];
  }
  results[len] = '\0';

  return len;
}