#include "binary.h"

Binary position_to_binary(Position position) {
  Binary result = 1 << (PUZZLE_Y * (position.y - 1)) << (position.x - 1);
  logger_debug("position_to_binary: %d, %d => %lu / %s", position.x, position.y, result, binary_to_string(result));
  return result;
}

Binary positions_to_binary(Position positions[], int total) {
  Binary result = 0;
  for (int i = 0; i < total; i ++) {
    result += position_to_binary(positions[i]);
  }
  logger_debug("positions_to_binary: %lu / %s", result, binary_to_string(result));
  return result;
}

char* binary_to_string(Binary bin) {
  char* result = malloc(sizeof(char) * (PUZZLE_TOTAL + 1));

  for (int i = 0; i < PUZZLE_TOTAL; i ++) {
    int v = bin >> i & 1;
    result[i] = v ? '1' : '0';
  }
  result[PUZZLE_TOTAL] = '\0';

  return result;
}

char* positions_to_binary_string(Position positions[], int total) {
  return binary_to_string(positions_to_binary(positions, total));
}