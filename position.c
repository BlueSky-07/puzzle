#include "position.h"

int get_index(int bin, int total) {
  int i = 0, b = 1;
  while ((bin & b) ^ b) {
    b = b << 1;
    i++;
  }
  return total - i;
}

Position get_index_position(Position position, int total_row, int total_col) {
  Position result = {
      get_index(position.row, total_row),
      get_index(position.col, total_col),
  };
  return result;
}
