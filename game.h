#ifndef _GAME_H_
#define _GAME_H_

#include "piece.h"
#include "puzzle.h"
#include "position.h"

typedef int GameActionResult;
#define GAME_ACTION_SUCCESS                0
#define GAME_ACTION_FAILURE                1
#define GAME_ACTION_FAILURE_HAS_PUT        2
#define GAME_ACTION_FAILURE_NOT_AVAILABLE  3
#define GAME_ACTION_FAILURE_NOT_EMPTY      4
#define GAME_ACTION_FAILURE_NOT_PUT        5
#define GAME_ACTION_FAILURE_NOT_FULL       6

const char* game_action_result_string(GameActionResult result);

GameActionResult put_piece_into_puzzle(Puzzle puzzle, Piece* piece, Position* move);
GameActionResult remove_piece_from_puzzle(Puzzle puzzle, Piece* piece, Position* move);

#endif