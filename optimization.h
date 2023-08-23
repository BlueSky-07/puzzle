#ifndef _OPTIMIZATION_H_
#define _OPTIMIZATION_H_

#include <stdlib.h>
#include "puzzle.h"
#include "binary.h"
#include "position.h"

#define PIECE_A_FORBIDDEN_ANY_COUNT 5
extern Position PIECE_A_FORBIDDEN_ANY[PIECE_A_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION];
#define PIECE_C_FORBIDDEN_ANY_COUNT 7
extern Position PIECE_C_FORBIDDEN_ANY[PIECE_C_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION];
#define PIECE_D_FORBIDDEN_ANY_COUNT 10
extern Position PIECE_D_FORBIDDEN_ANY[PIECE_D_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION];
#define PIECE_E_FORBIDDEN_ANY_COUNT 10
extern Position PIECE_E_FORBIDDEN_ANY[PIECE_E_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION];
#define PIECE_G_FORBIDDEN_ANY_COUNT 8
extern Position PIECE_G_FORBIDDEN_ANY[PIECE_G_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION];
#define PIECE_H_FORBIDDEN_ANY_COUNT 10
extern Position PIECE_H_FORBIDDEN_ANY[PIECE_H_FORBIDDEN_ANY_COUNT][PIECE_MAX_POSITION];

typedef struct _OptimizationForbiddenCaseItem {
  Position* condition;
  Position positions[PIECE_MAX_POSITION];
} OptimizationForbiddenCaseItem;

#define PIECE_C_FORBIDDEN_CASE_COUNT 2
extern OptimizationForbiddenCaseItem PIECE_C_FORBIDDEN_CASE[PIECE_C_FORBIDDEN_CASE_COUNT];
#define PIECE_F_FORBIDDEN_CASE_COUNT 12
extern OptimizationForbiddenCaseItem PIECE_F_FORBIDDEN_CASE[PIECE_F_FORBIDDEN_CASE_COUNT];
#define PIECE_G_FORBIDDEN_CASE_COUNT 11
extern OptimizationForbiddenCaseItem PIECE_G_FORBIDDEN_CASE[PIECE_G_FORBIDDEN_CASE_COUNT];
#define PIECE_I_FORBIDDEN_CASE_COUNT 12
extern OptimizationForbiddenCaseItem PIECE_I_FORBIDDEN_CASE[PIECE_I_FORBIDDEN_CASE_COUNT];
#define PIECE_J_FORBIDDEN_CASE_COUNT 19
extern OptimizationForbiddenCaseItem PIECE_J_FORBIDDEN_CASE[PIECE_J_FORBIDDEN_CASE_COUNT];

void optimization_piece_forbidden_any_print(Position forbidden_any[][PIECE_MAX_POSITION], unsigned int count, unsigned int piece_position_count, char name);
void optimization_piece_forbidden_case_print(OptimizationForbiddenCaseItem* items, unsigned int count, unsigned int piece_position_count, char name);
void optimization_data_print();

#endif