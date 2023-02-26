#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "position.h"

#define ROW 8
#define COL 7

extern Position MONTH[12];
extern Position DATE[31];
extern Position WEEK[7];

extern char* MONTH_TEXT[12];
extern char* DATE_TEXT[31];
extern char* WEEK_TEXT[7];

extern int puzzle[ROW + 1][COL + 1];
extern char pretty_puzzle[ROW + 1][COL + 1][4];

void init_puzzle(Position T[], int t, int len);

void init_pretty_puzzle_array();
void init_pretty_puzzle(Position T[], char** texts, int len);

void print_puzzle();
void pretty_print_puzzle();

void init_all_puzzle();

#endif