#include <stdio.h>
#define CONVERTER_IMPL
#include "converter.h"

#define BMP_IMPL
#include "bmp.h"

void run(char *filename, char *output, int group, size_t edge) {
  if (edge % 2 != 0) {
    fprintf(stderr, "Width/height must be even!\n");
    exit(1);
  }
  size_t size = getSize(filename) / group;
  Triple t = readConvert(filename, group, size);
  unsigned char *pixels = (unsigned char *)calloc(edge * edge * 3, 1);
  fillPixels(t, size, pixels, edge);

  BMPImage image = imageInit(pixels, edge);
  writeImage(&image, output);

  freePoints(t.points, size);
  free(pixels);
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr,
            "Usage: %s <inputfile> <outputfile> <groupsize> <width/height>!\n",
            argv[0]);
    exit(1);
  }
  run(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
  return 0;
}
