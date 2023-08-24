#ifndef _GAME_H_
#define _GAME_H_

#include <stdlib.h>
#include "bool.h"
#include "logger.h"
#include "piece.h"
#include "puzzle.h"
#include "position.h"
#include "binary.h"
#include "date.h"
#include "io.h"
#include "optimization.h"

typedef unsigned int GameActionResult;
#define GAME_ACTION_SUCCESS                0
#define GAME_ACTION_FAILURE                1
#define GAME_ACTION_FAILURE_HAS_PUT        2
#define GAME_ACTION_FAILURE_NOT_AVAILABLE  3
#define GAME_ACTION_FAILURE_NOT_EMPTY      4
#define GAME_ACTION_FAILURE_NOT_PUT        5

typedef struct _GameSolveListItem {
  char name;
  BinaryCount* bc;
} GameSolveListItem;

typedef struct _GameSolveResult {
  char name;
  Binary binary;
} GameSolveResult;

GameSolveListItem* game_solve_list_item_make(char name, BinaryCount* bc);
GameSolveResult* game_solve_result_make(char name, Binary binary);

void game_solve_list_free(GameSolveListItem* list);
void game_solve_result_free(GameSolveResult* result);

const char* game_action_result_string(GameActionResult result);

GameActionResult game_put_piece_into_puzzle(Puzzle puzzle, Piece* piece, Position* move);
GameActionResult game_remove_piece_from_puzzle(Puzzle puzzle, char name);
GameActionResult game_put_piece_into_puzzle_binary_mode(Puzzle puzzle, Piece* piece, Position* move);

Bool game_is_end(Puzzle puzzle);

BinaryCount* game_rotate_piece_all_kinds_unique(Piece* piece);
BinaryCount* game_put_piece_all_kinds_into_puzzle(Puzzle puzzle, Piece* piece);
BinaryCount* game_put_piece_all_kinds_all_rotate_into_puzzle(Puzzle puzzle, Piece* piece);

int game_solve_list_item_compare_asc(const void* a, const void *b);
int game_solve_list_item_compare_desc(const void* a, const void *b);

void game_solve_list_sort_asc(GameSolveListItem* list, unsigned int count);
void game_solve_list_sort_desc(GameSolveListItem* list, unsigned int count);
GameSolveListItem* game_solve_list_filter_by_puzzle_and_date(GameSolveListItem *items, Puzzle puzzle, Date* date);
Puzzle game_solve_result_to_puzzle(GameSolveResult* list, unsigned int count);

Bool game_solve_puzzle(GameSolveResult* result, Puzzle puzzle, GameSolveListItem items[], unsigned int current);
GameSolveResult* game_solve_by_date(Date* date);
GameSolveResult* game_solve_today();

void game_solve_all_puzzle(Puzzle puzzle, GameSolveListItem items[], unsigned int current);
void game_solve_all_by_date(Date* date);
void game_solve_all_today();

GameSolveListItem* game_read_pieces_data();
GameSolveListItem* game_make_pieces_data(Puzzle puzzle);

#endif