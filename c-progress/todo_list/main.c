#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct task {
  int status;
  char *description;
} Task;

char *read_dynamic_string() {
  int capacity = 16;
  int length = 0;

  char *str = malloc(sizeof(char) * capacity);

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

int main() {
  Task *task = malloc(sizeof(Task));

  printf("Enter a new task\n");
  char *input = read_dynamic_string();

  task->status = 1;
  task->description = input;

  printf("%d. %sstatus\n", 1, task->description);
  return 0;
}
