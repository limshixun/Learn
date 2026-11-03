#include <stdio.h>

int main() {
  int binary = 11011;
  int ans = 0;
  int count = 0;

  while (binary > 0) {
    ans += (binary % 10) << count;
    printf("%d\n", ans);
    binary /= 10;
    count++;
  }

  printf("Final: %d", ans);

  return 0;
}
