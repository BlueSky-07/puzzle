#include "binary.h"

Binary position_to_binary(Position* position) {
  Position p = *position;
  Binary result = 1 << (PUZZLE_Y * (p.y - 1)) << (p.x - 1);
  logger_debug("position_to_binary: %d, %d => %lu / %s", p.x, p.y, result, binary_to_string(result));
  return result;
}

Binary positions_to_binary(Position positions[], int total) {
  Binary result = 0;
  for (int i = 0; i < total; i ++) {
    result += position_to_binary(&positions[i]);
  }
  logger_debug("positions_to_binary: %lu / %s", result, binary_to_string(result));
  return result;
}

String binary_to_string(Binary binary) {
  char* result = malloc(sizeof(char) * (BINARY_TOTAL + 1));

  for (int i = 0; i < BINARY_TOTAL; i ++) {
    int v = binary >> i & 1;
    result[i] = v ? '1' : '0';
  }
  result[PUZZLE_TOTAL] = '\0';

  return result;
}

String positions_to_binary_string(Position positions[], int total) {
  return binary_to_string(positions_to_binary(positions, total));
}

PositionCount* binary_to_positions(Binary binary) {
  PositionListItem* list = make_position_list_item(NULL);

  logger_debug("binary_to_positions: %lu / %s", binary, binary_to_string(binary));
  for (int i = 0; i < BINARY_TOTAL; i ++) {
    int v = binary >> i & 1;
    if (!v) continue;
    int x = i % PUZZLE_Y + 1;
    int y = i / PUZZLE_Y + 1;
    logger_debug("binary_to_positions: %d => %d, %d", i, x, y);
    position_list_push(list, make_position(x, y));
  }

  PositionCount* pc = make_position_count(list);
  if (logger_level_is_debug_ok()) print_position_list(pc->positions);
  return pc;
}

Binary string_to_binary(String string) {
  Binary result = 0;
  for (int i = BINARY_TOTAL - 1; i >= 0; i --) {
    result <<= 1;
    result += string[i] == '1';
  }
  return result;
}

PositionCount* binary_string_to_positions(String string) {
  return binary_to_positions(string_to_binary(string));
}