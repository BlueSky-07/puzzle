#include "matrix.h"

/**
 * Rotate
 * [
 *   [ cos(θ), -sin(θ) ],
 *   [ sin(θ),  cos(θ) ]
 * ]
 */

Matrix ROTATE_MATRIX_0 = {
  {
    {1, 0},
    {0, 1},
  },
  2, 2
};

Matrix ROTATE_MATRIX_90 = {
  {
    {0, -1},
    {1, 0},
  },
  2, 2
};

Matrix ROTATE_MATRIX_180 = {
  {
    {-1, 0},
    {0, -1},
  },
  2, 2
};

Matrix ROTATE_MATRIX_270 = {
  {
    {0, 1},
    {-1, 0},
  },
  2, 2
};

void matrix_print(Matrix* matrix) {
  Matrix m = *matrix;
  printf("M |");
  for (int x = 1; x <= m.x; x++) {
    printf(" %d", x);
  }
  printf("\n");

  printf("--+");
  for (int x = 1; x <= m.x; x++) {
    printf("--");
  }

  printf("\n");
  for (int y = 0; y < m.y; y ++) {
    printf("%d | ", y + 1);
    for (int x = 0; x < m.x; x++) {
      printf("%d ", m.value[y][x]);
    }
    printf("\n");
  }
}