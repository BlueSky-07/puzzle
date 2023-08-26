#include "optimization.h"

Position PIECE_A_FORBIDDEN_ANY[PIECE_A_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION] = {
  {
    {0, 5}, {1, 5}, {2, 5}, {2, 6}, {2, 7},
  },
  {
    {3, 5}, {4, 5}, {5, 5}, {3, 6}, {3, 7},
  },
  {
    {4, 5}, {5, 5}, {6, 5}, {4, 6}, {4, 7},
  },
  {
    {2, 1}, {2, 2}, {2, 3}, {1, 3}, {0, 3},
  },
  {
    {4, 0}, {4, 1}, {4, 2}, {5, 2}, {6, 2},
  },
};

Position PIECE_C_FORBIDDEN_ANY[PIECE_C_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION] = {
  {
    {0, 6}, {1, 6}, {2, 6}, {3, 6}, {3, 7},
  },
  {
    {2, 6}, {3, 6}, {4, 6}, {5, 6}, {2, 7},
  },
  {
    {0, 4}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
  },
  {
    {0, 4}, {1, 1}, {1, 2}, {1, 3}, {1, 4},
  },
  {
    {0, 2}, {1, 2}, {2, 2}, {3, 2}, {3, 1},
  },
  {
    {3, 1}, {4, 1}, {5, 1}, {6, 1}, {6, 0},
  },
  {
    {5, 0}, {5, 1}, {5, 2}, {5, 3}, {6, 3},
  },
};

Position PIECE_D_FORBIDDEN_ANY[PIECE_D_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION] = {
  {
    {0, 5}, {1, 5}, {2, 5}, {1, 6}, {1, 7},
  },
  {
    {0, 6}, {1, 6}, {2, 6}, {2, 5}, {2, 7},
  },
  {
    {3, 6}, {4, 6}, {5, 6}, {3, 5}, {3, 7},
  },
  {
    {3, 5}, {4, 5}, {5, 5}, {4, 6}, {4, 7},
  },
  {
    {4, 3}, {5, 3}, {6, 3}, {5, 4}, {5, 5},
  },
  {
    {0, 3}, {1, 3}, {2, 3}, {1, 2}, {1, 1},
  },
  {
    {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 3},
  },
  {
    {4, 2}, {5, 2}, {6, 2}, {5, 1}, {5, 0},
  },
  {
    {4, 1}, {5, 1}, {6, 1}, {4, 0}, {4, 2},
  },
  {
    {4, 1}, {5, 1}, {6, 1}, {6, 0}, {6, 2},
  },
};

Position PIECE_E_FORBIDDEN_ANY[PIECE_E_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION] = {
  {
    {0, 5}, {1, 5}, {1, 6}, {1, 7},
  },
  {
    {0, 6}, {1, 6}, {2, 6}, {2, 7},
  },
  {
    {4, 5}, {4, 6}, {4, 7}, {5, 5},
  },
  {
    {3, 6}, {4, 6}, {5, 6}, {3, 7},
  },
  {
    {5, 3}, {5, 4}, {5, 5}, {6, 3},
  },
  {
    {0, 2}, {1, 2}, {2, 2}, {2, 1},
  },
  {
    {1, 1}, {1, 2}, {1, 3}, {0, 3},
  },
  {
    {4, 1}, {5, 1}, {6, 1}, {4, 0},
  },
  {
    {5, 0}, {5, 1}, {5, 2}, {6, 2},
  },
  {
    {4, 1}, {5, 1}, {6, 1}, {6, 0},
  },
};

Position PIECE_G_FORBIDDEN_ANY[PIECE_G_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION] = {
  {
    {0, 6}, {1, 6}, {2, 6}, {2, 7}, {3, 7},
  },
  {
    {0, 4}, {0, 5}, {1, 5}, {1, 6}, {1, 7},
  },
  {
    {2, 7}, {3, 7}, {3, 6}, {4, 6}, {5, 6},
  },
  {
    {4, 7}, {4, 6}, {4, 5}, {5, 5}, {5, 4},
  },
  {
    {5, 5}, {5, 4}, {5, 3}, {6, 3}, {6, 2},
  },
  {
    {0, 2}, {1, 2}, {2, 2}, {2, 1}, {3, 1},
  },
  {
    {0, 4}, {0, 3}, {1, 3}, {1, 2}, {1, 1},
  },
  {
    {5, 0}, {5, 1}, {5, 2}, {6, 2}, {6, 3},
  },
};

