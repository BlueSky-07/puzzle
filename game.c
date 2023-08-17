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
  if (puzzle_positions_count_of_available(puzzle, p.position, p.position_count, move) != p.position_count)
    return GAME_ACTION_FAILURE_NOT_AVAILABLE;
  if (puzzle_positions_count_of_empty(puzzle, p.position, p.position_count, move) == p.position_count) {
    puzzle_fill(puzzle, p.position, p.position_count, p.name, move);
    return GAME_ACTION_SUCCESS;
  }
  return GAME_ACTION_FAILURE_NOT_EMPTY;
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