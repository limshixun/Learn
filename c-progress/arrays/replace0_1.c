#include <math.h>
#include <stdio.h>

int main() {
  int number = 10200300;
  int count = 0;
  int ans = 0;

  while (number > 0) {
    int power = pow(10, count);
    int last_digit = number % 10;

    if (last_digit == 0) {
      ans += (1 * power);
    } else {
      ans += (last_digit * power);
    }

    number /= 10;
    printf("power: %d | number: %d | ans: %d\n", power, number, ans);
    count++;
  }
  printf("Ans: %d\n", ans);

  return 0;
}
