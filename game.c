#include "game.h"

GameSolveListItem* game_solve_list_item_make(char name, BinaryCount* bc) {
  GameSolveListItem* result = malloc(sizeof(GameSolveListItem));
  result->name = name;
  result->bc = bc;
  return result;
}

GameSolveResult* game_solve_result_make(char name, Binary binary) {
  GameSolveResult* result = malloc(sizeof(GameSolveResult));
  result->name = name;
  result->binary = binary;
  return result;
}

void game_solve_list_free(GameSolveListItem* list) {
  if (!list) return;
  binary_count_free(list->bc);
  free(list);
}

void game_solve_result_free(GameSolveResult* result) {
  if (!result) return;
  free(result);
}

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

int game_solve_list_item_compare_asc(const void* a, const void *b) {
  GameSolveListItem* item_a = (GameSolveListItem*)a;
  GameSolveListItem* item_b = (GameSolveListItem*)b;
  unsigned int count_a = item_a->bc->count;
  unsigned int count_b = item_b->bc->count;
  return count_a > count_b ? 1 : -1;
}

int game_solve_list_item_compare_desc(const void* a, const void *b) {
  return game_solve_list_item_compare_asc(b, a);
}

void game_solve_list_sort_asc(GameSolveListItem* list, unsigned int count) {
  qsort(
    list, count, sizeof(GameSolveListItem),
    game_solve_list_item_compare_asc
  );
}

void game_solve_list_sort_desc(GameSolveListItem* list, unsigned int count) {
  qsort(
    list, count, sizeof(GameSolveListItem),
    game_solve_list_item_compare_desc
  );
}

GameSolveListItem* game_solve_list_filter_by_puzzle(GameSolveListItem *items, Puzzle puzzle) {
  GameSolveListItem* result = malloc(sizeof(GameSolveListItem) * PIECE_COUNT);
  Binary puzzle_binary = binary_from_puzzle(puzzle);
  for (int i = 0; i < PIECE_COUNT; i ++) {
    GameSolveListItem game_solve_item = items[i];
    BinaryCount* piece_bc = game_solve_item.bc;
    BinaryListItem* optimized_piece_list = optimization_piece_forbidden_any_binary_list_filter(piece_bc->binaries, game_solve_item.name);
    BinaryListItem* piece_filtered = binary_list_filter_pieces_by_puzzle(optimized_piece_list, puzzle_binary);
    BinaryCount* piece_bc_filtered = binary_count_make(piece_filtered);

    if (logger_level_is_success_ok()) {
      BinaryCount* optimized_piece_bc = binary_count_make(optimized_piece_list);
      logger_success("game_solve_list_filter_by_puzzle %c: original: %d, optimize: %d, filter_by_puzzle: %d", game_solve_item.name, piece_bc->count, optimized_piece_bc->count, piece_bc_filtered->count);
      free(optimized_piece_bc);
    }

    result[i] = *game_solve_list_item_make(game_solve_item.name, piece_bc_filtered);
    logger_debug("game_solve_list_filter_by_puzzle: %c %d => %d", game_solve_item.name, piece_bc->count, piece_bc_filtered->count);
  }
  return result;
}

Puzzle game_solve_result_to_puzzle(GameSolveResult* list, unsigned int count) {
  Puzzle puzzle = puzzle_make();
  for (int i = 0; i < count; i ++) {
    GameSolveResult item = list[i];
    logger_verbose("game_solve_result_to_puzzle %c: %llu <=> %s", item.name, item.binary, binary_to_string(item.binary));

    puzzle_fill_position_count(
      puzzle,
      binary_to_positions(item.binary),
      item.name,
      NULL
    );
  }
  return puzzle;
}

Bool game_solve_puzzle(GameSolveResult* result, Puzzle puzzle, GameSolveListItem items[], unsigned int current) {
  unsigned int rest_count = PIECE_COUNT - current;
  if (rest_count == 0) {
    if (logger_level_is_debug_ok()) puzzle_print(puzzle);
    return TRUE;
  }
  if (current == 0) game_solve_list_sort_asc(&items[current], rest_count);

  Binary puzzle_binary = binary_from_puzzle(puzzle);
  GameSolveListItem game_solve_item = items[current];
  BinaryCount* piece_bc = game_solve_item.bc;
  BinaryListItem* piece_filtered = binary_list_filter_pieces_by_puzzle(piece_bc->binaries, puzzle_binary);
  if (!piece_filtered) return FALSE;
  BinaryListItem* piece_i = piece_filtered;
  while (piece_i) {
    Binary piece_binary = piece_i->binary;
    if (piece_binary != BINARY_INVALID) {
      PositionCount* piece_pc = binary_to_positions(piece_binary);
      puzzle_fill_position_count(puzzle, piece_pc, game_solve_item.name, NULL);
      Bool success = game_solve_puzzle(result, puzzle, items, current + 1);

      if (success) {
        result[current].name = game_solve_item.name;
        result[current].binary = piece_binary;

        position_count_free(piece_pc, TRUE);
        binary_list_free(piece_filtered);

        return TRUE;
      }

      puzzle_fill_position_count(puzzle, piece_pc, PUZZLE_POSITION_EMPTY, NULL); // revert
      position_count_free(piece_pc, TRUE);
    }
    piece_i = piece_i->next;
  }
  binary_list_free(piece_filtered);

  return FALSE;
}