Position PIECE_H_FORBIDDEN_ANY[PIECE_H_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION] = {
  {
    {0, 5}, {1, 5}, {1, 6}, {1, 7}, {2, 7},
  },
  {
    {0, 6}, {1, 6}, {2, 6}, {2, 7}, {0, 5},
  },
  {
    {4, 5}, {4, 6}, {4, 7}, {5, 5}, {3, 7},
  },
  {
    {3, 6}, {4, 6}, {5, 6}, {3, 7}, {5, 5},
  },
  {
    {5, 3}, {5, 4}, {5, 5}, {6, 3}, {4, 5},
  },
  {
    {0, 2}, {1, 2}, {2, 2}, {2, 1}, {0, 3},
  },
  {
    {1, 1}, {1, 2}, {1, 3}, {0, 3}, {2, 1},
  },
  {
    {4, 1}, {5, 1}, {6, 1}, {4, 0}, {6, 2},
  },
  {
    {5, 0}, {5, 1}, {5, 2}, {6, 2}, {4, 0},
  },
  {
    {4, 1}, {5, 1}, {6, 1}, {6, 0}, {4, 2},
  },
};


OptimizationForbiddenCaseItem PIECE_C_FORBIDDEN_CASE[PIECE_C_FORBIDDEN_CASE_COUNT] = {
  {
    &(Position){6, 5}, // 7
    {
      {5, 7}, {5, 6}, {5, 5}, {5, 4}, {6, 4},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {2, 1}, {3, 1}, {4, 1}, {5, 1}, {5, 0},
    },
  },
};

OptimizationForbiddenCaseItem PIECE_F_FORBIDDEN_CASE[PIECE_F_FORBIDDEN_CASE_COUNT] = {
  {
    &(Position){0, 7}, // Jan
    {
      {0, 5}, {0, 6}, {1, 6}, {1, 7},
    },
  },
  {
    &(Position){0, 7}, // Jan
    {
      {0, 6}, {1, 6}, {1, 7}, {2, 7},
    },
  },
  {
    &(Position){5, 7}, // Jun
    {
      {3, 7}, {4, 7}, {4, 6}, {5, 6},
    },
  },
  {
    &(Position){5, 7}, // Jun
    {
      {4, 7}, {4, 6}, {5, 6}, {5, 5},
    },
  },
  {
    &(Position){6, 5}, // 7
    {
      {5, 5}, {5, 4}, {6, 4}, {6, 3},
    },
  },
  {
    &(Position){6, 5}, // 7
    {
      {4, 5}, {5, 5}, {5, 4}, {6, 4},
    },
  },
  {
    &(Position){0, 1}, // 29
    {
      {0, 3}, {0, 2}, {1, 2}, {1, 1},
    },
  },
  {
    &(Position){0, 1}, // 29
    {
      {0, 2}, {1, 2}, {1, 1}, {2, 1},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {4, 2}, {4, 1}, {5, 1}, {5, 0},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {4, 1}, {5, 1}, {5, 0}, {6, 0},
    },
  },
  {
    &(Position){6, 0}, // Sat
    {
      {4, 0}, {5, 0}, {5, 1}, {6, 1},
    },
  },
  {
    &(Position){6, 0}, // Sat
    {
      {5, 0}, {5, 1}, {6, 1}, {6, 2},
    },
  },
};

OptimizationForbiddenCaseItem PIECE_G_FORBIDDEN_CASE[PIECE_G_FORBIDDEN_CASE_COUNT] = {
  {
    &(Position){0, 7}, // Jan
    {
      {0, 5}, {0, 6}, {1, 6}, {1, 7}, {0, 4},
    },
  },
  {
    &(Position){0, 7}, // Jan
    {
      {0, 6}, {1, 6}, {1, 7}, {2, 7}, {3, 7},
    },
  },
  {
    &(Position){5, 7}, // Jun
    {
      {3, 7}, {4, 7}, {4, 6}, {5, 6}, {2, 7},
    },
  },
  {
    &(Position){5, 7}, // Jun
    {
      {4, 7}, {4, 6}, {5, 6}, {5, 5}, {5, 4},
    },
  },
  {
    &(Position){6, 5}, // 7
    {
      {5, 5}, {5, 4}, {6, 4}, {6, 3}, {5, 6},
    },
  },
  {
    &(Position){6, 5}, // 7
    {
      {4, 5}, {5, 5}, {5, 4}, {6, 4}, {3, 5},
    },
  },
  {
    &(Position){0, 1}, // 29
    {
      {0, 3}, {0, 2}, {1, 2}, {1, 1}, {0, 4},
    },
  },
  {
    &(Position){0, 1}, // 29
    {
      {0, 2}, {1, 2}, {1, 1}, {2, 1}, {3, 1},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {4, 2}, {4, 1}, {5, 1}, {5, 0}, {4, 3},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {4, 1}, {5, 1}, {5, 0}, {6, 0}, {3, 1},
    },
  },
  {
    &(Position){6, 0}, // Sat
    {
      {5, 0}, {5, 1}, {6, 1}, {6, 2}, {6, 3},
    },
  },
};

