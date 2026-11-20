#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char **data;
  size_t size;
  size_t capacity;
} StringArray;

void print_arr(StringArray *arr) {
  for (int i = 0; i < (arr->size); i++) {
    printf("[%d] %s\n", i, arr->data[i]);
  }
}

void initialize_str_arr(StringArray *str_arr, const size_t initial_capacity) {
  // Allocate initial_capacity amount of pointers to data, which is pointer that
  // points to pointers, like an array of pointers
  str_arr->size = 0;
  if (initial_capacity <= 0) {
    str_arr->data = NULL;
    str_arr->capacity = 0;
  }
  str_arr->data = malloc(sizeof(char *) * initial_capacity);
  str_arr->capacity = initial_capacity;
}

void push_string(StringArray *str_arr, const char *str) {
  // size is the current index and size before pushing new string
  if (str_arr->size >= str_arr->capacity) {
    size_t new_capacity = str_arr->capacity == 0 ? 4 : str_arr->capacity * 2;
    char **temp = realloc(str_arr->data, new_capacity * sizeof(char *));
    if (!temp) {
      perror("Failed to allocate temporary string");
      return;
    }
    str_arr->data = temp;
    str_arr->capacity = new_capacity;
  }
  // *(((*str_arr).data) + ((*str_arr).size)) = malloc(strlen(str) + 1);
  // *((str_arr->data) + (str_arr->size)) = malloc(strlen(str) + 1);
  str_arr->data[str_arr->size] = malloc(strlen(str) + 1);
  if (!str_arr->data[str_arr->size]) {
    perror("Failed to allocate string");
    return;
  }
  strcpy(str_arr->data[str_arr->size], str);
  str_arr->size++;
}

void pop_string(StringArray *str_arr) {
  // Handle empty array
  if (str_arr->size == 0) {
    return;
  }
  str_arr->size--;
  // Free the string in the memory
  free(str_arr->data[str_arr->size]);
  // Clearing pointer to the string
  str_arr->data[str_arr->size] = NULL;
}

int main() {
  StringArray arr;
  initialize_str_arr(&arr, 4);
  push_string(&arr, "This is the first ever string array element to be pushed");
  push_string(&arr, "Here is another");

  printf("Printing string array\n");
  print_arr(&arr);
  pop_string(&arr);
  printf("Printing after pop\n");
  print_arr(&arr);
  printf("Finished printing string array\n");
}
