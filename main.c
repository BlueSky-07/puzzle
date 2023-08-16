#include "piece.h"
#include "matrix.h"
#include "puzzle.h"
#include "binary.h"
#include <stdio.h>

int main() {
  init_all_puzzle();
  // print_puzzle();
  // pretty_print_puzzle();

  // print_matrix(ROTATE_MATRIX_0);
  // print_matrix((Matrix){
  //   {
  //     {1},
  //     {2}
  //   }, 1, 2
  // });
  // print_matrix((Matrix){
  //   {
  //     {1, 2}
  //   }, 2, 1
  // });

  // print_piece(PIECE_C);
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_0));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_90));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_180));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_270));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_MIRROR_0));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_MIRROR_90));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_MIRROR_180));
  // print_piece(rotate_piece(PIECE_C, ROTATE_DIRECTION_MIRROR_270));

  printf("A: %s\n", binary_to_string(positions_to_binary(PIECE_A.position, PIECE_A.position_count)));
  return 0;
}