#ifndef _BINARY_H_
#define _BINARY_H_

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "const.h"
#include "position.h"
#include "puzzle.h"

typedef unsigned long Binary;
typedef char* String;

Binary position_to_binary(Position* position, Position* move);
Binary positions_to_binary(Position positions[], int total, Position* move);
String binary_to_string(Binary binary);
String positions_to_binary_string(Position positions[], int total);

PositionCount* binary_to_positions(Binary binary);
Binary string_to_binary(String string);
PositionCount* binary_string_to_positions(String string);

Binary puzzle_to_binary(Puzzle puzzle);
Binary binary_reverse(Binary binary);

Bool binary_test_piece_put_into_puzzle(Binary puzzle_binary, Binary piece_binary);
Bool binary_test_piece_put_with_piece(Binary piece_binary_a, Binary piece_binary_b);
Binary binary_piece_put_into_puzzle(Binary puzzle_binary, Binary piece_binary);
Binary binary_piece_put_with_piece(Binary piece_binary_a, Binary piece_binary_b);

#endif