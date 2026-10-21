#include <stdbool.h>
#include <stdio.h>

int int_pow(int base, int exp) {
  int result = 1;
  for (int i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

int number_of_digits(int num) {
  if (num == 0)
    return 1;
  int digits = 0;
  while (num > 0) {
    digits++;
    num /= 10;
  }
  return digits;
}

bool arm_strong(int num, int digits) {
  if (digits == 1) {
    return true;
  }
  int initial_num = num;
  int temp = 0;
  for (int i = 0; i < digits; i++) {
    int last_digit = num % 10;
    temp += int_pow(last_digit, digits);
    num /= 10;
  }
  if (initial_num == temp)
    return true;
  return false;
}

int main() {
  int num = 153;
  int digits = number_of_digits(num);
  bool result = arm_strong(num, digits);
  if (result) {
    printf("%d is a arm strong number", num);
  } else {
    printf("%d is NOT a arm strong number", num);
  }
  return 0;
}
