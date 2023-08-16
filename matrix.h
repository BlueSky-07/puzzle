#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>

#define MAX_MATRIX_X 2
#define MAX_MATRIX_Y 2

typedef struct _Matrix {
  int value[MAX_MATRIX_Y][MAX_MATRIX_X];
  unsigned int x;
  unsigned int y;
} Matrix;

extern Matrix ROTATE_MATRIX_0;
extern Matrix ROTATE_MATRIX_90;
extern Matrix ROTATE_MATRIX_180;
extern Matrix ROTATE_MATRIX_270;

void print_matrix(Matrix* matrix);

#endif