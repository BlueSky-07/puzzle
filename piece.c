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

char ALL_PIECE_NAMES[PIECE_COUNT] = {
  'A', 'B', 'C', 'D', 'E',
  'F', 'G', 'H', 'I', 'J',
};

RotateDirection ALL_ROTATE_DIRECTIONS[PIECE_ROTATE_DIRECTION_COUNT] = {
  ROTATE_DIRECTION_0,
  ROTATE_DIRECTION_90,
  ROTATE_DIRECTION_180,
  ROTATE_DIRECTION_270,
  ROTATE_DIRECTION_MIRROR_0,
  ROTATE_DIRECTION_MIRROR_90,
  ROTATE_DIRECTION_MIRROR_180,
  ROTATE_DIRECTION_MIRROR_270,
};

Piece* piece_make(char name, unsigned int position_count, Position positions[PIECE_MAX_POSITION]) {
  Piece* piece = malloc(sizeof(Piece));
  piece->name = name;
  piece->position_count = position_count;
  for (int i = 0; i < position_count; i ++) {
    piece->positions[i].x = positions ? positions[i].x : COORDINATE_INVALID;
    piece->positions[i].y = positions ? positions[i].y : COORDINATE_INVALID;
  }
  return piece;
}

Piece* piece_make_from_position_list(char name, unsigned int position_count, PositionListItem* list) {
  if (!list) return NULL;
  Position positions[PIECE_MAX_POSITION];
  int i = 0;
  while (list && list->position && i < PIECE_MAX_POSITION) {
    positions[i].x = list->position->x;
    positions[i].y = list->position->y;
    list = list ->next;
    i++;
  }
  return piece_make(name, position_count, positions);
}

void piece_init_puzzle(Piece* piece) {
  for (int i = 0; i < (PIECE_X + 1) * (PIECE_Y + 1); i++) {
    piece->puzzle[i / (PIECE_X + 1)][i % (PIECE_X + 1)] = 0;
  }
  for (int i = 0; i < piece->position_count; i++) {
    Position p = piece->positions[i];
    piece->puzzle[p.x][p.y] = 1;
  }
}

Piece* piece_rotate(Piece* piece, RotateDirection direction) {
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

  logger_debug("piece_rotate, direction: %d, mirror: %d, matrix:", direction, mirror);
  if (logger_level_is_debug_ok()) matrix_print(&matrix);

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

    logger_debug("piece_rotate, loop: %d, %d => %d, %d", pp.x, pp.y, ip->x, ip->y);
    free(pos_fixed);
  }

  Piece* fixed_result = piece_fix(result);
  free(result);
  return fixed_result;
}

Piece* piece_fix(Piece* piece) {
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

Piece* piece_move(Piece* piece, Position* move) {
  Piece p = *piece;
  if (!move || (move->x == 0 && move->y == 0)) return piece_make(p.name, p.position_count, p.positions);

  Piece* result = piece_make(p.name, p.position_count, NULL);

  for (int i = 0; i < p.position_count; i ++) {
    Position* new_pos = position_move(&p.positions[i], move, POSITION_MOVE_NEW);

    bool ok = position_is_ok(new_pos);
    if (ok) {
      result->positions[i].x = new_pos->x;
      result->positions[i].y = new_pos->y;
    }
    free(new_pos);
    if (!ok) {
      free(result);
      return NULL;
    }
  }

  logger_debug("piece_move done:");
  if (logger_level_is_debug_ok())
    for (int i = 0; i < result->position_count; i ++) {
      position_print(&result->positions[i], LOGGER_NEW_LINE);
    }
  return result;
}

void piece_print(Piece* piece) {
  if (!piece) return;
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
