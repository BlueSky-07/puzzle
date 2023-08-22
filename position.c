#include "position.h"

Position* position_make(Coordinate x, Coordinate y) {
  Position* p = malloc(sizeof(Position));
  p->x = x;
  p->y = y;
  return p;
}

PositionListItem* position_list_item_make(Position* position) {
  PositionListItem* pl = malloc(sizeof(PositionListItem));
  pl->position = position;
  pl->next = NULL;
  return pl;
}

PositionListItem* position_list_item_make_empty() {
  return position_list_item_make(NULL);
}

PositionCount* position_count_make(PositionListItem* list) {
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

Position* position_move(Position* position, Position* move, PositionMoveAction action) {
  Position p = *position;
  if (move && (move->x != 0 || move->y != 0))
    logger_debug("position_move: from %d, %d move %d, %d", p.x, p.y, move->x, move->y);
  return position_move_by_coordinate(position, move ? move->x : 0, move ? move->y : 0, action);
}

Position* position_move_by_coordinate(Position* position, Coordinate x, Coordinate y, PositionMoveAction action) {
  Position p = *position;
  Position* result = position;
  switch (action) {
    case POSITION_MOVE_NEW:
      result = position_make(
        coordinate_move_x(p.x, x),
        coordinate_move_y(p.y, y)
      );
      break;
    case POSITION_MOVE_ITSELF:
    default:
      p.x = coordinate_move_x(p.x, x);
      p.y = coordinate_move_y(p.y, y);
      break;
  }
  if (x != 0 || y != 0)
    logger_debug("position_move_by_coordinate: %d + %d, %d + %d => %d, %d", p.x, x, p.y ,y, result->x, result->y);
  return result;
}

Coordinate coordinate_move(Coordinate original, Coordinate move, Coordinate max) {
  if (move == 0) return original;
  if (move > 0 && original + move > max) return COORDINATE_INVALID;
  else if (move < 0 && -move > original) return COORDINATE_INVALID;
  else return original + move;

}

Coordinate coordinate_move_x(Coordinate original, Coordinate move) {
  return coordinate_move(original, move, MAX_COORDINATE_X);
}

Coordinate coordinate_move_y(Coordinate original, Coordinate move) {
  return coordinate_move(original, move, MAX_COORDINATE_Y);
}

Bool position_list_push(PositionListItem* list, Position* position) {
  if (!list) return FALSE;
  while (list->next) list = list->next;
  if (!list->position) list->position = position;
  else list->next = position_list_item_make(position);
  return TRUE;
}

void position_list_free(PositionListItem* list, Bool include_position) {
  if (list->next)
    position_list_free(list->next, include_position);

  if (include_position) free(list->position);
  free(list);
}

void position_count_free(PositionCount* pc, Bool include_position) {
  if (!pc) return;
  position_list_free(pc->positions, include_position);
  free(pc);
}

Bool coordinate_is_ok(Coordinate x, Coordinate y) {
  return x >= 0 && x < MAX_COORDINATE_X
      && y >= 0 && y < MAX_COORDINATE_Y;
}

Bool position_is_ok(Position* position) {
  Position p = *position;
  return coordinate_is_ok(p.x, p.y);
}

void position_print(Position* position, LoggerNewLine new_line) {
  if (!position) return;
  Position p = *position;
  printf("%d, %d", p.x, p.y);
  if (new_line) printf("\n");
}

void position_list_print(PositionListItem* list) {
  if (!list) return;
  while (list && list->position) {
    position_print(list->position, LOGGER_NEW_LINE);
    list = list->next;
  }
}
