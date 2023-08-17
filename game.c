#include "game.h"

const char* game_action_result_string(GameActionResult result) {
  switch (result) {
    case GAME_ACTION_SUCCESS:
      return "SUCCESS";
    case GAME_ACTION_FAILURE:
      return "FAILURE";
    case GAME_ACTION_FAILURE_HAS_PUT:
      return "FAILURE: HAS PUT";
    case GAME_ACTION_FAILURE_NOT_AVAILABLE:
      return "FAILURE: NOT AVAILABLE";
    case GAME_ACTION_FAILURE_NOT_EMPTY:
      return "FAILURE: NOT EMPTY";
    case GAME_ACTION_FAILURE_NOT_PUT:
      return "FAILURE: NOT PUT";
    default:
      return "UNKNOWN";
  }
}

GameActionResult put_piece_into_puzzle(Puzzle puzzle, Piece* piece, Position* move) {
  Piece p = *piece;
  PositionCount* pc = puzzle_find(puzzle, p.name);
  Bool found = pc->count > 0;
  position_count_free(pc, TRUE);
  if (found)
    return GAME_ACTION_FAILURE_HAS_PUT;
  if (puzzle_positions_count_of_available(puzzle, p.positions, p.position_count, move) != p.position_count)
    return GAME_ACTION_FAILURE_NOT_AVAILABLE;
  if (puzzle_positions_count_of_empty(puzzle, p.positions, p.position_count, move) == p.position_count) {
    puzzle_fill(puzzle, p.positions, p.position_count, p.name, move);
    return GAME_ACTION_SUCCESS;
  }
  return GAME_ACTION_FAILURE_NOT_EMPTY;
}

GameActionResult put_piece_into_puzzle_binary_mode(Puzzle puzzle, Piece* piece, Position* move) {
  Piece p = *piece;
  logger_debug("put_piece_into_puzzle_binary_mode");
  logger_debug("move: %d, %d %p", (move ? move->x : 0), (move ? move->y : 0), move);
  Binary puzzle_binary = puzzle_to_binary(puzzle);
  Binary piece_binary = positions_to_binary(p.positions, p.position_count, move);
  if (logger_level_is_debug_ok()) {
    logger_debug("puzzle: %s", binary_to_string(puzzle_binary));
    logger_debug("piece: %s", binary_to_string(piece_binary));
  }
  int test = binary_test_piece_put_into_puzzle(puzzle_binary, piece_binary);
  if (!test) return GAME_ACTION_FAILURE;
  puzzle_fill(puzzle, p.positions, p.position_count, p.name, move);
  return GAME_ACTION_SUCCESS;
}

GameActionResult remove_piece_from_puzzle(Puzzle puzzle, char name) {
  PositionCount* pc = puzzle_find_and_remove(puzzle, name);
  Bool success = pc->count > 0;
  position_count_free(pc, TRUE);
  return success ? GAME_ACTION_SUCCESS : GAME_ACTION_FAILURE_NOT_PUT;
}

Bool game_is_end(Puzzle puzzle) {
  return puzzle_count_of_empty(puzzle) == END_GAME_COUNT;
}