#include "binary.h"

BinaryListItem* binary_list_item_make(Binary binary) {
  BinaryListItem* bl = malloc(sizeof(BinaryListItem));
  bl->binary = binary;
  bl->next = NULL;
  return bl;
}

BinaryListItem* binary_list_item_make_empty() {
  return binary_list_item_make(BINARY_INVALID);
}

BinaryCount* binary_count_make(BinaryListItem* list) {
  BinaryCount* bc = malloc(sizeof(BinaryCount));
  bc->binaries = list;
  int count = 0;
  while (list) {
    count += list->binary ? 1 : 0;
    list = list->next;
  }
  bc->count = count;
  return bc;
}

Bool binary_list_push(BinaryListItem* list, Binary binary) {
  if (!list) return FALSE;
  while (list->next) list = list->next;
  if (list->binary == BINARY_INVALID) list->binary = binary;
  else list->next = binary_list_item_make(binary);
  return TRUE;
}

Bool binary_list_push_unique(BinaryListItem* list, Binary binary) {
  if (!list) return FALSE;
  while (list->next && list->binary != binary) list = list->next;
  if (list->binary == binary) return FALSE;
  if (list->binary == BINARY_INVALID) list->binary = binary;
  else list->next = binary_list_item_make(binary);
  return TRUE;
}

Bool binary_list_find(BinaryListItem* list, Binary binary) {
  if (!list) return FALSE;
  while (list->next) list = list->next;
  return list->binary == binary;
}

void binary_list_free(BinaryListItem* list) {
  if (list->next)
    binary_list_free(list->next);

  free(list);
}

void binary_count_free(BinaryCount* bc) {
  if (!bc) return;
  binary_list_free(bc->binaries);
  free(bc);
}

Binary binary_from_position(Position* position, Position* move) {
  Position p = *position;
  Position* pos = position_move(position, move, POSITION_MOVE_NEW);
  Binary result = 1l << (pos->y * PUZZLE_X + pos->x);

  if (logger_level_is_debug_ok()) {
    if (!move || (move->x == 0 && move->y == 0))
      logger_debug("binary_from_position: %d, %d <=> %lu <=> %s", pos->x, pos->y, result, binary_to_string(result));
    else
      logger_debug("binary_from_position: %d, %d => %d, %d <=> %lu <=> %s", p.x, p.y, pos->x, pos->y, result, binary_to_string(result));
  }

  free(pos);
  return result;
}

Binary binary_from_positions(Position positions[], int total, Position* move) {
  Binary result = 0;
  for (int i = 0; i < total; i ++)
    result += binary_from_position(&positions[i], move);

  if (logger_level_is_debug_ok())
    logger_debug("binary_from_positions: %lu <=> %s", result, binary_to_string(result));

  return result;
}

String binary_to_string(Binary binary) {
  unsigned int len = BINARY_TOTAL + 1;
  char* result = malloc(sizeof(char) * len);

  for (int i = 0; i < BINARY_TOTAL; i ++) {
    int v = binary >> i & 1;
    result[i] = v ? '1' : '0';
  }
  result[len - 1] = '\0';

  // logger_debug("binary_to_string: %lu => %s", binary, result);

  return result;
}

String binary_string_from_positions(Position positions[], int total) {
  return binary_to_string(binary_from_positions(positions, total, NULL));
}

PositionCount* binary_to_positions(Binary binary) {
  PositionListItem* list = position_list_item_make_empty();

  if (logger_level_is_debug_ok())
    logger_debug("binary_to_positions binary: %lu / %s", binary, binary_to_string(binary));

  for (int i = 0; i < BINARY_TOTAL; i ++) {
    int v = binary >> i & 1;
    if (!v) continue;
    int x = i % PUZZLE_X;
    int y = i / PUZZLE_X;
    logger_debug("binary_to_positions loop: %d => %d, %d", i, x, y);
    position_list_push(list, position_make(x, y));
  }

  PositionCount* pc = position_count_make(list);
  if (logger_level_is_debug_ok()) position_list_print(pc->positions);
  return pc;
}

Binary binary_from_string(String string) {
  Binary result = 0;
  for (int i = BINARY_TOTAL - 1; i >= 0; i --) {
    result <<= 1;
    result += string[i] == '1';
  }
  return result;
}

PositionCount* binary_string_to_positions(String string) {
  return binary_to_positions(binary_from_string(string));
}

Piece* binary_to_piece(Binary binary, char name) {
  if (binary == BINARY_INVALID) return NULL;
  PositionCount* pc = binary_to_positions(binary);
  return piece_make_from_position_list(name, pc->count, pc->positions);
}

Piece* binary_list_to_piece(BinaryListItem* list, char name) {
  return binary_to_piece(binary_from_binary_list(list), name);
}

Binary binary_from_puzzle(Puzzle puzzle) {
  Binary result = 0;
  for (int y = PUZZLE_Y - 1; y >= 0; y--) {
    for (int x = PUZZLE_X - 1; x >= 0; x--) {
      result <<= 1;
      result += puzzle[y * PUZZLE_X + x] == PUZZLE_POSITION_EMPTY ? 0 : 1;
    }
  }
  return result;
}

Binary binary_from_binary_list(BinaryListItem* list) {
  if (!list) return BINARY_INVALID;
  Binary sum = 0;
  while (list) {
    if (list->binary != BINARY_INVALID)
      sum = binary_piece_put_with_piece(sum, list->binary);
    list = list->next;
  }
  return sum;
}

PositionCount* binary_list_to_positions(BinaryListItem* list) {
  return binary_to_positions(binary_from_binary_list(list));
}

Binary binary_reverse(Binary binary) {
  return ~binary;
}

Bool binary_test_piece_put_into_puzzle(Binary puzzle_binary, Binary piece_binary) {
  return (binary_reverse(puzzle_binary) & piece_binary) == piece_binary;
}

Bool binary_test_piece_put_with_piece(Binary piece_binary_a, Binary piece_binary_b) {
  return (piece_binary_a | piece_binary_b) == (piece_binary_a + piece_binary_b);
}

Binary binary_piece_put_into_puzzle(Binary puzzle_binary, Binary piece_binary) {
  return puzzle_binary | piece_binary;
}

Binary binary_piece_put_with_piece(Binary piece_binary_a, Binary piece_binary_b) {
  return piece_binary_a | piece_binary_b; // same as piece_binary_a + piece_binary_b
}
