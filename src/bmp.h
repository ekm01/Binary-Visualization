#ifndef BMP_H
#define BMP_H

#include <stdio.h>

#define DEFAULT_EDGE 2048

typedef struct {
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offset;
  unsigned int DIB_header_size;
  int image_width;
  int image_height;
  unsigned short planes;
  unsigned short bits_per_pixel;
  unsigned int compression;
  int xPixels_pm;
  int yPixels_pm;
  unsigned int image_size;
  unsigned int colors;
  unsigned int important_colors;
} BMPHeader;

typedef struct {
  BMPHeader header;
  unsigned char *pixels;
} BMPImage;

BMPHeader headerInit(size_t edge);

BMPImage imageInit(unsigned char *pixels, size_t edge);

void writeImage(BMPImage *image, char *fileName);

#endif // BMP_H

#ifdef BMP_IMPL

BMPHeader headerInit(size_t edge) {
  BMPHeader header;

  header.size = 3 * edge * edge;
  header.reserved1 = 0;
  header.reserved2 = 0;
  header.offset = 54;
  header.DIB_header_size = 40;
  header.image_width = edge;
  header.image_height = edge;
  header.planes = 1;
  header.bits_per_pixel = 24;
  header.compression = 0;
  header.image_size = 0;
  header.xPixels_pm = 0;
  header.yPixels_pm = 0;
  header.colors = 0;
  header.important_colors = 0;

  return header;
}

BMPImage imageInit(unsigned char *pixels, size_t edge) {
  BMPImage image;
  image.header = headerInit(edge);
  image.pixels = pixels;
  return image;
}

void writeImage(BMPImage *image, char *filename) {
  FILE *imagefile = fopen(filename, "wb");
  if (imagefile == NULL) {
    fprintf(stderr, "File cannot be created!\n");
    exit(1);
  }

  unsigned short signature = 0x4D42; //"BM" in Ascii Little-Endian

  fwrite(&signature, 2, 1, imagefile);
  fwrite(&image->header, sizeof(BMPHeader), 1, imagefile);

  // write all the pixels to the file blue, green, red
  for (size_t i = 0; i < image->header.size; ++i) {
    fwrite(image->pixels, 1, 1, imagefile);
    image->pixels++;
  }
  fclose(imagefile);
}
#endif // BMP_IMPL
