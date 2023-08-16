#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "position.h"

#define PUZZLE_X 7
#define PUZZLE_Y 8
#define PUZZLE_TOTAL PUZZLE_X * PUZZLE_Y

extern Position MONTH[12];
extern Position DATE[31];
extern Position WEEK[7];

extern char* MONTH_TEXT[12];
extern char* DATE_TEXT[31];
extern char* WEEK_TEXT[7];

extern unsigned int puzzle[PUZZLE_X + 1][PUZZLE_Y + 1];
extern char pretty_puzzle[PUZZLE_X + 1][PUZZLE_Y + 1][4];

void init_puzzle(Position positions[], unsigned int v, unsigned int len);

void init_pretty_puzzle_array();
void init_pretty_puzzle(Position positions[], char** texts, unsigned int len);

void print_puzzle();
void pretty_print_puzzle();

void init_all_puzzle();

#endif