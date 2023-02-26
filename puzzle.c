#include "puzzle.h"
#include <stdio.h>
#include <string.h>

Position MONTH[12] = {
    {0b10000000, 0b1000000}, {0b10000000, 0b0100000}, {0b10000000, 0b0010000},
    {0b10000000, 0b0001000}, {0b10000000, 0b0000100}, {0b10000000, 0b0000010},
    {0b01000000, 0b1000000}, {0b01000000, 0b0100000}, {0b01000000, 0b0010000},
    {0b01000000, 0b0001000}, {0b01000000, 0b0000100}, {0b01000000, 0b0000010}};
int MONTH_LEN = (int)sizeof(MONTH) / (int)sizeof(Position);

Position DATE[31] = {
    {0b00100000, 0b1000000}, {0b00100000, 0b0100000}, {0b00100000, 0b0010000},
    {0b00100000, 0b0001000}, {0b00100000, 0b0000100}, {0b00100000, 0b0000010},
    {0b00100000, 0b0000001}, {0b00010000, 0b1000000}, {0b00010000, 0b0100000},
    {0b00010000, 0b0010000}, {0b00010000, 0b0001000}, {0b00010000, 0b0000100},
    {0b00010000, 0b0000010}, {0b00010000, 0b0000001}, {0b00001000, 0b1000000},
    {0b00001000, 0b0100000}, {0b00001000, 0b0010000}, {0b00001000, 0b0001000},
    {0b00001000, 0b0000100}, {0b00001000, 0b0000010}, {0b00001000, 0b0000001},
    {0b00000100, 0b1000000}, {0b00000100, 0b0100000}, {0b00000100, 0b0010000},
    {0b00000100, 0b0001000}, {0b00000100, 0b0000100}, {0b00000100, 0b0000010},
    {0b00000100, 0b0000001}, {0b00000010, 0b1000000}, {0b00000010, 0b0100000},
    {0b00000010, 0b0010000}};
int DATE_LEN = (int)sizeof(DATE) / (int)sizeof(Position);

Position WEEK[7] = {{0b00000010, 0b0001000}, {0b00000010, 0b0000100},
                    {0b00000010, 0b0000010}, {0b00000010, 0b0000001},
                    {0b00000001, 0b0000100}, {0b00000001, 0b0000010},
                    {0b00000001, 0b0000001}};
int WEEK_LEN = (int)sizeof(WEEK) / (int)sizeof(Position);

char* MONTH_TEXT[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

char* DATE_TEXT[31] = {"001", "002", "003", "004", "005", "006", "007", "008",
                       "009", "010", "011", "012", "013", "014", "015", "016",
                       "017", "018", "019", "020", "021", "022", "023", "024",
                       "025", "026", "027", "028", "029", "030", "031"};

char* WEEK_TEXT[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int puzzle[ROW + 1][COL + 1];
char pretty_puzzle[ROW + 1][COL + 1][4];

void init_puzzle(Position T[], int t, int len) {
  for (int i = 0; i < len; i++) {
    Position p = get_index_position(T[i], ROW, COL);
    puzzle[p.row][p.col] = t;
  }
}

void init_pretty_puzzle_array() {
  for (int r = 1; r <= ROW; r++) {
    for (int c = 1; c <= COL; c++) {
      strcpy(pretty_puzzle[r][c], "   ");
    }
  }
}

void init_pretty_puzzle(Position T[], char** texts, int len) {
  for (int i = 0; i < len; i++) {
    Position p = get_index_position(T[i], ROW, COL);
    strcpy(pretty_puzzle[p.row][p.col], texts[i]);
  }
}

void print_puzzle() {
  printf("  | 1 2 3 4 5 6 7\n");
  printf("--+-------------\n");
  for (int r = 1; r <= ROW; r++) {
    printf("%d | ", r);
    for (int c = 1; c <= COL; c++) {
      printf("%d ", puzzle[r][c]);
    }
    printf("\n");
  }
}

void pretty_print_puzzle() {
  printf("  |  1   2   3   4   5   6   7\n");
  printf("--+----------------------------\n");
  for (int r = 1; r <= ROW; r++) {
    printf("%d | ", r);
    for (int c = 1; c <= COL; c++) {
      printf("%s ", pretty_puzzle[r][c]);
    }
    printf("\n");
  }
}

void init_all_puzzle() {
  init_puzzle(MONTH, 1, MONTH_LEN);
  init_puzzle(DATE, 2, DATE_LEN);
  init_puzzle(WEEK, 3, WEEK_LEN);
  init_pretty_puzzle_array();
  init_pretty_puzzle(MONTH, MONTH_TEXT, MONTH_LEN);
  init_pretty_puzzle(DATE, DATE_TEXT, DATE_LEN);
  init_pretty_puzzle(WEEK, WEEK_TEXT, WEEK_LEN);
}
