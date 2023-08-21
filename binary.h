#ifndef _BINARY_H_
#define _BINARY_H_

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "const.h"
#include "bool.h"
#include "position.h"
#include "puzzle.h"

typedef unsigned long Binary;
typedef char* String;

typedef struct _BinaryListItem {
  Binary binary;
  struct _BinaryListItem* next;
} BinaryListItem;

typedef struct _BinaryCount {
  BinaryListItem* binaries;
  unsigned int count;
} BinaryCount;

BinaryListItem* binary_list_item_make(Binary binary);
BinaryListItem* binary_list_item_make_empty();
BinaryCount* binary_count_make(BinaryListItem* list);

Bool binary_list_push(BinaryListItem* list, Binary binary);
Bool binary_list_push_unique(BinaryListItem* list, Binary binary);
Bool binary_list_push_list_unique(BinaryListItem* list, BinaryListItem* addition);
Bool binary_list_find(BinaryListItem* list, Binary binary);

void binary_list_free(BinaryListItem* list);
void binary_count_free(BinaryCount* bc);

Binary binary_from_position(Position* position, Position* move);
Binary binary_from_positions(Position positions[], int total, Position* move);
Binary binary_from_puzzle(Puzzle puzzle);
Binary binary_from_string(String string);
Binary binary_from_binary_list(BinaryListItem* list);

PositionCount* binary_to_positions(Binary binary);
Piece* binary_to_piece(Binary binary, char name);
Piece* binary_list_to_piece(BinaryListItem* list, char name);
String binary_to_string(Binary binary);
PositionCount* binary_list_to_positions(BinaryListItem* list);

String binary_string_from_positions(Position positions[], int total);
PositionCount* binary_string_to_positions(String string);

Binary binary_reverse(Binary binary);

Bool binary_test_piece_put_into_puzzle(Binary puzzle_binary, Binary piece_binary);
Bool binary_test_piece_put_with_piece(Binary piece_binary_a, Binary piece_binary_b);
Binary binary_piece_put_into_puzzle(Binary puzzle_binary, Binary piece_binary);
Binary binary_piece_put_with_piece(Binary piece_binary_a, Binary piece_binary_b);

#endif