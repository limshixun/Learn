#include "read_string.h"
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

int main() {
  int capacity = 4;
  Task *task = malloc(sizeof(Task));
  TaskList task_list;
  init_task_list(&task_list, capacity);

  printf("Enter a new task\n");
  char *input = read_dynamic_string();

  task->status = 1;
  task->description = input;

  printf("%d. %s\n", 1, task->description);

  push_task(&task_list, *task);
  free(task);
  free_task_list(&task_list);
  return 0;
}
