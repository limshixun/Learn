#include "bit_manipulation.h"
#include <stdint.h>
#include <stdio.h>

void print_binary(uint8_t num, int max) {
  for (int i = max - 1; i >= 0; i--) {
    putchar(num & (1 << i) ? '1' : '0');
  }
  putchar('\n');
}

// const char *options[] is an array of 5 pointers.
// Each pointer stores the memory address of the first character of a string (R
// in "Read") Each string ends with a null-terminator (\0).
const char *options[] = {"Read", "Write", "Execute", "Admin", "Exit"};

void print_info(int privilege) {
  int size = sizeof(options) / sizeof(*options);
  for (int i = 0; i < size; i++) {
    int isSelected = privilege & (1 << i);
    printf("%d. %s %s\n", i + 1, options[i], isSelected ? "✓" : "");
  }
  print_binary(privilege, 4);
}

int main() {
  int quit = 1;

  int size = sizeof(options) / sizeof(*options);
  int number;
  uint8_t privilege = 0;
  uint8_t *pointer = &privilege;

  do {
    print_info(privilege);

    printf("Input:");
    scanf("%d", &number);

    if (number == 5) {
      quit = 0;
      printf("Bye.\n");
    } else if (number <= 0 || number > 5) {
      printf("Please enter a valid option!\n");
    } else {
      privilege = toggle_bit(privilege, number);
    }
  } while (quit != 0);
  return 0;
}
