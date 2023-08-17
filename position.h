#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdlib.h>
#include "bool.h"
#include "const.h"
#include "logger.h"

typedef unsigned int Coordinate;
typedef int CoordinateMove;

typedef struct _Position {
  Coordinate x;
  Coordinate y;
} Position;

typedef struct _PositionListItem {
  Position* position;
  struct _PositionListItem* next;
} PositionListItem;


typedef struct _PositionCount {
  PositionListItem* positions;
  Coordinate count;
} PositionCount;

typedef Coordinate PositionMoveAction;
#define POSITION_MOVE_ITSELF   1
#define POSITION_MOVE_NEW      2

Position* make_position(Coordinate x, Coordinate y);
PositionListItem* make_position_list_item(Position* position);
PositionCount* make_position_count(PositionListItem* list);

Position* position_move(Position* position, CoordinateMove x, CoordinateMove y, PositionMoveAction action);
Coordinate coordinate_move(Coordinate original, CoordinateMove move, Coordinate max);

Bool position_list_push(PositionListItem* list, Position* position);
PositionCount* position_list_find(PositionListItem* list, Position* position);
PositionCount* position_list_find_and_remove(PositionListItem* list, Position* position);

void position_list_free(PositionListItem* list, Bool include_position);
void position_count_free(PositionCount* pc, Bool include_position);

int is_position(Position* position);

#endif