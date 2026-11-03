#include <ctype.h>
#include <stdio.h>
#include <string.h>

void trim(char *string) {
  char *start = string;
  while (isspace((unsigned char)*start)) {
    // Increment the start of the pointer by 1
    start++;
  }
  if (*start == '\0') {
    return;
  }
  char *end = start + strlen(start) - 1;

  while (end > start && isspace((unsigned char)*end)) {
    end--;
  }
  if (*end == '\0') {
    return;
  }

  // Assign new  string ender
  *(end + 1) = '\0';
  // Move start of "start" to the start of string
  memmove(string, start, strlen(start) + 1);
}

int palindrom_str(char string[]) {
  trim(string);
  int i = 0;
  int j = strlen(string) - 1;

  while (i < j) {
    if (tolower(string[i]) != tolower(string[j])) {
      return 0;
    }
    i++;
    j--;
  }
  return 1;
}

int main() {
  char string[] = " radar ";

  int size = strlen(string);
  int result = palindrom_str(string);

  if (result == 1) {
    printf("%s is a palindrome", string);
  } else {
    printf("%s is NOT a palindrome", string);
  }

  return 0;
}
