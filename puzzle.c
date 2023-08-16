#include "puzzle.h"

Position MONTH[12] = {
  {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8},
  {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7},
};
int MONTH_LEN = (int)sizeof(MONTH) / (int)sizeof(Position);

Position DATE[31] = {
  {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6},
  {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5},
  {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4},
  {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3},
  {1, 2}, {2, 2}, {3, 2},
};
int DATE_LEN = (int)sizeof(DATE) / (int)sizeof(Position);

Position WEEK[7] = {
                          {4, 2}, {5, 2}, {6, 2}, {7, 2},
                                  {5, 1}, {6, 1}, {7, 1},
};
int WEEK_LEN = (int)sizeof(WEEK) / (int)sizeof(Position);

char* MONTH_TEXT[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

char* DATE_TEXT[31] = {"001", "002", "003", "004", "005", "006", "007", "008",
                       "009", "010", "011", "012", "013", "014", "015", "016",
                       "017", "018", "019", "020", "021", "022", "023", "024",
                       "025", "026", "027", "028", "029", "030", "031"};

char* WEEK_TEXT[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

unsigned int puzzle[PUZZLE_X + 1][PUZZLE_Y + 1];
char pretty_puzzle[PUZZLE_X + 1][PUZZLE_Y + 1][4];

void init_puzzle(Position positions[], unsigned int v, unsigned int len) {
  for (int i = 0; i < len; i++) {
    Position p = positions[i];
    puzzle[p.x][p.y] = v;
  }
}

void init_pretty_puzzle_array() {
  for (int x = 1; x <= PUZZLE_X; x++) {
    for (int y = 1; y <= PUZZLE_Y; y++) {
      strcpy(pretty_puzzle[x][y], "   ");
    }
  }
}

void init_pretty_puzzle(Position positions[], char** texts, unsigned int len) {
  for (int i = 0; i < len; i++) {
    Position p = positions[i];
    strcpy(pretty_puzzle[p.x][p.y], texts[i]);
  }
}

void print_puzzle() {
  for (int y = PUZZLE_Y; y >= 1; y--) {
    printf("%d | ", y);
    for (int x = 1; x <= PUZZLE_X; x++) {
      printf("%d ", puzzle[x][y]);
    }
    printf("\n");
  }
  printf("--+--------------\n");
  printf("P | 1 2 3 4 5 6 7\n");
}

void pretty_print_puzzle() {
  for (int y = PUZZLE_Y; y >= 1; y--) {
    printf("%d | ", y);
    for (int x = 1; x <= PUZZLE_X; x++) {
      printf("%s ", pretty_puzzle[x][y]);
    }
    printf("\n");
  }
  printf("--+----------------------------\n");
  printf("P |  1   2   3   4   5   6   7\n");
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