OptimizationForbiddenCaseItem PIECE_I_FORBIDDEN_CASE[PIECE_I_FORBIDDEN_CASE_COUNT] = {
  {
    &(Position){0, 7}, // Jan
    {
      {0, 5}, {0, 6}, {1, 5}, {1, 6}, {1, 7},
    },
  },
  {
    &(Position){0, 7}, // Jan
    {
      {0, 6}, {1, 6}, {2, 6}, {1, 7}, {2, 7},
    },
  },
  {
    &(Position){5, 7}, // Jun
    {
      {3, 6}, {4, 6}, {5, 6}, {3, 7}, {4, 7},
    },
  },
  {
    &(Position){5, 7}, // Jun
    {
      {4, 7}, {4, 6}, {4, 5}, {5, 6}, {5, 5},
    },
  },
  {
    &(Position){6, 5}, // 7
    {
      {5, 5}, {5, 4}, {5, 3}, {6, 4}, {6, 3},
    },
  },
  {
    &(Position){6, 5}, // 7
    {
      {4, 5}, {5, 5}, {4, 4}, {5, 4}, {6, 4},
    },
  },
  {
    &(Position){0, 1}, // 29
    {
      {0, 2}, {1, 2}, {2, 2}, {1, 1}, {2, 1},
    },
  },
  {
    &(Position){0, 1}, // 29
    {
      {0, 3}, {0, 2}, {1, 3}, {1, 2}, {1, 1},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {4, 2}, {4, 1}, {5, 2}, {5, 1}, {5, 0},
    },
  },
  {
    &(Position){4, 0}, // Thu
    {
      {4, 1}, {5, 1}, {6, 1}, {5, 0}, {6, 0},
    },
  },
  {
    &(Position){6, 0}, // Sat
    {
      {4, 1}, {5, 1}, {6, 1}, {5, 0}, {4, 0},
    },
  },
  {
    &(Position){6, 0}, // Sat
    {
      {6, 2}, {6, 1}, {5, 2}, {5, 1}, {5, 0},
    },
  },
};

OptimizationForbiddenCaseItem PIECE_J_FORBIDDEN_CASE[PIECE_J_FORBIDDEN_CASE_COUNT] = {
  {
    &(Position){0, 6}, // Jul
    {
      {0, 5}, {1, 5}, {1, 6}, {1, 7}, {0, 7},
    },
  },
  {
    &(Position){1, 7}, // Feb
    {
      {0, 7}, {0, 6}, {1, 6}, {2, 6}, {2, 7},
    },
  },
  {
    &(Position){2, 7}, // Mar
    {
      {1, 7}, {1, 6}, {2, 6}, {3, 6}, {3, 7},
    },
  },
  {
    &(Position){3, 7}, // Apr
    {
      {2, 7}, {2, 6}, {3, 6}, {4, 6}, {4, 7},
    },
  },
  {
    &(Position){4, 7}, // May
    {
      {3, 7}, {3, 6}, {4, 6}, {5, 6}, {5, 7},
    },
  },
  {
    &(Position){5, 6}, // Dec
    {
      {5, 7}, {4, 7}, {4, 6}, {4, 5}, {5, 5},
    },
  },
  {
    &(Position){6, 4}, // 14
    {
      {6, 5}, {5, 5}, {5, 4}, {5, 3}, {6, 3},
    },
  },
  {
    &(Position){6, 3}, // 21
    {
      {6, 4}, {5, 4}, {5, 3}, {5, 2}, {6, 2},
    },
  },
  {
    &(Position){6, 2}, // 28
    {
      {6, 3}, {5, 3}, {5, 2}, {5, 1}, {6, 1},
    },
  },
  {
    &(Position){2, 1}, // 31
    {
      {1, 1}, {1, 2}, {2, 2}, {3, 2}, {3, 1},
    },
  },
  {
    &(Position){1, 1}, // 30
    {
      {0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1},
    },
  },
  {
    &(Position){0, 2}, // 22
    {
      {0, 1}, {1, 1}, {1, 2}, {1, 3}, {0, 3},
    },
  },
  {
    &(Position){0, 3}, // 15
    {
      {0, 2}, {1, 2}, {1, 3}, {1, 4}, {0, 4},
    },
  },
  {
    &(Position){0, 4}, // 8
    {
      {0, 3}, {1, 3}, {1, 4}, {1, 5}, {0, 5},
    },
  },
  {
    &(Position){0, 5}, // 1
    {
      {0, 4}, {1, 4}, {1, 5}, {1, 6}, {0, 6},
    },
  },
  {
    &(Position){6, 1}, // Wed
    {
      {6, 2}, {5, 2}, {5, 1}, {5, 0}, {6, 0},
    },
  },
  {
    &(Position){5, 0}, // Fri
    {
      {4, 0}, {4, 1}, {5, 1}, {6, 1}, {6, 0},
    },
  },
  {
    &(Position){4, 1}, // Mon
    {
      {4, 2}, {5, 2}, {5, 1}, {5, 0}, {4, 0},
    },
  },
  {
    &(Position){3, 1}, // Sun
    {
      {2, 1}, {2, 2}, {3, 2}, {4, 2}, {4, 1},
    },
  },
};

