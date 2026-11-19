#include "read_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_dynamic_string() {
  int capacity = 16;
  int length = 0;
  char *str = malloc(capacity);

  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (length + 1 >= capacity) {
      capacity *= 2;
      char *temp = realloc(str, capacity);
      if (!temp) {
        free(str);
        return NULL;
      }
      str = temp;
    }
    str[length++] = (char)ch;
  }

  if (ch == EOF && length == 0) {
    free(str);
    return NULL;
  }

  str[length] = '\0';
  return str;
}
