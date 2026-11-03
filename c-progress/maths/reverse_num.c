#include <math.h>
#include <stdio.h>

int number_of_digits(int num) {
  int count = 0;
  while (num > 0) {
    num /= 10;
    count++;
  }
  return count;
}

int reverse_num(int num, int digits) {
  int result = 0;
  for (int i = digits - 1; i >= 0; i--) {
    int last_digit = num % 10;
    result += last_digit * pow(10, i);
    num /= 10;
  }

  return result;
}

int reverse_num_2(int num) {
  int result = 0;
  while (num > 0) {
    int last_digit = num % 10;
    result = (result * 10) + last_digit;
    num /= 10;
  }
  return result;
}

int main() {
  int num = 1501030450;
  int digits = number_of_digits(num);
  int result = reverse_num(num, digits);
  int result2 = reverse_num_2(num);
  printf("Result   %d\n", result);
  printf("Result_2 %d\n", result2);
  return 0;
}
