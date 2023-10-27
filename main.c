#define CONVERTER_IMPL
#include "converter.h"

#define BMP_IMPL
#include "bmp.h"

void print(unsigned char **p, size_t size) {
  for (size_t i = 0; i < 10; ++i) {
    printf("%zu: ", i);
    printf("%x, %x\n", (int)p[i][0], (int)p[i][1]);
  }
}

int main(void) {
  unsigned char **p = readConvert("test.jpg");
  size_t size = getSize("test.jpg") / 2;
  print(p, size);
  freePoints(p, size);
  return 0;
}
