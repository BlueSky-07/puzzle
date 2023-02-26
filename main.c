#include "piece.h"
#include "puzzle.h"
#include <stdio.h>

int main() {
  init_all_puzzle();
  print_puzzle();
  pretty_print_puzzle();
  // print_all_pieces();
  // print_piece(PIECE_C);
  return 0;
}