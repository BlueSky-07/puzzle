#ifndef _PIECE_H_
#define _PIECE_H_

#include "position.h"

#define PIECE_ROW 4
#define PIECE_COL 4

typedef struct Piece {
  char name;
  Position position[PIECE_ROW * PIECE_COL];
  int position_count;
  int puzzle[PIECE_ROW + 1][PIECE_COL + 1];
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

void print_piece_mirror(Piece piece, int mirror);
void print_piece(Piece piece);
void print_all_pieces();

#endif