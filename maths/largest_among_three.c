#include <stdio.h>

int largest_among_three(int a, int b, int c) {
  if (a > b && a > c) {
    return a;
  }
  if (b > a && b > c) {
    return b;
  }
  return c;
}

int main() {
  int a = 1;
  int b = 3;
  int c = 3;

  int result = largest_among_three(a, b, c);
  printf("result: %d", result);
  return 0;
}
