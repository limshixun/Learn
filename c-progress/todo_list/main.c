#include "read_string.h"
#include "string_array.h"
#include <ctype.h>
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
  arr->capacity = 0;
  arr->size = 0;
}

void consume_line() {
  int ch;
  while ((ch = getchar()) && ch != '\n' && ch != EOF) {
  }
}

void print_arr(TaskList *arr) {
  if (arr->size == 0) {
    printf("The tasks is empty\n");
    return;
  }
  for (int i = 0; i < (arr->size); i++) {
    char ch = ' ';
    if (arr->data[i].status == 1)
      ch = 'x';
    printf("%d. [%c] %s\n", i + 1, ch, arr->data[i].description);
  }
}

void toggle_mode(TaskList *task_list) {
  int buf_size = 48;
  char toggle_option[buf_size];
  do {
    print_arr(task_list);
    printf("Select item by index to toggle: \n");
    fgets(toggle_option, buf_size, stdin);
    if (toggle_option[0] == 'q') {
      printf("Exit toggle mode\n");
      continue;
    }
    int number = strtol(toggle_option, NULL, 10);
    if (!(number > 0 && number <= task_list->size)) {
      printf("Invalid task index\n");
      continue;
    }
    task_list->data[number - 1].status ^= 1;
  } while (toggle_option[0] != 'q');
}

const char *OPTIONS[] = {"add", "remove", "list", "toggle", "quit"};

void print_options() {
  for (size_t i = 0; i < (sizeof(OPTIONS) / sizeof(char *)); i++) {
    printf("%c: %s\n", tolower((unsigned char)OPTIONS[i][0]), OPTIONS[i]);
  }
}

StringArray *split(StringArray *str_arr, char *str, char *delimeter) {
  char *token = strtok(str, delimeter);
  while (token != NULL) {
    push_string(str_arr, token);
    token = strtok(NULL, delimeter);
  }
  return str_arr;
}

void split_by_first_occurance(StringArray *str_arr, char *str, char delimeter) {
  char *status;
  char *description = strchr(str, delimeter);
  if (!description) {
    printf("Failed to identify delimeter");
    return;
  }

  size_t len = description - str;
  status = malloc(len + 1);
  strncpy(status, str, len);
  status[len] = '\0';

  push_string(str_arr, status);
  push_string(str_arr, description + 1);
  free(status);
  status = NULL;
}

void load_tasks(TaskList *task_list) {
  // Create/Open file
  FILE *fptr = fopen("todo.txt", "r");

  if (fptr == NULL) {
    printf("Error opening file!\n");
    return;
  }

  StringArray sa;
  initialize_str_arr(&sa, 4);

  char buffer[256];

  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
    split_by_first_occurance(&sa, buffer, '|');

    if (sa.size == 2) {
      Task task;
      task.status = strtol(sa.data[0], NULL, 10);
      task.description = malloc(strlen(sa.data[1]) + 1);
      strcpy(task.description, sa.data[1]);
      push_task(task_list, task);
    }
    while (sa.size > 0) {
      pop_string(&sa);
    }
  }
  free(sa.data);
  sa.data = NULL;
  sa.size = 0;
  fclose(fptr);
}

void save_tasks(TaskList *task_list) {
  FILE *fptr = fopen("todo.txt", "w");
  if (!fptr) {
    printf("Error opening file!\n");
    return;
  }

  for (size_t i = 0; i < task_list->size; i++) {
    char *text = task_list->data[i].description;
    int status = task_list->data[i].status;
    fprintf(fptr, "%d|%s\n", status, text);
  }

  fclose(fptr);
}

int main() {
  // Task list
  int capacity = 4;
  TaskList task_list;
  init_task_list(&task_list, capacity);

  load_tasks(&task_list);

  char option;
  print_options();
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
      task->status = 0;
      task->description = input;
      push_task(&task_list, *task);
      free(task);
      save_tasks(&task_list);
    } else if (option == 'r') {
      pop_task(&task_list);
      save_tasks(&task_list);
    } else if (option == 'l') {
      print_arr(&task_list);
    } else if (option == 't') {
      toggle_mode(&task_list);
      save_tasks(&task_list);
    } else {
      printf("%s", "Please enter a valid option.\n");
    }
  } while (option != 'q');
  return 0;
}
