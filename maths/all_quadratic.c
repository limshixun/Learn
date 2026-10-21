#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int quadratic_eq(float a, float b, float c, float *root1, float *root2) {
  if (a == 0) {
    return 0;
  }

  float discriminant = pow(b, 2) - 4 * a * c;
  if (discriminant < 0) {
    return 0;
  }

  *root1 = (-b + sqrt(discriminant)) / (2 * a);
  *root2 = (-b - sqrt(discriminant)) / (2 * a);
  return 1;
}

int main() {
  float root1, root2;
  float a = 1, b = -16, c = 1;

  int success = quadratic_eq(a, b, c, &root1, &root2);

  if (success == 1) {
    printf("Root1: %.3f | Root2: %.3f", root1, root2);
  } else {
    printf("Error: Equation has complex roots or is not quadratic (a == 0)");
  }

  return 0;
}
