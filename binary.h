#ifndef _BINARY_H_
#define _BINARY_H_

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "const.h"
#include "position.h"

typedef unsigned long Binary;
typedef char* String;

Binary position_to_binary(Position* position);
Binary positions_to_binary(Position positions[], int total);
String binary_to_string(Binary binary);
String positions_to_binary_string(Position positions[], int total);

PositionCount* binary_to_positions(Binary binary);
Binary string_to_binary(String string);
PositionCount* binary_string_to_positions(String string);

#endif