#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "const.h"
#include "bool.h"
#include "logger.h"
#include "position.h"
#include "piece.h"

#define PUZZLE_POSITION_UNAVAILABLE 'x'
#define PUZZLE_POSITION_EMPTY       '0'

extern Position UNAVAILABLE[PUZZLE_UNAVAILABLE_COUNT];
extern Position MONTH[PUZZLE_MONTH_COUNT];
extern Position DATE[PUZZLE_DATE_COUNT];
extern Position WEEK[PUZZLE_WEEK_COUNT];

extern const char* UNAVAILABLE_TEXTS[PUZZLE_UNAVAILABLE_COUNT];
extern const char* MONTH_TEXTS[PUZZLE_MONTH_COUNT];
extern const char* DATE_TEXTS[PUZZLE_DATE_COUNT];
extern const char* WEEK_TEXTS[PUZZLE_WEEK_COUNT];

typedef char* Puzzle;
typedef char* PuzzleText;

Puzzle puzzle_make();
PuzzleText puzzle_text_make();

void puzzle_fill(Puzzle puzzle, Position positions[], unsigned int len, char v, Position* move);
void puzzle_text_fill(PuzzleText puzzle_text, Position positions[], unsigned int len, const char** texts, Position* move);

void print_puzzle(Puzzle puzzle);
void print_puzzle_text(PuzzleText puzzle_text);

int puzzle_positions_count_of_empty(Puzzle puzzle, Position positions[], unsigned int len, Position* move);
int puzzle_positions_count_of_available(Puzzle puzzle, Position positions[], unsigned int len, Position* move);
int puzzle_count_of_empty(Puzzle puzzle);

PositionCount* puzzle_find(Puzzle puzzle, char name);
PositionCount* puzzle_find_and_remove(Puzzle puzzle, char name);
PositionCount* puzzle_find_and_fill(Puzzle puzzle, char find_name, char fill_name);
void puzzle_clear(Puzzle puzzle);

#endif