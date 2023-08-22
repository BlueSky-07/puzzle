#ifndef _POSITION_H_
#define _POSITION_H_

#include <stdlib.h>
#include "bool.h"
#include "const.h"
#include "logger.h"

typedef unsigned int Coordinate;

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
  unsigned int count;
} PositionCount;

typedef Coordinate PositionMoveAction;
#define POSITION_MOVE_ITSELF   1
#define POSITION_MOVE_NEW      2

Position* position_make(Coordinate x, Coordinate y);
PositionListItem* position_list_item_make(Position* position);
PositionListItem* position_list_item_make_empty();
PositionCount* position_count_make(PositionListItem* list);

Position* position_move(Position* position, Position* move, PositionMoveAction action);
Position* position_move_by_coordinate(Position* position, Coordinate x, Coordinate y, PositionMoveAction action);
Coordinate coordinate_move(Coordinate original, Coordinate move, Coordinate max);
Coordinate coordinate_move_x(Coordinate original, Coordinate move);
Coordinate coordinate_move_y(Coordinate original, Coordinate move);

Bool position_list_push(PositionListItem* list, Position* position);

void position_list_free(PositionListItem* list, Bool include_position);
void position_count_free(PositionCount* pc, Bool include_position);

Bool coordinate_is_ok(Coordinate x, Coordinate y);
Bool position_is_ok(Position* position);

void position_print(Position* position, LoggerNewLine new_line);
void position_list_print(PositionListItem* list);

#endif