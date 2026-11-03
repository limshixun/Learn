#include <stdio.h>

int factorial(int val) {
  if (val == 0)
    return 1;
  return val * factorial(val - 1);
}

int main() {
  int result = factorial(10);
  printf("%d", result);
  return 0;
}
