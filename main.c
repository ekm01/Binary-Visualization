#define CONVERTER_IMPL
#include "converter.h"

void print(Point *p, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%zu: ", i);
    printp(p[i]);
  }
}

int main(void) {
  Point *test = readConvert("test.jpg");
  print(test, getSize("test.jpg"));
  return 0;
}
