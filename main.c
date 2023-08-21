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

  Puzzle puzzle = puzzle_make();
  puzzle_fill_positions(puzzle, MONTH, PUZZLE_MONTH_COUNT, '1', NULL);
  puzzle_fill_positions(puzzle, DATE, PUZZLE_DATE_COUNT, '2', NULL);
  puzzle_fill_positions(puzzle, WEEK, PUZZLE_WEEK_COUNT, '3', NULL);
  puzzle_print(puzzle);
  free(puzzle);

  PuzzleText puzzle_text = puzzle_text_make();
  puzzle_text_fill(puzzle_text, MONTH, PUZZLE_MONTH_COUNT, MONTH_TEXTS, NULL);
  puzzle_text_fill(puzzle_text, DATE, PUZZLE_DATE_COUNT, DATE_TEXTS, NULL);
  puzzle_text_fill(puzzle_text, WEEK, PUZZLE_WEEK_COUNT, WEEK_TEXTS, NULL);
  puzzle_text_print(puzzle_text);
  free(puzzle_text);
}

void matrix_test() {
  logger_info("=======================================");
  logger_info("matrix_test:");

  matrix_print(&ROTATE_MATRIX_0);
  matrix_print(&(Matrix){
    {
      {1},
      {2},
    }, 1, 2,
  });
  matrix_print(&(Matrix){
    {
      {1, 2},
    }, 2, 1,
  });
}

void piece_data_test() {
  logger_info("=======================================");
  logger_info("piece_data_test:");

  for (int i = 0; i < PIECE_COUNT; i ++) {
    piece_print(ALL_PIECES[i]);
  }
}

void piece_rotate_test() {
  logger_info("=======================================");
  logger_info("piece_rotate_test:");

  piece_print(&PIECE_C);
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_0));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_90));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_180));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_270));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_MIRROR_0));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_MIRROR_90));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_MIRROR_180));
  piece_print(piece_rotate(&PIECE_C, ROTATE_DIRECTION_MIRROR_270));
}

void binary_test() {
  logger_info("=======================================");
  logger_info("binary_test:");

  piece_print(&PIECE_A);

  String a_string = binary_string_from_positions(PIECE_A.positions, PIECE_A.position_count);
  logger_info("binary stringify:");
  logger_info("%s", a_string);

  PositionCount* a_pc = binary_string_to_positions(a_string);
  logger_info("binary parse:");
  position_list_print(a_pc->positions);

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
  if (!failure) puzzle_print(puzzle);
}

void game_remove_test(Puzzle puzzle, char name) {
  logger_info("*******************");
  logger_info("game_remove_test:");

  int failure = game_remove_piece_from_puzzle(puzzle, name);
  logger_info("remove: %s", game_action_result_string(failure));
  if (!failure) puzzle_print(puzzle);
}

void game_test_single(Puzzle puzzle, int mode) {
  logger_info("---------------------------------------");
  logger_info("game_test_single:");

  puzzle_clear(puzzle);
  game_put_test(puzzle, &PIECE_A, position_make(0, 1), mode);
  game_put_test(puzzle, &PIECE_A, position_make(1, 2), mode);
  game_put_test(puzzle, &PIECE_B, NULL, mode);
  game_remove_test(puzzle, PIECE_B.name);
  game_put_test(puzzle, &PIECE_B, position_make(1, 1), mode);
  game_put_test(puzzle, &PIECE_C, position_make(1, 2), mode);
  game_remove_test(puzzle, PIECE_A.name);
  logger_info("is end: %d", game_is_end(puzzle));
}

void game_test() {
  logger_info("=======================================");
  logger_info("game_test:");

  Puzzle puzzle = puzzle_make();
  game_test_single(puzzle, 0);
  game_test_single(puzzle, 1);
  return;

  logger_info("puzzle: %s", puzzle);
  logger_info("puzzle stringify: %s", binary_to_string(binary_from_puzzle(puzzle)));
  logger_info("puzzle reverse stringify: %s", binary_to_string(binary_reverse(binary_from_puzzle(puzzle))));
  free(puzzle);
}

void game_piece_rotate_all_kinds_unique_test() {
  logger_info("=======================================");
  logger_info("game_piece_rotate_all_kinds_unique_test:");

  for (int i = 0; i < PIECE_COUNT; i ++) {
    Piece* piece = ALL_PIECES[i];
    Piece p = *piece;
    BinaryCount* bc = game_rotate_piece_all_kinds_unique(piece);
    logger_info("%c has %d kinds", p.name, bc->count);
    BinaryListItem* ii = bc->binaries;
    while (ii) {
      Binary binary = ii->binary;
      logger_info("%lu <=> %s", binary, binary_to_string(binary));
      PositionCount* pc = binary_to_positions(binary);
      position_list_print(pc->positions);
      free(pc);
      Piece* pp = binary_to_piece(binary, p.name);
      piece_print(pp);
      free(pp);
      ii = ii->next;
    }
    binary_count_free(bc);
  }
}

void game_piece_put_all_kinds_test() {
  logger_info("=======================================");
  logger_info("game_piece_put_all_kinds_test:");

  Puzzle puzzle = puzzle_make();
  for (int i = 0; i < PIECE_COUNT; i ++) {
    puzzle_clear(puzzle);
    Piece* piece = ALL_PIECES[i];
    Piece p = *piece;
    BinaryCount* bc = game_put_piece_all_kinds_into_puzzle(puzzle, piece);
    logger_info("%c has %d kinds", p.name, bc->count);
    BinaryListItem* ii = bc->binaries;
    while (ii) {
      Binary binary = ii->binary;
      logger_info("%lu <=> %s", binary, binary_to_string(binary));
      PositionCount* pc = binary_to_positions(binary);
      position_list_print(pc->positions);
      Puzzle piece_into_puzzle = puzzle_make();
      puzzle_fill_position_count(piece_into_puzzle, pc, piece->name, NULL);
      puzzle_print(piece_into_puzzle);
      free(pc);
      free(piece_into_puzzle);
      ii = ii->next;
    }
    binary_count_free(bc);
  }
}

int main() {
  logger_global_set_all_from_env();
  logger_info("start puzzle test");

  // logger_test();
  // puzzle_data_test();
  // matrix_test();
  // piece_data_test();
  // piece_rotate_test();
  // binary_test();
  // game_test();
  game_piece_rotate_all_kinds_unique_test();
  // game_piece_put_all_kinds_test();

  logger_info("end puzzle test");

  return 0;
}