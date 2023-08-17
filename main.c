#include "logger.h"
#include "const.h"
#include "piece.h"
#include "matrix.h"
#include "puzzle.h"
#include "binary.h"
#include "game.h"
#include <stdio.h>

void logger_test() {
  logger_info("=======================================");
  logger_info("logger_test:");

  logger_info("info");
  logger_error("error");
  logger_verbose("verbose");
  logger_success("success");
  logger_debug("debug");
}

void puzzle_data_test() {
  logger_info("=======================================");
  logger_info("puzzle_data_test:");

  Puzzle puzzle = make_puzzle();
  puzzle_fill(puzzle, MONTH, PUZZLE_MONTH_COUNT, '1', NULL);
  puzzle_fill(puzzle, DATE, PUZZLE_DATE_COUNT, '2', NULL);
  puzzle_fill(puzzle, WEEK, PUZZLE_WEEK_COUNT, '3', NULL);
  print_puzzle(puzzle);
  free(puzzle);

  PuzzleText puzzle_text = make_puzzle_text();
  puzzle_text_fill(puzzle_text, MONTH, PUZZLE_MONTH_COUNT, MONTH_TEXTS, NULL);
  puzzle_text_fill(puzzle_text, DATE, PUZZLE_DATE_COUNT, DATE_TEXTS, NULL);
  puzzle_text_fill(puzzle_text, WEEK, PUZZLE_WEEK_COUNT, WEEK_TEXTS, NULL);
  print_puzzle_text(puzzle_text);
  free(puzzle_text);
}

void matrix_test() {
  logger_info("=======================================");
  logger_info("matrix_test:");

  print_matrix(&ROTATE_MATRIX_0);
  print_matrix(&(Matrix){
    {
      {1},
      {2},
    }, 1, 2,
  });
  print_matrix(&(Matrix){
    {
      {1, 2},
    }, 2, 1,
  });
}

void piece_data_test() {
  logger_info("=======================================");
  logger_info("piece_data_test:");

  for (int i = 0; i < PIECE_COUNT; i ++) {
    print_piece(ALL_PIECES[i]);
  }
}

void piece_rotate_test() {
  logger_info("=======================================");
  logger_info("piece_rotate_test:");

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
  logger_info("=======================================");
  logger_info("binary_test:");

  print_piece(&PIECE_A);

  String a_string = positions_to_binary_string(PIECE_A.positions, PIECE_A.position_count);
  logger_info("binary stringify:");
  logger_info("%s", a_string);

  PositionCount* a_pc = binary_string_to_positions(a_string);
  logger_info("binary parse:");
  print_position_list(a_pc->positions);

  free(a_string);
  free(a_pc);
}

void game_put_test(Puzzle puzzle, Piece* piece, Position* move, int mode) {
  logger_info("*******************");
  logger_info("game_put_test:");

  int failure = mode == 0
    ? game_put_piece_into_puzzle(puzzle, piece, move)
    : game_put_piece_into_puzzle_binary_mode(puzzle, piece, move);
  logger_info("put: %s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

void game_remove_test(Puzzle puzzle, char name) {
  logger_info("*******************");
  logger_info("game_remove_test:");

  int failure = game_remove_piece_from_puzzle(puzzle, name);
  logger_info("remove: %s", game_action_result_string(failure));
  if (!failure) print_puzzle(puzzle);
}

void game_test_single(Puzzle puzzle, int mode) {
  logger_info("---------------------------------------");
  logger_info("game_test_single:");

  puzzle_clear(puzzle);
  game_put_test(puzzle, &PIECE_A, make_position(0, 1), mode);
  game_put_test(puzzle, &PIECE_A, make_position(1, 2), mode);
  game_put_test(puzzle, &PIECE_B, NULL, mode);
  game_remove_test(puzzle, PIECE_B.name);
  game_put_test(puzzle, &PIECE_B, make_position(1, 1), mode);
  game_put_test(puzzle, &PIECE_C, make_position(1, 2), mode);
  game_remove_test(puzzle, PIECE_A.name);
  logger_info("is end: %d", game_is_end(puzzle));
}

void game_test() {
  logger_info("=======================================");
  logger_info("game_test:");

  Puzzle puzzle = make_puzzle();
  game_test_single(puzzle, 0);
  game_test_single(puzzle, 1);
  return;

  logger_info("puzzle: %s", puzzle);
  logger_info("puzzle stringify: %s", binary_to_string(puzzle_to_binary(puzzle)));
  logger_info("puzzle reverse stringify: %s", binary_to_string(binary_reverse(puzzle_to_binary(puzzle))));
  free(puzzle);
}

int main() {
  set_logger_global_from_env();

  logger_test();
  puzzle_data_test();
  matrix_test();
  piece_data_test();
  piece_rotate_test();
  binary_test();
  game_test();

  return 0;
}