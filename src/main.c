#define CONVERTER_IMPL
#include "converter.h"

#define BMP_IMPL
#include "bmp.h"

void run(char *filename, char *output, int group) {
  size_t size = getSize(filename) / group;
  Triple t = readConvert(filename, group, size);
  unsigned char *pixels = (unsigned char *)calloc(EDGE * EDGE * 3, 1);
  fillPixels(t, size, pixels, EDGE);

  BMPImage image = imageInit(pixels);
  writeImage(&image, output);

  freePoints(t.points, size);
  free(pixels);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <inputfile> <outputfile> <groupsize>!\n",
            argv[0]);
    exit(1);
  }
  run(argv[1], argv[2], atoi(argv[3]));
  return 0;
}
