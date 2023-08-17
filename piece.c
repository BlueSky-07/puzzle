#include "piece.h"

/**
 * y
 * 3
 * 2 *
 * 1 *
 * 0 * * *
 *   0 1 2 3 x
 */
Piece PIECE_A = {
  'A',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
    {0, 2},
  },
  5,
};

/**
 * y
 * 3
 * 2
 * 1
 * 0 * * * *
 *   0 1 2 3 x
 */
Piece PIECE_B = {
  'B',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
  },
  4,
};

/**
 * y
 * 3
 * 2
 * 1 *
 * 0 * * * *
 *   0 1 2 3 x
 */
Piece PIECE_C = {
  'C',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {0, 1},
  },
  5,
};

/**
 * y
 * 3
 * 2   *
 * 1   *
 * 0 * * *
 *   0 1 2 3 x
 */
Piece PIECE_D = {
  'D',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {1, 1},
    {1, 2},
  },
  5,
};

/**
 * y
 * 3
 * 2
 * 1 *
 * 0 * * *
 *   0 1 2 3 x
 */
Piece PIECE_E = {
  'E',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
  },
  4,
};

/**
 * y
 * 3
 * 2
 * 1   * *
 * 0 * *
 *   0 1 2 3 x
 */
Piece PIECE_F = {
  'F',
  {
    {0, 0},
    {1, 0},
    {1, 1},
    {2, 1},
  },
  4,
};


/**
 * y
 * 3
 * 2
 * 1     * *
 * 0 * * *
 *   0 1 2 3 x
 */
Piece PIECE_G = {
  'G',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {2, 1},
    {3, 1},
  },
  5,
};

/**
 * y
 * 3
 * 2   * *
 * 1   *
 * 0 * *
 *   0 1 2 3 x
 */
Piece PIECE_H = {
  'H',
  {
    {0, 0},
    {1, 0},
    {1, 1},
    {1, 2},
    {2, 2},
  },
  5,
};


/**
 * y
 * 3
 * 2
 * 1 * *
 * 0 * * *
 *   0 1 2 3 x
 */
Piece PIECE_I = {
  'I',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
    {1, 1},
  },
  5,
};

/**
 * y
 * 3
 * 2
 * 1 *   *
 * 0 * * *
 *   0 1 2 3 x
 */
Piece PIECE_J = {
  'J',
  {
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 1},
    {2, 1},
  },
  5,
};
Piece* ALL_PIECES[PIECE_COUNT] = {
  &PIECE_A, &PIECE_B, &PIECE_C, &PIECE_D, &PIECE_E,
  &PIECE_F, &PIECE_G, &PIECE_H, &PIECE_I, &PIECE_J,
};

void piece_init_puzzle(Piece* piece) {
  for (int i = 0; i < piece->position_count; i++) {
    Position p = piece->positions[i];
    piece->puzzle[p.x][p.y] = 1;
  }
}

Piece* rotate_piece(Piece* piece, RotateDirection direction) {
  Piece p = *piece;
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

  result->name = p.name;
  result->position_count = p.position_count;

  logger_debug("rotate_piece, direction: %d, mirror: %d, matrix:", direction, mirror);
  if (logger_level_is_debug_ok()) print_matrix(&matrix);

  for (int i = 0; i < p.position_count; i ++) {
    // move 1, 1 to use rotate matrix
    int fix = 1;
    Position pp = p.positions[i];
    Position* pos_fixed = position_move_by_coordinate(&pp, fix, fix, POSITION_MOVE_NEW);
    Position pf = *pos_fixed;
    Position* ip = &result->positions[i];

    ip->x = calc_negative_to_positive(
      matrix.value[0][0] * pf.x + matrix.value[0][1] * pf.y,
      PIECE_X + fix
    );

    ip->y = calc_negative_to_positive(
      matrix.value[1][0] * pf.x + matrix.value[1][1] * pf.y,
      PIECE_Y + fix
    );

    ip->y = calc_negative_to_positive(ip->y * mirror, PIECE_Y + fix);

    // revert fix
    ip->x = ip->x - fix;
    ip->y = ip->y - fix;

    logger_debug("rotate_piece, loop: %d, %d => %d, %d", pp.x, pp.y, ip->x, ip->y);
    free(pos_fixed);
  }

  Piece* fixed_result = fix_piece(result);
  free(result);
  return fixed_result;
}

Piece* fix_piece(Piece* piece) {
  Piece p = *piece;
  Piece* result = malloc(sizeof(Piece));
  result->name = p.name;
  result->position_count = p.position_count;
  int min_x = p.positions[0].x, min_y = p.positions[0].y;
  for (int i = 1; i < p.position_count; i ++) {
    Position pos = p.positions[i];
    if (pos.x < min_x) min_x = pos.x;
    if (pos.y < min_y) min_y = pos.y;
  }
  for (int i = 0; i < p.position_count; i ++) {
    Position pos = p.positions[i];
    Position* ip = &result->positions[i];
    ip->x = pos.x - min_x;
    ip->y = pos.y - min_y;
  }

  return result;
}

void print_piece(Piece* piece) {
  piece_init_puzzle(piece);
  Piece p = *piece;

  for (int y = PIECE_Y - 1; y >= 0; y--) {
    printf("%d | ", y);
    for (int x = 0; x < PIECE_X; x ++)
      printf("%c ", p.puzzle[x][y] ? '*' : ' ');
    printf("\n");
  }
  printf("--+--------\n");
  printf("%c | 0 1 2 3\n", p.name);
}
