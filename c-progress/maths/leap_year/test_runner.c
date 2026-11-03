#include "leap.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
  int year;
  bool expected;
} LeapTestCase;

int main(void) {

  LeapTestCase tests[] = {
      {2024, true}, {2020, true}, {2023, false}, {1900, false}, {2100, false},
      {2000, true}, {1600, true}, {0, true},     {-4, true},    {-100, false},
  };
  int length = sizeof(tests) / sizeof(tests[0]);
  int failed_tests = 0;

  for (int i = 0; i < length; i++) {
    bool actual = leap_year(tests[i].year);

    if (actual != tests[i].expected) {
      printf("❌ FAIL: Year %d expected %s, but got %s\n", tests[i].year,
             tests[i].expected ? "true" : "false", actual ? "true" : "false");
      failed_tests++;
    }
  }

  if (failed_tests > 0) {
    printf("\nTesting failed! %d errors found.\n", failed_tests);
    return 1;
  }

  printf("\n✅ All %d leap year tests passed successfully!\n", length);
  return 0;
}
