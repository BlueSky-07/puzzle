#include "puzzle.h"

Position UNAVAILABLE[6] = {
                                                  {7, 8},
                                                  {7, 7},
  {1, 1}, {2, 1}, {3, 1}, {4, 1},
};
int UNAVAILABLE_LEN = (int)sizeof(UNAVAILABLE) / (int)sizeof(Position);

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

const char* UNAVAILABLE_TEXTS[6] = {
  " x ", " x ", " x ", " x ", " x ", " x ",
};

const char* MONTH_TEXTS[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
};

const char* DATE_TEXTS[31]  = {
  "001", "002", "003", "004", "005", "006", "007",
  "008", "009", "010", "011", "012", "013", "014",
  "015", "016", "017", "018", "019", "020", "021",
  "022", "023", "024", "025", "026", "027", "028",
  "029", "030", "031",
};

const char* WEEK_TEXTS[7] = {
                       "Sun", "Mon", "Tue", "Wed",
                              "Thu", "Fri", "Sat",
};

Puzzle make_puzzle() {
  Puzzle puzzle = malloc(sizeof(unsigned int) * PUZZLE_TOTAL);
  memset(puzzle, PUZZLE_POSITION_EMPTY, PUZZLE_TOTAL);
  puzzle_fill(puzzle, UNAVAILABLE, UNAVAILABLE_LEN, PUZZLE_POSITION_UNAVAILABLE, NULL);
  return puzzle;
}

PuzzleText make_puzzle_text() {
  PuzzleText puzzle_text = malloc(sizeof(char) * PUZZLE_TOTAL * 4);
  memset(puzzle_text, ' ', PUZZLE_TOTAL);
  for (int i = 3; i < PUZZLE_TOTAL * 4; i += 4) puzzle_text[i] = '\0';
  puzzle_text_fill(puzzle_text, UNAVAILABLE, UNAVAILABLE_LEN, UNAVAILABLE_TEXTS, NULL);
  return puzzle_text;
}

void puzzle_fill(Puzzle puzzle, Position positions[], unsigned int len, char v, Position* move) {
  for (int i = 0; i < len; i++) {
    Position* pos = position_move(&positions[i], move, POSITION_MOVE_NEW);
    puzzle[pos->y * PUZZLE_X + pos->x] = v;
    free(pos);
  }
}

void puzzle_text_fill(PuzzleText puzzle_text, Position positions[], unsigned int len, const char** texts, Position* move) {
  for (int i = 0; i < len; i++) {
    Position* pos = position_move(&positions[i], move, POSITION_MOVE_NEW);
    strcpy(puzzle_text + (pos->y * PUZZLE_X + pos->x) * 4, texts[i]);
    free(pos);
  }
}

void print_puzzle(Puzzle puzzle) {
  for (int y = PUZZLE_Y; y >= 1; y--) {
    printf("%d | ", y);
    for (int x = 1; x <= PUZZLE_X; x++) {
      printf("%c ", puzzle[y * PUZZLE_X + x]);
    }
    printf("\n");
  }
  printf("--+--------------\n");
  printf("p | 1 2 3 4 5 6 7\n");
}

void print_puzzle_text(PuzzleText puzzle_text) {
  for (int y = PUZZLE_Y; y >= 1; y--) {
    printf("%d | ", y);
    for (int x = 1; x <= PUZZLE_X; x++) {
      printf("%s ", puzzle_text + (y * PUZZLE_X + x) * 4);
    }
    printf("\n");
  }
  printf("--+----------------------------\n");
  printf("P |  1   2   3   4   5   6   7\n");
}

void puzzle_data_test() {
  Puzzle puzzle = make_puzzle();
  puzzle_fill(puzzle, MONTH, MONTH_LEN, '1', NULL);
  puzzle_fill(puzzle, DATE, DATE_LEN, '2', NULL);
  puzzle_fill(puzzle, WEEK, WEEK_LEN, '3', NULL);
  print_puzzle(puzzle);
  free(puzzle);

  PuzzleText puzzle_text = make_puzzle_text();
  puzzle_text_fill(puzzle_text, MONTH, MONTH_LEN, MONTH_TEXTS, NULL);
  puzzle_text_fill(puzzle_text, DATE, DATE_LEN, DATE_TEXTS, NULL);
  puzzle_text_fill(puzzle_text, WEEK, WEEK_LEN, WEEK_TEXTS, NULL);
  print_puzzle_text(puzzle_text);
  free(puzzle_text);
}

int puzzle_positions_count_of_empty(Puzzle puzzle, Position positions[], unsigned int len, Position* move) {
  int result = 0;
  for (int i = 0; i < len; i ++) {
    Position* pos = position_move(&positions[i], move, POSITION_MOVE_NEW);
    if (!coordinate_is_ok(pos->x, pos->y)) result += 0;
    else result += puzzle[pos->y * PUZZLE_X + pos->x] == PUZZLE_POSITION_EMPTY ? 1 : 0;
    free(pos);
  }
  return result;
}

int puzzle_positions_count_of_available(Puzzle puzzle, Position positions[], unsigned int len, Position* move) {
  int result = 0;
  for (int i = 0; i < len; i ++) {
    Position* pos = position_move(&positions[i], move, POSITION_MOVE_NEW);
    if (!coordinate_is_ok(pos->x, pos->y)) result += 1;
    else result += puzzle[pos->y * PUZZLE_X + pos->x] == PUZZLE_POSITION_UNAVAILABLE ? 0 : 1;
    free(pos);
  }
  return result;
}

int puzzle_count_of_empty(Puzzle puzzle) {
  int result = 0;
  for (int i = 0; i < PUZZLE_TOTAL; i ++) {
    result += puzzle[i] == PUZZLE_POSITION_EMPTY ? 1 : 0;
  }
  return result;
}

PositionCount* puzzle_find(Puzzle puzzle, char name) {
  PositionListItem* list = make_position_list_item(NULL);
  logger_debug("puzzle_find: %c", name);
  for (int y = PUZZLE_Y; y >= 1; y--) {
    for (int x = 1; x <= PUZZLE_X; x++) {
      char c = puzzle[y * PUZZLE_X + x];
      Bool found = c == name;
      if (found) {
        logger_debug("puzzle_find, loop: %d, %d = %c => %d", x, y, c, found);
        position_list_push(list, make_position(x, y));
      }
    }
  }
  return make_position_count(list);
}

PositionCount* puzzle_find_and_remove(Puzzle puzzle, char name) {
  return puzzle_find_and_fill(puzzle, name, PUZZLE_POSITION_EMPTY);
}

PositionCount* puzzle_find_and_fill(Puzzle puzzle, char find_name, char fill_name) {
  PositionListItem* list = make_position_list_item(NULL);
  for (int y = PUZZLE_Y; y >= 1; y--) {
    for (int x = 1; x <= PUZZLE_X; x++) {
      if (puzzle[y * PUZZLE_X + x] == find_name) {
        position_list_push(list, make_position(x, y));
        puzzle[y * PUZZLE_X + x] = fill_name;
      }
    }
  }
  return make_position_count(list);
}

void puzzle_clear(Puzzle puzzle) {
  memset(puzzle, PUZZLE_POSITION_EMPTY, PUZZLE_TOTAL);
  puzzle_fill(puzzle, UNAVAILABLE, UNAVAILABLE_LEN, PUZZLE_POSITION_UNAVAILABLE, NULL);
}