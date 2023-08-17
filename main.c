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
}

void binary_test() {
  print_piece(&PIECE_A);
  String a_string = positions_to_binary_string(PIECE_A.positions, PIECE_A.position_count);
  logger_info("stringify:");
  logger_info("%s", a_string);
  PositionCount* a_pc = binary_string_to_positions(a_string);
  logger_info("parse:");
  print_position_list(a_pc->positions);

  free(a_string);
  free(a_pc);
}

void put_test(Puzzle puzzle, Piece* piece, Position* move, int mode) {
  int failure = mode == 0
    ? put_piece_into_puzzle(puzzle, piece, move)
    : put_piece_into_puzzle_binary_mode(puzzle, piece, move);
  logger_info("put: %s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

void remove_test(Puzzle puzzle, char name) {
  int failure = remove_piece_from_puzzle(puzzle, name);
  logger_info("remove: %s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

void game_test(Puzzle puzzle, int mode) {
  puzzle_clear(puzzle);
  put_test(puzzle, &PIECE_A, make_position(0, 1), mode);
  put_test(puzzle, &PIECE_A, make_position(1, 2), mode);
  put_test(puzzle, &PIECE_B, NULL, mode);
  remove_test(puzzle, PIECE_B.name);
  put_test(puzzle, &PIECE_B, make_position(1, 1), mode);
  put_test(puzzle, &PIECE_C, make_position(1, 2), mode);
  remove_test(puzzle, PIECE_A.name);
  logger_info("is end: %d", game_is_end(puzzle));
}

int main() {
  set_logger_global_from_env();

  // base_test();
  // binary_test();

  Puzzle puzzle = make_puzzle();
  game_test(puzzle, 0);
  game_test(puzzle, 1);

  // logger_info("puzzle stringify: %s", binary_to_string(puzzle_to_binary(puzzle)));
  // logger_info("puzzle reverse stringify: %s", binary_to_string(binary_reverse(puzzle_to_binary(puzzle))));
  return 0;
}