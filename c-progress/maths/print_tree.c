#include <stdio.h>
#include <string.h>

void print_tree(int height) {
  // 1, 3, 5 ...
  int max_width = 2 * height - 1;
  // + 1 for \0
  char str[max_width + 1];
  // Set value to str
  memset(str, '*', max_width);
  str[max_width] = '\0';

  for (int i = 0; i < height; i++) {
    int number_of_str = 2 * i + 1;
    int left_padding = (max_width - number_of_str) / 2;
    int total_field_width = left_padding + number_of_str;
    printf("%*.*s\n", total_field_width, number_of_str, str);
  }
}

int main() {
  printf("\nStart\n");
  print_tree(10);
  printf("\nEnd\n");
  return 0;
}
