#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <string.h>
#include "piece.h"
#include "binary.h"
#include "game.h"

extern char* IO_STORE_ROOT_PATH;

typedef unsigned int IoActionResult;
#define IO_SUCCESS           0
#define IO_FAILURE           1
#define IO_FAILURE_NOT_FOUND 2


IoActionResult io_write_binary(Binary binary, const char* path);
IoActionResult io_read_binary(const char* path, Binary* binary);
IoActionResult io_write_binary_list(BinaryListItem* list, const char* path);
IoActionResult io_read_binary_list(const char* path, BinaryListItem* list);

IoActionResult io_write_piece(Piece* piece);
IoActionResult io_write_piece_list(BinaryListItem* list, char name);
IoActionResult io_write_piece_all_kinds(Piece* piece, Puzzle puzzle);

#endif