#include "logger.h"
#include "piece.h"
#include "matrix.h"
#include "puzzle.h"
#include "binary.h"
#include "game.h"
#include <stdio.h>

void base_test() {
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

  logger_info("A: %s\n", positions_to_binary_string(PIECE_A.position, PIECE_A.position_count));
}

void put_test(Puzzle puzzle, Piece* piece, Position* move) {
  int failure = put_piece_into_puzzle(puzzle, piece, move);
  logger_info("put: %s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

void remove_test(Puzzle puzzle, char name) {
  int failure = remove_piece_from_puzzle(puzzle, name);
  logger_info("remove: %s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

int main() {
  set_logger_global_from_env();

  // base_test();

  Puzzle puzzle = make_puzzle();
  put_test(puzzle, &PIECE_A, make_position(0, 1));
  put_test(puzzle, &PIECE_A, make_position(1, 2));
  put_test(puzzle, &PIECE_B, NULL);
  remove_test(puzzle, PIECE_B.name);
  put_test(puzzle, &PIECE_B, make_position(1, 1));
  put_test(puzzle, &PIECE_C, make_position(1, 2));
  remove_test(puzzle, PIECE_A.name);
  logger_info("is end: %d", game_is_end(puzzle));

  return 0;
}