#include "puzzle.h"

Position POSITIONS_UNAVAILABLE[PUZZLE_UNAVAILABLE_COUNT] = {
                                                  {6, 7},
                                                  {6, 6},
  {0, 0}, {1, 0}, {2, 0}, {3, 0},
};

Position POSITIONS_MONTH[PUZZLE_MONTH_COUNT] = {
  {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7},
  {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6},
};

Position POSITIONS_DATE[PUZZLE_DATE_COUNT] = {
  {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5},
  {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4},
  {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3},
  {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2},
  {0, 1}, {1, 1}, {2, 1},
};

Position POSITIONS_WEEK[PUZZLE_WEEK_COUNT] = {
                           {3, 1},{4, 1}, {5, 1}, {6, 1},
                                  {4, 0}, {5, 0}, {6, 0},
};

const char* UNAVAILABLE_TEXTS[PUZZLE_UNAVAILABLE_COUNT] = {
  " x ", " x ", " x ", " x ", " x ", " x ",
};

const char* MONTH_TEXTS[PUZZLE_MONTH_COUNT] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
};

const char* DATE_TEXTS[PUZZLE_DATE_COUNT]  = {
  "001", "002", "003", "004", "005", "006", "007",
  "008", "009", "010", "011", "012", "013", "014",
  "015", "016", "017", "018", "019", "020", "021",
  "022", "023", "024", "025", "026", "027", "028",
  "029", "030", "031",
};

const char* WEEK_TEXTS[PUZZLE_WEEK_COUNT] = {
                       "Sun", "Mon", "Tue", "Wed",
                              "Thu", "Fri", "Sat",
};

Puzzle puzzle_make() {
  Puzzle puzzle = malloc(sizeof(unsigned int) * PUZZLE_TOTAL);
  memset(puzzle, PUZZLE_POSITION_EMPTY, PUZZLE_TOTAL);
  puzzle_fill_positions(puzzle, POSITIONS_UNAVAILABLE, PUZZLE_UNAVAILABLE_COUNT, PUZZLE_POSITION_UNAVAILABLE, NULL);
  return puzzle;
}

PuzzleText puzzle_text_make() {
  PuzzleText puzzle_text = malloc(sizeof(char) * PUZZLE_TOTAL * 4);
  memset(puzzle_text, ' ', PUZZLE_TOTAL);
  for (int i = 3; i < PUZZLE_TOTAL * 4; i += 4) puzzle_text[i] = '\0';
  puzzle_text_fill(puzzle_text, POSITIONS_UNAVAILABLE, PUZZLE_UNAVAILABLE_COUNT, UNAVAILABLE_TEXTS, NULL);
  return puzzle_text;
}

void puzzle_fill_positions(Puzzle puzzle, Position positions[], unsigned int len, char v, Position* move) {
  for (int i = 0; i < len; i++) {
    Position* pos = position_move(&positions[i], move, POSITION_MOVE_NEW);
    puzzle[pos->y * PUZZLE_X + pos->x] = v;
    free(pos);
  }
}

void puzzle_fill_position_count(Puzzle puzzle, PositionCount* pc, char v, Position* move) {
  if (!pc) return;
  PositionListItem* i = pc->positions;
  while (i) {
    Position* pos = position_move(i->position, move, POSITION_MOVE_NEW);
    puzzle[pos->y * PUZZLE_X + pos->x] = v;
    free(pos);
    i = i->next;
  }
}

void puzzle_text_fill(PuzzleText puzzle_text, Position positions[], unsigned int len, const char** texts, Position* move) {
  for (int i = 0; i < len; i++) {
    Position* pos = position_move(&positions[i], move, POSITION_MOVE_NEW);
    strcpy(puzzle_text + (pos->y * PUZZLE_X + pos->x) * 4, texts[i]);
    free(pos);
  }
}

void puzzle_print(Puzzle puzzle) {
  for (int y = PUZZLE_Y - 1; y >= 0; y--) {
    printf("%d | ", y);
    for (int x = 0; x < PUZZLE_X; x++) {
      printf("%c ", puzzle[y * PUZZLE_X + x]);
    }
    printf("\n");
  }
  printf("--+--------------\n");
  printf("p | 0 1 2 3 4 5 6\n");
}

void puzzle_text_print(PuzzleText puzzle_text) {
  for (int y = PUZZLE_Y - 1; y >= 0; y--) {
    printf("%d | ", y);
    for (int x = 0; x < PUZZLE_X; x++) {
      printf("%s ", puzzle_text + (y * PUZZLE_X + x) * 4);
    }
    printf("\n");
  }
  printf("--+----------------------------\n");
  printf("P |  0   1   2   3   4   5   6 \n");
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
  PositionListItem* list = position_list_item_make_empty();;
  logger_debug("puzzle_find: %c", name);
  for (int y = 0; y < PUZZLE_Y; y++) {
    for (int x = 0; x < PUZZLE_X; x++) {
      char c = puzzle[y * PUZZLE_X + x];
      Bool found = c == name;
      if (found) {
        logger_debug("puzzle_find, loop: %d, %d = %c => %d", x, y, c, found);
        position_list_push(list, position_make(x, y));
      }
    }
  }
  return position_count_make(list);
}

PositionCount* puzzle_find_and_remove(Puzzle puzzle, char name) {
  return puzzle_find_and_fill(puzzle, name, PUZZLE_POSITION_EMPTY);
}

PositionCount* puzzle_find_and_fill(Puzzle puzzle, char find_name, char fill_name) {
  PositionListItem* list = position_list_item_make_empty();;
  for (int y = 0; y < PUZZLE_Y; y++) {
    for (int x = 0; x < PUZZLE_X; x++) {
      if (puzzle[y * PUZZLE_X + x] == find_name) {
        position_list_push(list, position_make(x, y));
        puzzle[y * PUZZLE_X + x] = fill_name;
      }
    }
  }
  return position_count_make(list);
}

void puzzle_clear(Puzzle puzzle) {
  memset(puzzle, PUZZLE_POSITION_EMPTY, PUZZLE_TOTAL);
  puzzle_fill_positions(puzzle, POSITIONS_UNAVAILABLE, PUZZLE_UNAVAILABLE_COUNT, PUZZLE_POSITION_UNAVAILABLE, NULL);
}