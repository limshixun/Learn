#include <stdio.h>

int gcd(int a, int b) {
  int min = (a < b) ? a : b;

  while (min > 0) {
    if (a % min == 0 && b % min == 0) {
      return min;
    }
    min--;
  }
  return min;
}

// Least common multiple
int lcm(int a, int b) { return (a * b) / gcd(a, b); }

int main() {
  int a = 56;
  int b = 98;
  int result = gcd(a, b);

  printf("Result: %d\n", result);

  int lcm_result = lcm(a, b);
  printf("LCM: %d\n", lcm_result);
  return 0;
}
