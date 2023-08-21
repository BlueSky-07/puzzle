#ifndef _GAME_H_
#define _GAME_H_

#include "bool.h"
#include "logger.h"
#include "piece.h"
#include "puzzle.h"
#include "position.h"
#include "binary.h"

typedef int GameActionResult;
#define GAME_ACTION_SUCCESS                0
#define GAME_ACTION_FAILURE                1
#define GAME_ACTION_FAILURE_HAS_PUT        2
#define GAME_ACTION_FAILURE_NOT_AVAILABLE  3
#define GAME_ACTION_FAILURE_NOT_EMPTY      4
#define GAME_ACTION_FAILURE_NOT_PUT        5

const char* game_action_result_string(GameActionResult result);

GameActionResult game_put_piece_into_puzzle(Puzzle puzzle, Piece* piece, Position* move);
GameActionResult game_remove_piece_from_puzzle(Puzzle puzzle, char name);
GameActionResult game_put_piece_into_puzzle_binary_mode(Puzzle puzzle, Piece* piece, Position* move);

Bool game_is_end(Puzzle puzzle);

BinaryCount* game_put_piece_all_kinds_into_puzzle(Puzzle puzzle, Piece* piece);

#endif