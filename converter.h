#ifndef CONVERTER_H
#define CONVERTER_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char x;
  char y;
} Point;

void printp(Point p);

Point convert(char c);

Point *readConvert(char *filename);

size_t getSize(char *filename);

#endif // CONVERTER_H

#ifdef CONVERTER_IMPL

void printp(Point p) { printf("%d, %d\n", (int)p.x, (int)p.y); }

Point convert(char c) {
  Point res;
  res.x = (c & 0xF0) >> 4;
  res.y = c & 0x0F;
  return res;
}

Point *readConvert(char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "File with the name %s does not exist!\n", filename);
    exit(1);
  }

  // allocate array of points wrt. size of file
  size_t size = getSize(filename);
  Point *points = (Point *)malloc(size * sizeof(Point));

  // read bytes from file and fill array with points
  char byte;
  size_t i = 0;
  while (fread(&byte, 1, 1, file) == 1) {
    Point p = convert(byte);
    points[i] = p;
    i++;
  }
  fclose(file);
  return points;
}

size_t getSize(char *filename) {
  FILE *file = fopen(filename, "rb");
  assert(file != NULL);
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  if (size > SIZE_MAX) {
    fprintf(stderr, "File is too big!\n");
    exit(1);
  }
  fclose(file);
  return size;
}

#endif // CONVERTER_IMPL
