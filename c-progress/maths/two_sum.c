#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int num;
  int index;
} Element;

int compare(const void *a, const void *b) {
  return ((Element *)a)->num - ((Element *)b)->num;
};

int *two_sum(int *arr, int size, int sum, int *returnSize) {
  // Allocate memory for index num map
  Element *map = (Element *)malloc(size * sizeof(Element));
  //  Fill up the map
  for (int i = 0; i < size; i++) {
    map[i].num = arr[i];
    map[i].index = i;
  }
  // Sort map in ascending order
  qsort(map, size, sizeof(Element), compare);
  int left = 0;
  int right = size - 1;
  while (left < right) {
    int current_sum = map[left].num + map[right].num;

    if (current_sum == sum) {
      int *result = (int *)malloc(2 * sizeof(int));
      result[0] = map[left].index;
      result[1] = map[right].index;
      *returnSize = 2;
      free(map);
      return result;
    } else if (current_sum > sum) {
      right--;
    } else {
      left++;
    }
  }
  *returnSize = 0;
  free(map);
  return NULL;
}

int main() {
  int two_sum_tests[] = {1, -2, 5, 8, -4};
  int test_size = sizeof(two_sum_tests) / sizeof(int);
  int returnSize;

  int *result = two_sum(two_sum_tests, test_size, 6, &returnSize);
  if (returnSize > 0) {
    for (int i = 0; i < returnSize; i++) {
      printf("%d", result[i]);
    }
    printf("\n");
    free(result);
  } else {
    printf("No valid two sum");
  }
  return 0;
}
