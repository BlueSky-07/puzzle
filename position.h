#ifndef _POSITION_H_
#define _POSITION_H_

typedef struct Position {
  int row;
  int col;
} Position;

int get_index(int bin, int total);
Position get_index_position(Position position, int total_row, int total_col);

#endif