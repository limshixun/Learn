#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Given an array arr[], where arr[i] represents the exact number of steps to
// move from index i.  An index is considered good if repeatedly following the
// jumps eventually takes you outside the array. Otherwise, if the jumps result
// in an infinite loop, the index is considered bad.
//
// A positive value indicates a move to the right
// A negative value indicates a move to the left.
// A 0 value means no move and considered bad.
// Return the number of good indices.
//
// Input: [2, 3, -1, 2, -2, 4, 1]
// Output: 3
// Explanation: Indices 3, 5, and 6 are good because their jump sequences
// eventually leave the array. Indices 1, 2, and 4 form a cycle, while index 0
// eventually enters this cycle through index 2. Hence, the total number of good
// indices is 3.

bool isInArr(int *arr, int size, int value) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == value) {
      return true;
    }
  }
  return false;
}

int count_good_indices(int *arr, int size) {
  if (size == 0) {
    return 0;
  }
  int count = 0;
  int current_index;

  for (int i = 0; i < size; i++) {
    current_index = i;
    int traveled[size];
    int traveled_size = 0;

    for (int j = 0; j < size; j++) {
      traveled[traveled_size] = current_index;
      traveled_size++;

      if (arr[current_index] == 0) {
        break;
      }
      current_index += arr[current_index];
      if (isInArr(traveled, traveled_size, current_index)) {
        break;
      }

      if (current_index > size) {
        count++;
        break;
      }
    }
  }
  return count;
}

// Input: [2, 3, -1, 2, -2, 4, 1]
bool is_good(int *arr, int size, int cur, int *state, int *memo) {
  if (cur < 0 || cur >= size) {
    return true;
  }

  // If current value is 0, will result in infinite loop
  if (arr[cur] == 0) {
    return false;
  }

  // If current state is visiting, means we have looped back
  if (state[cur] == 1) {
    return false;
  }

  // If current state is resolved, check memo for result
  if (state[cur] == 2) {
    return memo[cur] == 1;
  }

  // set current to visiting
  state[cur] = 1;

  int next_index = cur + arr[cur];
  printf("cur: %d next: %d\n", cur, next_index);
  bool result = is_good(arr, size, next_index, state, memo);

  state[cur] = 2;
  memo[cur] = result ? 1 : 0;

  return result;
}

int optimized_count_good_indices(int *arr, int size) {
  if (size == 0) {
    return 0;
  }

  int count = 0;
  // 0 bad; 1 good;
  int *memo = (int *)calloc(size, sizeof(int));
  // 0 unvisited; 1 visiting; 2 visited;
  int *state = (int *)calloc(size, sizeof(int));

  for (int i = 0; i < size; i++) {
    if (is_good(arr, size, i, state, memo)) {
      count++;
    }
  }
  free(memo);
  free(state);

  return count;
}

int main() {
  int testcase[] = {2, 3, -1, 2, -2, 4, 1};
  int expect = 3;
  int size = sizeof(testcase) / sizeof(int);

  int result = optimized_count_good_indices(testcase, size);
  printf("Expected: %d | Result: %d\n", expect, result);

  return 0;
}