void optimization_piece_forbidden_any_print(Position forbidden_any[][PIECE_MAX_POSITION], unsigned int count, unsigned int piece_position_count, char name) {
  Puzzle puzzle = puzzle_make();

  for (int i = 0; i < count; i ++) {
    puzzle_fill_positions(puzzle, forbidden_any[i], piece_position_count, name, NULL);
    puzzle_print(puzzle);
    puzzle_fill_positions(puzzle, forbidden_any[i], piece_position_count, PUZZLE_POSITION_EMPTY, NULL);
  }

  free(puzzle);
}

void optimization_piece_forbidden_case_print(OptimizationForbiddenCaseItem* items, unsigned int count, unsigned int piece_position_count, char name) {
  Puzzle puzzle = puzzle_make();

  for (int i = 0; i < count; i ++) {
    OptimizationForbiddenCaseItem ii = items[i];
    puzzle_fill_positions(puzzle, ii.positions, piece_position_count, name, NULL);
    puzzle_fill_positions(puzzle, ii.condition, 1, PUZZLE_POSITION_DISABLED, NULL);
    puzzle_print(puzzle);
    puzzle_fill_positions(puzzle, ii.positions, piece_position_count, PUZZLE_POSITION_EMPTY, NULL);
    puzzle_fill_positions(puzzle, ii.condition, 1, PUZZLE_POSITION_EMPTY, NULL);
  }

  free(puzzle);
}

void optimization_data_print() {
  optimization_piece_forbidden_any_print(PIECE_A_FORBIDDEN_ANY, PIECE_A_FORBIDDEN_ANY_COUNT, PIECE_A.position_count, PIECE_A.name);
  optimization_piece_forbidden_any_print(PIECE_C_FORBIDDEN_ANY, PIECE_C_FORBIDDEN_ANY_COUNT, PIECE_C.position_count, PIECE_C.name);
  optimization_piece_forbidden_any_print(PIECE_D_FORBIDDEN_ANY, PIECE_D_FORBIDDEN_ANY_COUNT, PIECE_D.position_count, PIECE_D.name);
  optimization_piece_forbidden_any_print(PIECE_E_FORBIDDEN_ANY, PIECE_E_FORBIDDEN_ANY_COUNT, PIECE_E.position_count, PIECE_E.name);
  optimization_piece_forbidden_any_print(PIECE_G_FORBIDDEN_ANY, PIECE_G_FORBIDDEN_ANY_COUNT, PIECE_G.position_count, PIECE_G.name);
  optimization_piece_forbidden_any_print(PIECE_H_FORBIDDEN_ANY, PIECE_H_FORBIDDEN_ANY_COUNT, PIECE_H.position_count, PIECE_H.name);

  optimization_piece_forbidden_case_print(PIECE_C_FORBIDDEN_CASE, PIECE_C_FORBIDDEN_CASE_COUNT, PIECE_C.position_count, PIECE_C.name);
  optimization_piece_forbidden_case_print(PIECE_F_FORBIDDEN_CASE, PIECE_F_FORBIDDEN_CASE_COUNT, PIECE_F.position_count, PIECE_F.name);
  optimization_piece_forbidden_case_print(PIECE_G_FORBIDDEN_CASE, PIECE_G_FORBIDDEN_CASE_COUNT, PIECE_G.position_count, PIECE_G.name);
  optimization_piece_forbidden_case_print(PIECE_I_FORBIDDEN_CASE, PIECE_I_FORBIDDEN_CASE_COUNT, PIECE_I.position_count, PIECE_I.name);
  optimization_piece_forbidden_case_print(PIECE_J_FORBIDDEN_CASE, PIECE_J_FORBIDDEN_CASE_COUNT, PIECE_J.position_count, PIECE_J.name);
};

