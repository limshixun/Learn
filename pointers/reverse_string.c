#include <stdio.h>
#include <string.h>

typedef struct {
  char testcase[20];
  char expected[20];
} Testcase;

void reverse_string(char *str) {
  char *x = str;
  char *y = str + strlen(str) - 1;

  while (x < y) {
    if (*x != *y) {
      // Get the intersection between x and y
      *x ^= *y;
      // Get back Y
      *y ^= *x;
      // Get back X
      *x ^= *y;
    }
    x++;
    y--;
  }
}

void swap_memory(void *a, void *b, size_t size) {
  if (a == b)
    return;
  char temp[size];

  memcpy(temp, a, size);
  memcpy(a, b, size);
  memcpy(b, temp, size);
}

void reverse_string_3(char *str) {
  char *x = str;
  char *y = str + strlen(str) - 1;

  while (x < y) {
    // pass x and y directly, they are pointer
    swap_memory(x, y, sizeof(char));
    x++;
    y--;
  }
}

void swap_pointer(int **a, int **b) {
  printf("\n**a %d\n", **a);
  printf("**b %d\n", **b);
  printf("*a %p\n", *a);
  printf("*b %p\n", *b);
  printf("a %p\n", a);
  printf("b %p\n", b);

  int *temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  Testcase testcases[] = {
      {"desserts", "stressed"},
      {"drawer", "reward"},
      {"time", "emit"},
      {"radar", "radar"},
  };
  int testcases_size = sizeof(testcases) / sizeof(Testcase) - 1;
  Testcase *ptr = testcases;

  while (ptr <= testcases + testcases_size) {
    reverse_string_3(ptr->testcase);
    printf("\nReversed: %s", ptr->testcase);
    ptr++;
  }

  int a = 100;
  int b = 200;
  int *ptr_a = &a;
  int *ptr_b = &b;
  printf("Before: *p1 = %d, *p2 = %d\n", *ptr_a, *ptr_b);
  swap_pointer(&ptr_a, &ptr_b);
  printf("After:  *p1 = %d, *p2 = %d\n", *ptr_a, *ptr_b);

  char *str_1 = "pointer";
  char *str_2 = "address";

  return 0;
}

// #define SWAP(a, b, size) do { \
//     unsigned char temp[size]; \
//     memcpy(temp, &(a), size); \
//     memcpy(&(a), &(b), size); \
//     memcpy(&(b), temp, size); \
// } while(0)
// TODO swap the pointer itself
