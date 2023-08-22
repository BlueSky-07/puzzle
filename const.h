#ifndef _CONST_H_
#define _CONST_H_

#define PUZZLE_X 7
#define PUZZLE_Y 8
#define PUZZLE_TOTAL PUZZLE_X * PUZZLE_Y
#define PUZZLE_UNAVAILABLE_COUNT 6
#define PUZZLE_MONTH_COUNT 12
#define PUZZLE_DATE_COUNT 31
#define PUZZLE_WEEK_COUNT 7
#define PUZZLE_STRING_LENGTH (PUZZLE_TOTAL - PUZZLE_UNAVAILABLE_COUNT)

#define MAX_COORDINATE_X PUZZLE_X
#define MAX_COORDINATE_Y PUZZLE_Y

#define PIECE_X 4
#define PIECE_Y 4
#define PIECE_MAX_POSITION 5
#define PIECE_COUNT 10
#define PIECE_ROTATE_DIRECTION_COUNT 8

#define BINARY_TOTAL PUZZLE_TOTAL
#define BINARY_INVALID (BINARY_TOTAL + 1)

#define COORDINATE_INVALID 9

#define GAME_IS_END_REST_COUNT 3

#endif