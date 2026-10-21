#include <math.h>
#include <stdio.h>

int main() {
  double rate = 7;
  double principal = 2300;
  double time = 4;

  double amount = principal * pow((1 + rate / 100), time);

  printf("%f\n", amount - principal);

  return 0;
}
