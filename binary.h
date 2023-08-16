#ifndef _BINARY_H_
#define _BINARY_H_

#include "position.h"
#include "puzzle.h"

typedef unsigned long Binary;

Binary position_to_binary(Position position);
Binary positions_to_binary(Position positions[], int total);
char* binary_to_string(Binary bin);

#endif