BinaryListItem* optimization_piece_forbidden_any_to_binary_list(Position forbidden_any[][PIECE_MAX_POSITION], unsigned int count, unsigned int piece_position_count) {
  BinaryListItem* result = binary_list_item_make_empty();
  for (int i = 0; i < count; i ++) {
    Binary binary = binary_from_positions(forbidden_any[i], piece_position_count, NULL);
    binary_list_push(result, binary);
  }
  return result;
}

BinaryListItem* optimization_piece_forbidden_any_binary_list_filter(BinaryListItem* original, char name) {
  if (!original) return original;
  BinaryListItem* list = NULL;
  switch (name) {
    case 'A':
      list = optimization_piece_forbidden_any_to_binary_list(PIECE_A_FORBIDDEN_ANY, PIECE_A_FORBIDDEN_ANY_COUNT, PIECE_A.position_count);
      break;
    case 'C':
      list = optimization_piece_forbidden_any_to_binary_list(PIECE_C_FORBIDDEN_ANY, PIECE_C_FORBIDDEN_ANY_COUNT, PIECE_C.position_count);
      break;
    case 'D':
      list = optimization_piece_forbidden_any_to_binary_list(PIECE_D_FORBIDDEN_ANY, PIECE_D_FORBIDDEN_ANY_COUNT, PIECE_D.position_count);
      break;
    case 'E':
      list = optimization_piece_forbidden_any_to_binary_list(PIECE_E_FORBIDDEN_ANY, PIECE_E_FORBIDDEN_ANY_COUNT, PIECE_E.position_count);
      break;
    case 'G':
      list = optimization_piece_forbidden_any_to_binary_list(PIECE_G_FORBIDDEN_ANY, PIECE_G_FORBIDDEN_ANY_COUNT, PIECE_G.position_count);
      break;
    case 'H':
      list = optimization_piece_forbidden_any_to_binary_list(PIECE_H_FORBIDDEN_ANY, PIECE_H_FORBIDDEN_ANY_COUNT, PIECE_H.position_count);
      break;
    default:
      break;
  }
  if (list == NULL) return original;
  return binary_list_find_and_remove_list(original, list);
}

BinaryListItem* optimization_piece_forbidden_case_to_binary_list(OptimizationForbiddenCaseItem* forbidden_case, unsigned int count, unsigned int piece_position_count, Date* date) {
  if (!date) return NULL;
  BinaryListItem* list = binary_list_item_make_empty();
  for (int i = 0; i < count; i ++) {
    OptimizationForbiddenCaseItem item = forbidden_case[i];
    PuzzlePositionInfo* info = puzzle_position_info_make(item.condition);
    if (
         (info->kind == PUZZLE_POSITION_KIND_MONTH && info->index != date->month)
      || (info->kind == PUZZLE_POSITION_KIND_DATE && info->index != date->date)
      || (info->kind == PUZZLE_POSITION_KIND_WEEK && info->index != date->week)
    ) {
      binary_list_push_unique(list, binary_from_positions(item.positions, piece_position_count, NULL));
    }
  }
  return list;
}

BinaryListItem* optimization_piece_forbidden_case_binary_list_filter(BinaryListItem* original, char name, Date* date) {
  if (!original || !date) return original;

  BinaryListItem* list = NULL;
  switch (name) {
    case 'C':
      list = optimization_piece_forbidden_case_to_binary_list(PIECE_C_FORBIDDEN_CASE, PIECE_C_FORBIDDEN_CASE_COUNT, PIECE_C.position_count, date);
      break;
    case 'F':
      list = optimization_piece_forbidden_case_to_binary_list(PIECE_F_FORBIDDEN_CASE, PIECE_F_FORBIDDEN_CASE_COUNT, PIECE_F.position_count, date);
      break;
    case 'G':
      list = optimization_piece_forbidden_case_to_binary_list(PIECE_G_FORBIDDEN_CASE, PIECE_G_FORBIDDEN_CASE_COUNT, PIECE_G.position_count, date);
      break;
    case 'I':
      list = optimization_piece_forbidden_case_to_binary_list(PIECE_I_FORBIDDEN_CASE, PIECE_I_FORBIDDEN_CASE_COUNT, PIECE_I.position_count, date);
      break;
    case 'J':
      list = optimization_piece_forbidden_case_to_binary_list(PIECE_J_FORBIDDEN_CASE, PIECE_J_FORBIDDEN_CASE_COUNT, PIECE_J.position_count, date);
      break;
    default:
      break;
  }

  return binary_list_find_and_remove_list(original, list);
}