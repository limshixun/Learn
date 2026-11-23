#include "read_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct task {
  int status;
  char *description;
} Task;

typedef struct {
  Task *data;
  size_t size;
  size_t capacity;
} TaskList;

void init_task_list(TaskList *arr, size_t init_cap) {
  arr->size = 0;
  if (init_cap == 0) {
    arr->capacity = 0;
    arr->data = NULL;
    return;
  }
  arr->capacity = init_cap;
  arr->data = malloc(sizeof(Task) * init_cap);
  if (!arr->data) {
    perror("Failed to malloc task");
    arr->capacity = 0;
    return;
  }
}

void push_task(TaskList *arr, Task task) {
  if (arr->size >= arr->capacity) {
    size_t new_capacity = arr->capacity == 0 ? 4 : arr->capacity * 2;
    Task *temp = realloc(arr->data, sizeof(Task) * new_capacity);
    if (!temp) {
      perror("Failed to realloc task");
      return;
    }
    arr->capacity = new_capacity;
    arr->data = temp;
  }
  arr->data[arr->size] = task;
  arr->size++;
}

void pop_task(TaskList *arr) {
  if (arr->size == 0) {
    return;
  }
  arr->size--;
  // Free String in Task
  free(arr->data[arr->size].description);
  arr->data[arr->size].description = NULL;
}

void free_task_list(TaskList *arr) {
  for (int i = 0; i < arr->size; i++) {
    free(arr->data[i].description);
    arr->data[i].description = NULL;
  }
  free(arr->data);
  arr->data = NULL;
}

int ch;
void consume_line() {
  while ((ch = getchar()) && ch != '\n' && ch != EOF) {
  }
}

void print_arr(TaskList *arr) {
  if (arr->size == 0) {
    printf("The tasks is empty\n");
    return;
  }
  for (int i = 0; i < (arr->size); i++) {
    printf("[%d] %s\n", i, arr->data[i].description);
  }
}

int main() {
  int capacity = 4;
  TaskList task_list;
  init_task_list(&task_list, capacity);

  char option;
  int index;

  printf("%s", "a: add\n");
  printf("%s", "x: remove\n");
  printf("%s", "l: list\n");
  printf("%s", "q: quit\n");
  do {
    printf("Enter option: ");
    // Leading space to ignore whitespaces (space, tab , newline) in the input
    // buffer before reading the next non whitespace character
    // Consume \n from read dynamic string
    scanf(" %c", &option);

    if (option == 'q') {
      free_task_list(&task_list);
      printf("%s", "Bye.\n");
    } else if (option == 'a') {
      printf("Enter a new task: ");
      // Consume next line from previous scanf
      consume_line();
      char *input = read_dynamic_string();
      Task *task = malloc(sizeof(Task));
      task->status = 1;
      task->description = input;
      push_task(&task_list, *task);
      free(task);
    } else if (option == 'x') {
      pop_task(&task_list);
    } else if (option == 'l') {
      print_arr(&task_list);
    } else {
      printf("%s", "Please enter a valid option.\n");
    }
  } while (option != 'q');
  return 0;
}
