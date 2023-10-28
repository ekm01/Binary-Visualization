#define CONVERTER_IMPL
#include "converter.h"

#define BMP_IMPL
#include "bmp.h"

void run(char *filename, char *output) {
  unsigned char **points = readConvert(filename);
  size_t size = getSize(filename) / 2;
  unsigned char *pixels = (unsigned char *)calloc(EDGE * EDGE * 3, 1);
  fillPixels(points, size, pixels, EDGE);
  BMPImage image = imageInit(pixels);
  writeImage(&image, output);

  freePoints(points, size);
  free(pixels);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <inputfile> <outputfile>!\n", argv[0]);
    exit(1);
  }
  run(argv[1], argv[2]);
  return 0;
}
