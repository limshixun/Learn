#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool is_prime(int num) {
  if (num <= 1 || (num != 2 && num % 2 == 0)) {
    return false;
  }
  float sq_root = sqrt((float)num);
  for (int i = 2; i <= sq_root; i++) {
    if (num % i == 0) {
      return false;
    }
  }

  return true;
}

#define ARR_SIZE 1000

int main() {
  // srand((unsigned int)time(NULL));
  // int number[ARR_SIZE];
  //
  // int min = 0;
  // int max = 10;
  //
  // for (int i = 0; i < ARR_SIZE; i++) {
  //   number[i] = rand() % (max + 1) + min;
  // }

  for (int i = 0; i <= ARR_SIZE; i++) {
    int test = i;
    bool result = is_prime(test);
    if (result) {
      printf("%d\n", test);
    } else {
    }
  }

  return 0;
}
