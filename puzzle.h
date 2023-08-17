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

extern Position UNAVAILABLE[6];
extern Position MONTH[12];
extern Position DATE[31];
extern Position WEEK[7];

extern const char* UNAVAILABLE_TEXTS[6];
extern const char* MONTH_TEXTS[12];
extern const char* DATE_TEXTS[31];
extern const char* WEEK_TEXTS[7];

typedef unsigned char* Puzzle;
typedef char* PuzzleText;

Puzzle make_puzzle();
PuzzleText make_puzzle_text();

void puzzle_fill(Puzzle puzzle, Position positions[], unsigned int len, char v, Position* move);
void puzzle_text_fill(PuzzleText puzzle_text, Position positions[], unsigned int len, const char** texts, Position* move);

void print_puzzle(Puzzle puzzle);
void print_puzzle_text(PuzzleText puzzle_text);

void puzzle_data_test();

int puzzle_positions_count_of_empty(Puzzle puzzle, Position positions[], unsigned int len, Position* move);
int puzzle_positions_count_of_available(Puzzle puzzle, Position positions[], unsigned int len, Position* move);
int puzzle_count_of_empty(Puzzle puzzle);

PositionCount* puzzle_find(Puzzle puzzle, char name);
PositionCount* puzzle_find_and_remove(Puzzle puzzle, char name);
PositionCount* puzzle_find_and_fill(Puzzle puzzle, char find_name, char fill_name);

#endif