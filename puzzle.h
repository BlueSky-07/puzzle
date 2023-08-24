#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "const.h"
#include "texts.h"
#include "bool.h"
#include "logger.h"
#include "position.h"
#include "piece.h"
#include "date.h"

#define PUZZLE_POSITION_UNAVAILABLE 'x'
#define PUZZLE_POSITION_EMPTY       '0'
#define PUZZLE_POSITION_DISABLED    '1'

extern Position POSITIONS_UNAVAILABLE[PUZZLE_UNAVAILABLE_COUNT];
extern Position POSITIONS_MONTH[PUZZLE_MONTH_COUNT];
extern Position POSITIONS_DATE[PUZZLE_DATE_COUNT];
extern Position POSITIONS_WEEK[PUZZLE_WEEK_COUNT];

typedef char* Puzzle;
typedef char* PuzzleText;

Puzzle puzzle_make();
PuzzleText puzzle_text_make();

PuzzleText puzzle_text_make_from_puzzle(Puzzle puzzle);

void puzzle_fill_positions(Puzzle puzzle, Position positions[], unsigned int len, char v, Position* move);
void puzzle_fill_position_count(Puzzle puzzle, PositionCount* pc, char v, Position* move);
void puzzle_fill_date(Puzzle puzzle, Date* date, char v);
void puzzle_text_fill(PuzzleText puzzle_text, Position positions[], unsigned int len, const char** texts, Position* move);

void puzzle_print(Puzzle puzzle);
void puzzle_text_print(PuzzleText puzzle_text);

char* puzzle_to_string(Puzzle puzzle);
Puzzle puzzle_from_string(char* puzzle_string);

int puzzle_positions_count_of_empty(Puzzle puzzle, Position positions[], unsigned int len, Position* move);
int puzzle_positions_count_of_available(Puzzle puzzle, Position positions[], unsigned int len, Position* move);
int puzzle_count_of_empty(Puzzle puzzle);

PositionCount* puzzle_find(Puzzle puzzle, char name);
PositionCount* puzzle_find_and_remove(Puzzle puzzle, char name);
PositionCount* puzzle_find_and_fill(Puzzle puzzle, char find_name, char fill_name);
void puzzle_clear(Puzzle puzzle);

#endif