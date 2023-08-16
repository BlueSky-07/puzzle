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
  if (puzzle_has_piece(puzzle, p.name))
    return GAME_ACTION_FAILURE_HAS_PUT;
  if (puzzle_positions_count_of_available(puzzle, p.position, p.position_count, move) != p.position_count)
    return GAME_ACTION_FAILURE_NOT_AVAILABLE;
  if (puzzle_positions_count_of_empty(puzzle, p.position, p.position_count, move) == p.position_count) {
    puzzle_fill(puzzle, p.position, p.position_count, p.name, move);
    return GAME_ACTION_SUCCESS;
  }
  return GAME_ACTION_FAILURE_NOT_EMPTY;
}

GameActionResult remove_piece_from_puzzle(Puzzle puzzle, Piece* piece, Position* move) {
  Piece p = *piece;
  if (!puzzle_has_piece(puzzle, p.name))
    return GAME_ACTION_FAILURE_NOT_PUT;
  if (puzzle_positions_count_of_available(puzzle, p.position, p.position_count, move) != p.position_count)
    return GAME_ACTION_FAILURE_NOT_AVAILABLE;
  if (puzzle_positions_count_of_piece(puzzle, piece, move) == p.position_count) {
    puzzle_fill(puzzle, p.position, p.position_count, PUZZLE_POSITION_EMPTY, move);
    return GAME_ACTION_SUCCESS;
  }
  return GAME_ACTION_FAILURE_NOT_FULL;
}