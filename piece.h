#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "logger.h"
#include "calc.h"
#include "position.h"
#include "matrix.h"

typedef struct _Piece {
  char name;
  Position positions[PIECE_MAX_POSITION];
  unsigned int position_count;
  unsigned int puzzle[PIECE_X + 1][PIECE_Y + 1];
} Piece;

extern Piece PIECE_A;
extern Piece PIECE_B;
extern Piece PIECE_C;
extern Piece PIECE_D;
extern Piece PIECE_E;
extern Piece PIECE_F;
extern Piece PIECE_G;
extern Piece PIECE_H;
extern Piece PIECE_I;
extern Piece PIECE_J;

extern Piece* ALL_PIECES[PIECE_COUNT];
extern char ALL_PIECE_NAMES[PIECE_COUNT];

typedef int RotateDirection;
#define ROTATE_DIRECTION_0          1
#define ROTATE_DIRECTION_90         2
#define ROTATE_DIRECTION_180        3
#define ROTATE_DIRECTION_270        4
#define ROTATE_DIRECTION_MIRROR_0   -1
#define ROTATE_DIRECTION_MIRROR_90  -2
#define ROTATE_DIRECTION_MIRROR_180 -3
#define ROTATE_DIRECTION_MIRROR_270 -4
extern RotateDirection ALL_ROTATE_DIRECTIONS[PIECE_ROTATE_DIRECTION_COUNT];

Piece* piece_make(char name, unsigned int position_count, Position positions[PIECE_MAX_POSITION]);
Piece* piece_make_from_position_list(char name, unsigned int position_count, PositionListItem* list);

void piece_init_puzzle(Piece* piece);
Piece* piece_rotate(Piece* piece, RotateDirection direction);
Piece* piece_fix(Piece* piece);
Piece* piece_move(Piece* piece, Position* move);
void piece_print(Piece* piece);

#endif