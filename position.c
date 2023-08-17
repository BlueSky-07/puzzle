#include "position.h"

Position* make_position(Coordinate x, Coordinate y) {
  Position* p = malloc(sizeof(Position));
  p->x = x;
  p->y = y;
  return p;
}

PositionListItem* make_position_list_item(Position* position) {
  PositionListItem* pl = malloc(sizeof(PositionListItem));
  pl->position = position;
  pl->next = NULL;
  return pl;
}

PositionCount* make_position_count(PositionListItem* list) {
  PositionCount* pc = malloc(sizeof(PositionCount));
  pc->positions = list;
  int count = 0;
  while (list) {
    count += list->position ? 1 : 0;
    list = list->next;
  }
  pc->count = count;
  return pc;
}

Position* position_move(Position* position, CoordinateMove x, CoordinateMove y, PositionMoveAction action) {
  Position p = *position;
  switch (action) {
    case POSITION_MOVE_NEW:
      return make_position(
        coordinate_move(p.x, x, MAX_COORDINATE_X),
        coordinate_move(p.y, y, MAX_COORDINATE_Y)
      );
    case POSITION_MOVE_ITSELF:
    default:
      p.x = coordinate_move(p.x, x, MAX_COORDINATE_X);
      p.y = coordinate_move(p.y, y, MAX_COORDINATE_Y);
      return position;
  }
}

Coordinate coordinate_move(Coordinate original, CoordinateMove move, Coordinate max) {
  if (move >= 0 && original + move > max) return 0;
  else if (move < 0 && -move > original) return 0;
  else return original + move;
}

Bool position_list_push(PositionListItem* list, Position* position) {
  if (!list) return FALSE;
  while (list->next) list = list->next;
  if (!list->position) list->position = position;
  else list->next = make_position_list_item(position);
  return TRUE;
}

PositionCount* position_list_find(PositionListItem* list, Position* position) {
  // todo
  return NULL;
}

PositionCount* position_list_find_and_remove(PositionListItem* list, Position* position) {
  // todo
  return NULL;
}

void position_list_free(PositionListItem* list, Bool include_position) {
  if (list->next) {
    position_list_free(list->next, include_position);
  }
  if (include_position) free(list->position);
  free(list);
}

void position_count_free(PositionCount* pc, Bool include_position) {
  if (!pc) return;
  position_list_free(pc->positions, include_position);
  free(pc);
}

int is_position(Position* position) {
  Position p = *position;
  return p.x > 0 && p.x <= MAX_COORDINATE_X
      && p.y > 0 && p.y <= MAX_COORDINATE_Y;
}

void print_position(Position* position) {
  if (!position) return;
  Position p = *position;
  printf("%d, %d", p.x, p.y);
}

void print_position_list(PositionListItem* list) {
  if (!list) return;
  while (list && list->position) {
    print_position(list->position);
    printf("\n");
    list = list->next;
  }
}
