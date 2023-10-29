#include <stdio.h>

// Randomly generated C code
int foo(int a, int b) {
  int result = a + b;
  return result;
}

int bar(int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += i;
  }
  return sum;
}

int main() {
  int x = 10;
  int y = 5;

  // Call a function
  int result = foo(x, y);

  // Print the result
  printf("Result: %d\n", result);

  // Call another function
  int sum = bar(100);

  // Print the sum
  printf("Sum: %d\n", sum);

  return 0;
}
