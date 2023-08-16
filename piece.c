#include "piece.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * y
 * 4
 * 3 *
 * 2 *
 * 1 * * *
 *   1 2 3 4 x
 */
Piece PIECE_A = {
  'A',
  {
    {1, 1},
    {2, 1},
    {3, 1},
    {1, 2},
    {1, 3},
  },
  5,
};

/**
 * y
 * 4
 * 3
 * 2
 * 1 * * * *
 *   1 2 3 4 x
 */
Piece PIECE_B = {
  'B',
  {
    {1, 1},
    {2, 1},
    {3, 1},
    {4, 1},
  },
  4,
};

/**
 * y
 * 4
 * 3
 * 2 *
 * 1 * * * *
 *   1 2 3 4 x
 */
Piece PIECE_C = {
  'C',
  {
    {1, 1},
    {2, 1},
    {3, 1},
    {4, 1},
    {1, 2},
  },
  5,
};

/**
 * y
 * 4
 * 3   *
 * 2   *
 * 1 * * *
 *   1 2 3 4 x
 */
Piece PIECE_D = {
  'D',
  {
    {1, 1},
    {2, 1},
    {3, 1},
    {2, 2},
    {2, 3},
  },
  5,
};

/**
 * y
 * 4
 * 3
 * 2 *
 * 1 * * *
 *   1 2 3 4 x
 */
Piece PIECE_E = {
  'E',
  {
    {1, 1},
    {2, 1},
    {3, 1},
    {1, 2},
  },
  4,
};

/**
 * y
 * 4
 * 3
 * 2   * *
 * 1 * *
 *   1 2 3 4 x
 */
Piece PIECE_F = {
  'F',
  {
    {1, 1},
    {2, 1},
    {2, 2},
    {3, 2},
  },
  4,
};


/**
 * y
 * 4
 * 3
 * 2   * * *
 * 1 * *
 *   1 2 3 4 x
 */
Piece PIECE_G = {
  'G',
  {
    {1, 1},
    {2, 1},
    {2, 2},
    {3, 2},
    {4, 2},
  },
  5,
};

/**
 * y
 * 4
 * 3   * *
 * 2   *
 * 1 * *
 *   1 2 3 4 x
 */
Piece PIECE_H = {
  'H',
  {
    {1, 1},
    {2, 1},
    {2, 2},
    {2, 3},
    {3, 3},
  },
  5,
};


/**
 * y
 * 4
 * 3 *
 * 2 * *
 * 1 * *
 *   1 2 3 4 x
 */
Piece PIECE_I = {
  'I',
  {
    {1, 1},
    {2, 1},
    {1, 2},
    {2, 2},
    {1, 3},
  },
  5,
};

/**
 * y
 * 4
 * 3
 * 2 *   *
 * 1 * * *
 *   1 2 3 4 x
 */
Piece PIECE_J = {
  'J',
  {
    {1, 1},
    {2, 1},
    {3, 1},
    {1, 2},
    {3, 2},
  },
  5,
};
Piece* ALL_PIECES[10] = {&PIECE_A, &PIECE_B, &PIECE_C, &PIECE_D, &PIECE_E,
                         &PIECE_F, &PIECE_G, &PIECE_H, &PIECE_I, &PIECE_J};

void init_piece_puzzle(Piece* piece) {
  for (int i = 0; i < piece->position_count; i++) {
    Position p = piece->position[i];
    piece->puzzle[p.x][p.y] = 1;
  }
}

unsigned int fix_negative(int number, unsigned int max) {
  if (number == 0) return 0;
  int result = number;
  while (result < 0) {
    result = result + max + 1;
  }
  result = result % max;
  result = result ? result : max;
  // printf("fix(%d) = %d\n", number, result);
  return result;
}

Piece rotate_piece(Piece piece, ROTATE_DIRECTION direction) {
  Piece* result = malloc(sizeof(Piece));
  Matrix matrix;
  int mirror = direction > 0 ? 1 : -1;
  switch (direction) {
    case ROTATE_DIRECTION_90:
    case ROTATE_DIRECTION_MIRROR_90:
      matrix = ROTATE_MATRIX_90;
      break;
    case ROTATE_DIRECTION_180:
    case ROTATE_DIRECTION_MIRROR_180:
      matrix = ROTATE_MATRIX_180;
      break;
    case ROTATE_DIRECTION_270:
    case ROTATE_DIRECTION_MIRROR_270:
      matrix = ROTATE_MATRIX_270;
      break;
    case ROTATE_DIRECTION_0:
    case ROTATE_DIRECTION_MIRROR_0:
    default:
      matrix = ROTATE_MATRIX_0;
      break;
  }

  result->name = piece.name;
  result->position_count = piece.position_count;

  // printf("direction: %d, mirror: %d\n", direction, mirror);
  // print_matrix(matrix);
  for (int i = 0; i < piece.position_count; i ++) {
    Position p = piece.position[i];
    Position* ip = &result->position[i];

    ip->x = fix_negative(
      matrix.value[0][0] * p.x + matrix.value[0][1] * p.y,
      PIECE_X
    );

    ip->y = fix_negative(
      matrix.value[1][0] * p.x + matrix.value[1][1] * p.y,
      PIECE_Y
    );

    ip->y = fix_negative(ip->y * mirror, PIECE_Y);

    // printf("%d, %d => %d, %d\n", p.x, p.y, ip->x, ip->y);
  }

  return fix_piece(*result);
}

Piece fix_piece(Piece piece) {
  Piece* result = malloc(sizeof(Piece));
  result->name = piece.name;
  result->position_count = piece.position_count;
  int min_x = piece.position[0].x, min_y = piece.position[0].y;
  for (int i = 1; i < piece.position_count; i ++) {
    Position p = piece.position[i];
    if (p.x < min_x) min_x = p.x;
    if (p.y < min_y) min_y = p.y;
  }
  for (int i = 0; i < piece.position_count; i ++) {
    Position p = piece.position[i];
    Position* ip = &result->position[i];
    ip->x = p.x - min_x + 1;
    ip->y = p.y - min_y + 1;
  }

  return *result;
}

void print_piece(Piece piece) {
  init_piece_puzzle(&piece);

  for (int y = PIECE_Y; y >= 1; y--) {
    printf("%d | ", y);
    for (int x = 1; x <= PIECE_X; x ++) {
      printf("%c ", piece.puzzle[x][y]
                 ? '*'
                 : ' ');
    }
    printf("\n");
  }
  printf("--+--------\n");
  printf("%c | 1 2 3 4\n", piece.name);
}
