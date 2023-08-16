#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "position.h"

#define PUZZLE_X 7
#define PUZZLE_Y 8
#define PUZZLE_TOTAL (PUZZLE_X + 1) * (PUZZLE_Y + 1)

extern Position MONTH[12];
extern Position DATE[31];
extern Position WEEK[7];

extern char* MONTH_TEXTS[12];
extern char* DATE_TEXTS[31];
extern char* WEEK_TEXTS[7];

typedef unsigned char* Puzzle;
typedef char* PuzzleText;

Puzzle make_puzzle();
PuzzleText make_puzzle_text();

void puzzle_fill(Puzzle puzzle, Position positions[], unsigned int len, char v);
void puzzle_text_fill(PuzzleText puzzle_text, Position positions[], unsigned int len, char** texts);

void print_puzzle(Puzzle puzzle);
void print_puzzle_text(PuzzleText puzzle_text);

void puzzle_data_test();

#endif