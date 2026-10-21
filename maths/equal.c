#include <stdbool.h>
#include <stdio.h>

int main() {
  int a = 10;
  int b = 11;

  bool c = !(a ^ b);
  if (c) {
    printf("%d equal %d", a, b);
  } else {
    printf("%d NOT equal %d", a, b);
  }

  return 0;
}
