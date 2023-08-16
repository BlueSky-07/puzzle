#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "position.h"
#include "matrix.h"

#define PIECE_X 4
#define PIECE_Y 4
#define PIECE_MAX_POSITION 5

typedef struct _Piece {
  char name;
  Position position[PIECE_MAX_POSITION];
  unsigned position_count;
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

extern Piece* ALL_PIECES[10];

typedef int RotateDirection;
#define ROTATE_DIRECTION_0          1
#define ROTATE_DIRECTION_90         2
#define ROTATE_DIRECTION_180        3
#define ROTATE_DIRECTION_270        4
#define ROTATE_DIRECTION_MIRROR_0   -1
#define ROTATE_DIRECTION_MIRROR_90  -2
#define ROTATE_DIRECTION_MIRROR_180 -3
#define ROTATE_DIRECTION_MIRROR_270 -4

void piece_init_puzzle(Piece* piece);
Piece* rotate_piece(Piece* piece, RotateDirection direction);
Piece* fix_piece(Piece* piece);
void print_piece(Piece* piece);

#endif