#include <stdio.h>
#include <string.h>

void times_two(int *value) { *value <<= 1; }

int main() {
  int n = 1;
  int *pointer_to_n = &n;

  // A pointer points to a memory address
  printf("Pointer: %p \n", (void *)pointer_to_n);
  // * Access the pointed memory address
  printf("*Pointer: %d \n", *pointer_to_n);
  // & returns the address of variable
  printf("&Pointer: %p \n", (void *)&pointer_to_n);

  printf("Before change: %d\n", n);
  *pointer_to_n += 1;
  printf("After change: %d\n", n);

  // Pass the address of variable
  times_two(&n);
  printf("Times two: %d\n", n);

  // Use a counter to print out the string in reverse order
  char sentence[] = "What is a pointer";
  char *pointer_to_sentence = sentence;

  int sentenceLength = sizeof(sentence) / sizeof(sentence[0]) - 1;
  printf("Sentence length: %d \n", sentenceLength);

  int count = sentenceLength;
  printf("\n%s: ", sentence);
  while (count >= 0) {
    printf("%c", *(pointer_to_sentence + count - 1));
    count--;
  }

  // Decrement the address' hexadecimal digit directly
  char sentence2[] = "desserts";
  char *pointer_2 = sentence2 + strlen(sentence2);

  printf("\n%s: ", sentence2);
  while (pointer_2 >= sentence2) {
    printf("%c", *pointer_2);
    pointer_2--;
  }

  return 0;
}
