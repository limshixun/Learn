#include <stdlib.h>
#ifndef STRING_ARRAY
#define STRING_ARRAY

typedef struct {
  char **data;
  size_t size;
  size_t capacity;
} StringArray;

void print_str_arr(StringArray *arr);
void initialize_str_arr(StringArray *str_arr, const size_t initial_capacity);
void push_string(StringArray *str_arr, const char *str);
void pop_string(StringArray *str_arr);

#endif
