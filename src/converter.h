#ifndef CONVERTER_H
#define CONVERTER_H

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t max;
  size_t min;
  size_t **points;
} Triple;

typedef struct {
  size_t x;
  size_t y;
} Double;

typedef Double (*Alg)(int, unsigned char *);

Triple readConvert(char *filename, int group, size_t size);

size_t getSize(char *filename);

void freePoints(size_t **points, size_t size);

void fillPixels(Triple triple, size_t size, unsigned char *pixels, size_t edge);

Double algOdd(int group, unsigned char *buf);

Double algEven(int group, unsigned char *buf);

size_t mini(size_t a, size_t b);

size_t maxi(size_t a, size_t b);

#endif // CONVERTER_H

#ifdef CONVERTER_IMPL

#define GROUP_SIZE_MAX 16

Triple readConvert(char *filename, int group, size_t size) {
  if (group > 16 || group < 1) {
    fprintf(stderr, "Group size must be between 1 and 16!\n");
    exit(1);
  }
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    fprintf(stderr, "File with the name %s does not exist!\n", filename);
    exit(1);
  }

  // allocate array of points wrt. size of file
  Triple triple;
  triple.points = (size_t **)malloc(size * sizeof(size_t *));

  assert(triple.points != NULL);

  // read bytes from file and fill array with points
  size_t min = SIZE_MAX;
  size_t max = 0;
  unsigned char buf[group];
  size_t i = 0;

  // set algorithm depending on group
  Alg algorithm = algOdd;
  if (group % 2 == 0) {
    algorithm = algEven;
  }

  while (fread(&buf, 1, group, file) == (size_t)group) {
    triple.points[i] = (size_t *)malloc(2 * sizeof(size_t));
    assert(triple.points[i] != NULL);

    Double points = algorithm(group, buf);

    size_t maxx = maxi(points.x, points.y);
    size_t minn = mini(points.x, points.y);

    if (minn < min) {
      min = minn;
    }

    if (maxx > max) {
      max = maxx;
    }

    triple.points[i][0] = points.x;
    triple.points[i][1] = points.y;
    i++;
  }

  triple.max = max;
  triple.min = min;
  fclose(file);
  return triple;
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

void freePoints(size_t **points, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    free(points[i]);
  }
  free(points);
}

#define POS(x, y, e) (x * 3 * e) + (y * 3)

void fillPixels(Triple triple, size_t size, unsigned char *pixels,
                size_t edge) {
  for (size_t i = 0; i < size; ++i) {
    double max = (double)triple.max;
    double min = (double)triple.min;

    double sf = (edge - 1) / (max - min);
    double x = (((double)triple.points[i][0] - min) * sf);
    double y = (((double)triple.points[i][1] - min) * sf);
    size_t pos = POS((size_t)round(x), (size_t)round(y), edge);
    pixels[pos] = 255;
    pixels[pos + 1] = 255;
    pixels[pos + 2] = 255;
  }
}

Double algOdd(int group, unsigned char *buf) {
  // 0xABCDEF -> x: 0xABC, y: 0xDEF
  Double res;
  int mid = group / 2;
  size_t x = 0;
  size_t y = buf[mid] & 0x0F;
  int j = mid + 1;
  for (int i = 0; i < mid; ++i) {
    x = (x << 8) | buf[i];
    y = (y << 8) | buf[j++];
  }
  x = (x << 4) | ((buf[mid] & 0xF0) >> 4);
  res.x = x;
  res.y = y;
  return res;
}

Double algEven(int group, unsigned char *buf) {
  // 0xABCDEF12 -> x: 0xABCD, y: 0xEF12
  Double res;
  int mid = group / 2;
  size_t x = 0;
  size_t y = 0;
  int j = mid;
  for (int i = 0; i < mid; ++i) {
    x = (x << 8) | buf[i];
    y = (y << 8) | buf[j++];
  }
  res.x = x;
  res.y = y;
  return res;
}

size_t mini(size_t a, size_t b) {
  if (a <= b) {
    return a;
  }
  return b;
}

size_t maxi(size_t a, size_t b) {
  if (a <= b) {
    return b;
  }
  return a;
}

#endif // CONVERTER_IMPL
