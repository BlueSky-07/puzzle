#include "logger.h"
#include "piece.h"
#include "matrix.h"
#include "puzzle.h"
#include "binary.h"
#include "game.h"
#include <stdio.h>

void base() {
  logger_info("info");
  logger_error("error");
  logger_verbose("verbose");
  logger_success("success");
  logger_debug("debug");

  puzzle_data_test();

  print_matrix(&ROTATE_MATRIX_0);
  print_matrix(&(Matrix){
    {
      {1},
      {2},
    }, 1, 2
  });
  print_matrix(&(Matrix){
    {
      {1, 2},
    }, 2, 1
  });

  print_piece(&PIECE_C);
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_0));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_90));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_180));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_270));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_MIRROR_0));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_MIRROR_90));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_MIRROR_180));
  print_piece(rotate_piece(&PIECE_C, ROTATE_DIRECTION_MIRROR_270));

  printf("A: %s\n", positions_to_binary_string(PIECE_A.position, PIECE_A.position_count));
}

int put(Puzzle puzzle, Piece* piece, Position* move) {
  int failure = put_piece_into_puzzle(puzzle, piece, move);
  logger_info("%s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

int main() {
  set_logger_global_from_env();

  // base();

  Puzzle puzzle = make_puzzle();
  put(puzzle, &PIECE_A, &(Position){0, 1});
  put(puzzle, &PIECE_A, &(Position){1, 2});
  put(puzzle, &PIECE_B, NULL);
  put(puzzle, &PIECE_B, &(Position){1, 1});
  put(puzzle, &PIECE_C, &(Position){1, 2});

  return 0;
}