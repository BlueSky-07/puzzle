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

GameActionResult game_put_piece_into_puzzle(Puzzle puzzle, Piece* piece, Position* move) {
  Piece p = *piece;
  PositionCount* pc = puzzle_find(puzzle, p.name);
  Bool found = pc->count > 0;
  position_count_free(pc, TRUE);
  if (found)
    return GAME_ACTION_FAILURE_HAS_PUT;
  if (puzzle_positions_count_of_available(puzzle, p.positions, p.position_count, move) != p.position_count)
    return GAME_ACTION_FAILURE_NOT_AVAILABLE;
  if (puzzle_positions_count_of_empty(puzzle, p.positions, p.position_count, move) == p.position_count) {
    puzzle_fill_positions(puzzle, p.positions, p.position_count, p.name, move);
    return GAME_ACTION_SUCCESS;
  }
  return GAME_ACTION_FAILURE_NOT_EMPTY;
}

GameActionResult game_put_piece_into_puzzle_binary_mode(Puzzle puzzle, Piece* piece, Position* move) {
  Piece p = *piece;
  logger_debug("game_put_piece_into_puzzle_binary_mode");
  if (move && (move->x != 0 || move->y != 0))
    logger_debug("move: %d, %d", move->x, move->y);
  Binary puzzle_binary = binary_from_puzzle(puzzle);
  Binary piece_binary = binary_from_positions(p.positions, p.position_count, move);
  if (logger_level_is_debug_ok()) {
    logger_debug("puzzle: %s", binary_to_string(puzzle_binary));
    logger_debug("piece: %s", binary_to_string(piece_binary));
  }
  int test = binary_test_piece_put_into_puzzle(puzzle_binary, piece_binary);
  if (!test) return GAME_ACTION_FAILURE;
  puzzle_fill_positions(puzzle, p.positions, p.position_count, p.name, move);
  return GAME_ACTION_SUCCESS;
}

GameActionResult game_remove_piece_from_puzzle(Puzzle puzzle, char name) {
  PositionCount* pc = puzzle_find_and_remove(puzzle, name);
  Bool success = pc->count > 0;
  position_count_free(pc, TRUE);
  return success ? GAME_ACTION_SUCCESS : GAME_ACTION_FAILURE_NOT_PUT;
}

Bool game_is_end(Puzzle puzzle) {
  return puzzle_count_of_empty(puzzle) == GAME_IS_END_REST_COUNT;
}

BinaryCount* game_rotate_piece_all_kinds_unique(Piece* piece) {
  BinaryListItem* list = binary_list_item_make_empty();
  for (int i = 0; i < PIECE_ROTATE_DIRECTION_COUNT; i ++) {
    RotateDirection rotate = ALL_ROTATE_DIRECTIONS[i];
    Piece* new_piece = piece_rotate(piece, rotate);
    Binary new_piece_binary = binary_from_positions(new_piece->positions, new_piece->position_count, NULL);
    binary_list_push_unique(list, new_piece_binary);
    free(new_piece);
  }
  return binary_count_make(list);
}

BinaryCount* game_put_piece_all_kinds_into_puzzle(Puzzle puzzle, Piece* piece) {
  BinaryListItem* list = binary_list_item_make_empty();
  Binary binary_puzzle = binary_from_puzzle(puzzle);
  for (Coordinate y = 0; y < PUZZLE_Y; y ++) {
    for (Coordinate x = 0; x < PUZZLE_X; x ++) {
      Position* move = position_make(x, y);
      Piece* new_piece = piece_move(piece, move);
      free(move);

      if (!new_piece) {
        logger_debug("game_put_piece_all_kinds_into_puzzle loop, [failure] move out of puzzle: %d, %d", x, y);
        continue;
      }

      Binary new_piece_binary = binary_from_positions(new_piece->positions, new_piece->position_count, NULL);
      if (!binary_test_piece_put_into_puzzle(binary_puzzle, new_piece_binary)) {
        logger_debug("game_put_piece_all_kinds_into_puzzle loop, [failure] put into puzzle: %d, %d", x, y);
        free(new_piece);
        continue;
      }

      logger_debug("game_put_piece_all_kinds_into_puzzle loop, [success] put into puzzle: %d, %d", x, y);
      if (logger_level_is_debug_ok()) {
        Puzzle puzzle = puzzle_make();
        puzzle_fill_positions(puzzle, new_piece->positions, piece->position_count, piece->name, NULL);
        puzzle_print(puzzle);
        free(puzzle);
      }

      binary_list_push_unique(list, new_piece_binary);
      free(new_piece);
    }
  }
  return binary_count_make(list);
}

BinaryCount* game_put_piece_all_kinds_all_rotate_into_puzzle(Puzzle puzzle, Piece* piece) {
  BinaryListItem* list = binary_list_item_make_empty();
  BinaryCount* rotate_list = game_rotate_piece_all_kinds_unique(piece);
  BinaryListItem* i = rotate_list->binaries;
  while (i) {
    Piece* new_piece = binary_to_piece(i->binary, piece->name);
    BinaryCount* piece_list = game_put_piece_all_kinds_into_puzzle(puzzle, new_piece);
    binary_list_push_list_unique(list, piece_list->binaries);
    free(new_piece);
    binary_count_free(piece_list);
    i = i->next;
  }
  return binary_count_make(list);
}