GameSolveResult* game_solve_by_date(Date* date) {
  Puzzle puzzle = puzzle_make();
  puzzle_fill_date(puzzle, date, PUZZLE_POSITION_DISABLED);

  GameSolveListItem* items = game_read_pieces_data();
  GameSolveListItem* optimized_items = game_solve_list_filter_by_puzzle(items, puzzle);
  game_solve_list_free(items);

  GameSolveResult* result = malloc(sizeof(GameSolveResult) * PIECE_COUNT);

  Bool success = game_solve_puzzle(result, puzzle, optimized_items, 0);

  game_solve_list_free(optimized_items);
  free(puzzle);

  return success ? result : NULL;
}

GameSolveResult* game_solve_today() {
  Date* today = date_get_today();
  GameSolveResult* result = game_solve_by_date(today);
  free(today);
  return result;
}

void game_solve_all_puzzle(Puzzle puzzle, GameSolveListItem items[], unsigned int current) {
  unsigned int rest_count = PIECE_COUNT - current;
  if (rest_count == 0) {
    char* puzzle_string = puzzle_to_string(puzzle);
    printf("%s\n", puzzle_string);
    if (logger_level_is_verbose_ok()) puzzle_print(puzzle_from_string(puzzle_string));
    return;
  }
  if (current == 0) game_solve_list_sort_asc(&items[current], rest_count);

  Binary puzzle_binary = binary_from_puzzle(puzzle);
  GameSolveListItem game_solve_item = items[current];
  BinaryCount* piece_bc = game_solve_item.bc;
  BinaryListItem* piece_filtered = binary_list_filter_pieces_by_puzzle(piece_bc->binaries, puzzle_binary);
  if (!piece_filtered) return;
  BinaryListItem* piece_i = piece_filtered;
  while (piece_i) {
    Binary piece_binary = piece_i->binary;
    if (piece_binary != BINARY_INVALID) {
      PositionCount* piece_pc = binary_to_positions(piece_binary);
      puzzle_fill_position_count(puzzle, piece_pc, game_solve_item.name, NULL);
      game_solve_all_puzzle(puzzle, items, current + 1);

      puzzle_fill_position_count(puzzle, piece_pc, PUZZLE_POSITION_EMPTY, NULL); // revert
      position_count_free(piece_pc, TRUE);
    }
    piece_i = piece_i->next;
  }
  binary_list_free(piece_filtered);
}

void game_solve_all_by_date(Date* date) {
  Puzzle puzzle = puzzle_make();
  puzzle_fill_date(puzzle, date, PUZZLE_POSITION_DISABLED);

  GameSolveListItem* items = game_read_pieces_data();
  GameSolveListItem* optimized_items = game_solve_list_filter_by_puzzle(items, puzzle);
  game_solve_list_free(items);

  game_solve_all_puzzle(puzzle, optimized_items, 0);

  game_solve_list_free(optimized_items);
  free(puzzle);
}

void game_solve_all_today() {
  Date* today = date_get_today();
  game_solve_all_by_date(today);
  free(today);
}

GameSolveListItem* game_read_pieces_data() {
  GameSolveListItem* items = malloc(sizeof(GameSolveListItem) * PIECE_COUNT);
  char* filename = malloc(sizeof(char) * (strlen(IO_STORE_ROOT_PATH) + 13));
  for (int i = 0; i < PIECE_COUNT; i ++) {
    filename[0] = '\0';
    char piece_name = ALL_PIECE_NAMES[i];
    strcpy(filename, IO_STORE_ROOT_PATH);
    strcat(filename, (char[]){piece_name, '\0'});
    strcat(filename, ".piece.txt");
    BinaryListItem* list = binary_list_item_make_empty();
    IoActionResult io_result = io_read_binary_list(filename, list);
    if (io_result != IO_SUCCESS) {
      logger_error("read pieces data of %c error: %s, (%d) %s", piece_name, filename, io_result, io_action_result_string(io_result));
      binary_list_free(list);
      free(filename);
      return game_make_pieces_data(NULL);
    }

    if (logger_level_is_debug_ok()) {
      BinaryListItem* ii = list;
      while(ii) {
        break; // hide read data;
        Binary binary = ii->binary;
        logger_info("%llu <=> %s", binary, binary_to_string(binary));
        ii = ii->next;
        PositionCount* pc = binary_to_positions(binary);
        position_list_print(pc->positions);
        Puzzle piece_into_puzzle = puzzle_make();
        puzzle_fill_position_count(piece_into_puzzle, pc, piece_name, NULL);
        puzzle_print(piece_into_puzzle);
        position_count_free(pc, TRUE);
        free(piece_into_puzzle);
      }
    }

    BinaryCount* bc = binary_count_make(list);
    logger_debug("%c read %d kinds", piece_name, bc->count);
    items[i] = *game_solve_list_item_make(piece_name, bc);
  }
  logger_success("read pieces data done");
  free(filename);

  return items;
}

GameSolveListItem* game_make_pieces_data(Puzzle puzzle) {
  GameSolveListItem* items = malloc(sizeof(GameSolveListItem) * PIECE_COUNT);
  Puzzle puzzle_final = puzzle ? puzzle : puzzle_make();
  for (int i = 0; i < PIECE_COUNT; i ++) {
    Piece* piece = ALL_PIECES[i];
    BinaryCount* bc = game_put_piece_all_kinds_all_rotate_into_puzzle(puzzle_final, piece);
    items[i] = *game_solve_list_item_make(piece->name, bc);
  }

  if (!puzzle) free(puzzle_final);
  return items;
}