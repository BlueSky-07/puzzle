#include "piece.h"
#include <stdio.h>

/**
 *   1 2 3 4
 * 1 x x x
 * 2 x
 * 3 x
 * 4
 */
Piece PIECE_A = {'A',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b1000, 0b0010},
                  {0b0100, 0b1000},
                  {0b0010, 0b1000}},
                 5};

/**
 *   1 2 3 4
 * 1 x x x x
 * 2
 * 3
 * 4
 */
Piece PIECE_B = {
    'B',
    {{0b1000, 0b1000}, {0b1000, 0b0100}, {0b1000, 0b0010}, {0b1000, 0b0001}},
    4};

/**
 *   1 2 3 4
 * 1 x x x x
 * 2 x
 * 3
 * 4
 */
Piece PIECE_C = {'C',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b1000, 0b0010},
                  {0b1000, 0b0001},
                  {0b0100, 0b1000}},
                 5};

/**
 *   1 2 3 4
 * 1 x x x
 * 2   x
 * 3   x
 * 4
 */
Piece PIECE_D = {'D',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b1000, 0b0010},
                  {0b0100, 0b0100},
                  {0b0010, 0b0100}},
                 5};

/**
 *   1 2 3 4
 * 1 x x x
 * 2 x
 * 3
 * 4
 */
Piece PIECE_E = {
    'E',
    {{0b1000, 0b1000}, {0b1000, 0b0100}, {0b1000, 0b0010}, {0b0100, 0b1000}},
    4};

/**
 *   1 2 3 4
 * 1 x x
 * 2   x x
 * 3
 * 4
 */
Piece PIECE_F = {
    'F',
    {{0b1000, 0b1000}, {0b1000, 0b0100}, {0b0100, 0b0100}, {0b0100, 0b0010}},
    4};

/**
 *   1 2 3 4
 * 1 x x x
 * 2     x x
 * 3
 * 4
 */
Piece PIECE_G = {'G',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b1000, 0b0010},
                  {0b0100, 0b0010},
                  {0b0100, 0b0001}},
                 5};

/**
 *   1 2 3 4
 * 1 x x
 * 2   x
 * 3   x x
 * 4
 */
Piece PIECE_H = {'H',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b0100, 0b0100},
                  {0b0010, 0b0100},
                  {0b0010, 0b0010}},
                 5};

/**
 *   1 2 3 4
 * 1 x x x
 * 2 x x
 * 3
 * 4
 */
Piece PIECE_I = {'I',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b1000, 0b0010},
                  {0b0100, 0b1000},
                  {0b0100, 0b0100}},
                 5};

/**
 *   1 2 3 4
 * 1 x x x
 * 2 x   x
 * 3
 * 4
 */
Piece PIECE_J = {'J',
                 {{0b1000, 0b1000},
                  {0b1000, 0b0100},
                  {0b1000, 0b0010},
                  {0b0100, 0b1000},
                  {0b0100, 0b0010}},
                 5};

Piece* ALL_PIECES[10] = {&PIECE_A, &PIECE_B, &PIECE_C, &PIECE_D, &PIECE_E,
                         &PIECE_F, &PIECE_G, &PIECE_H, &PIECE_I, &PIECE_J};

void print_piece_mirror(Piece piece, int mirror) {
  for (int i = 0; i < piece.position_count; i++) {
    Position p = get_index_position(piece.position[i], PIECE_ROW, PIECE_COL);
    piece.puzzle[p.row][p.col] = 1;
  }

  printf("%c%d| 1 2 3 4\n", mirror ? '-' : '+', 1);
  printf("--+--------\n");
  for (int r = 1; r <= PIECE_ROW; r++) {
    printf("%d | ", r);
    for (int c = 1; c <= PIECE_COL; c++) {
      printf("%c ",
             (mirror ? piece.puzzle[r][PIECE_COL - c + 1] : piece.puzzle[r][c])
                 ? piece.name
                 : ' ');
    }
    printf("\n");
  }

  printf("%c%d| 1 2 3 4\n", mirror ? '-' : '+', 2);
  printf("--+--------\n");
  for (int c = 1; c <= PIECE_COL; c++) {
    printf("%d | ", c);
    for (int r = 1; r <= PIECE_ROW; r++) {
      printf("%c ", (mirror ? piece.puzzle[PIECE_ROW - r + 1][PIECE_COL - c + 1]
                            : piece.puzzle[PIECE_ROW - r + 1][c])
                        ? piece.name
                        : ' ');
    }
    printf("\n");
  }

  printf("%c%d| 1 2 3 4\n", mirror ? '-' : '+', 3);
  printf("--+--------\n");
  for (int r = 1; r <= PIECE_ROW; r++) {
    printf("%d | ", r);
    for (int c = 1; c <= PIECE_COL; c++) {
      printf("%c ",
             (mirror ? piece.puzzle[PIECE_ROW - r + 1][c]
                     : piece.puzzle[PIECE_ROW - r + 1][PIECE_COL - c + 1])
                 ? piece.name
                 : ' ');
    }
    printf("\n");
  }

  printf("%c%d| 1 2 3 4\n", mirror ? '-' : '+', 4);
  printf("--+--------\n");
  for (int c = 1; c <= PIECE_COL; c++) {
    printf("%d | ", c);
    for (int r = 1; r <= PIECE_ROW; r++) {
      printf("%c ",
             (mirror ? piece.puzzle[r][c] : piece.puzzle[r][PIECE_COL - c + 1])
                 ? piece.name
                 : ' ');
    }
    printf("\n");
  }
}

void print_piece(Piece piece) {
  print_piece_mirror(piece, 0);
  print_piece_mirror(piece, 1);
}

void print_all_pieces() {
  for (int i = 0; i < (int)sizeof(ALL_PIECES) / (int)sizeof(&ALL_PIECES[0]);
       i++) {
    print_piece(*ALL_PIECES[i]);
  }
}