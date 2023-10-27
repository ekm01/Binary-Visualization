#ifndef CONVERTER_H
#define CONVERTER_H

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char **readConvert(char *filename);

size_t getSize(char *filename);

void freePoints(unsigned char **points, size_t size);

#endif // CONVERTER_H

#ifdef CONVERTER_IMPL

unsigned char **readConvert(char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "File with the name %s does not exist!\n", filename);
    exit(1);
  }

  // allocate array of points wrt. size of file
  size_t size = getSize(filename) / 2;
  unsigned char **points =
      (unsigned char **)malloc(size * sizeof(unsigned char *));
  assert(points != NULL);

  // read bytes from file and fill array with points
  unsigned char buf[2];
  size_t i = 0;
  while (fread(&buf, 1, 2, file) == 2) {
    points[i] = (unsigned char *)malloc(2);
    assert(points[i] != NULL);

    points[i][0] = buf[0];
    points[i][1] = buf[1];
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

void freePoints(unsigned char **points, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    free(points[i]);
  }
  free(points);
}

#endif // CONVERTER_IMPL
