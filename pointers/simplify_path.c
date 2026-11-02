#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *simplifyPath(char *path) {
  int len = strlen(path);

  // Create array of string
  char **stack = malloc(len * sizeof(char *));
  // Track top of stack
  int stack_top = 0;

  // Replace "/" with '\0'
  char *token = strtok(path, "/");
  while (token != NULL) {
    if (strcmp(token, "..") == 0 && stack_top > 0) {
      stack_top--; // pop
    } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
      stack[stack_top++] = token; // push
    }
    // Continue with the next token
    token = strtok(NULL, "/");
  }

  char *result = malloc((len + 1) * sizeof(char));
  result[0] = '\0'; // Prepare for strcat

  if (stack_top == 0) {
    strcpy(result, "/");
  } else {
    for (int i = 0; i < stack_top; i++) {
      strcat(result, "/");
      strcat(result, stack[i]);
    }
  }

  free(stack);
  return result;
}

int main() {
  char test[] = "/home//user/./Document/.../../.././/.///something.doc";
  char *result = simplifyPath(test);

  printf("Result: %s\n", result);

  return 0;
}
