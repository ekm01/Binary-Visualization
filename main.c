#include <stdio.h>
#define CONVERTER_IMPL
#include "converter.h"

#define BMP_IMPL
#include "bmp.h"

void print(Point *p, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("%zu: ", i);
    printp(p[i]);
  }
}

int main(void) {
  size_t len = EDGE * EDGE * 3;
  unsigned char *pixels = (unsigned char *)malloc(len);
  for (size_t i = 0; i < len; ++i) {
    pixels[i] = 255;
  }
  BMPImage image = imageInit(pixels);
  writeImage(&image, "test.bmp");
  return 0;
}
