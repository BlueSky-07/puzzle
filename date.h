#ifndef _DATE_H_
#define _DATE_H_

#include <time.h>
#include <stdlib.h>
#include "logger.h"
#include "puzzle.h"

typedef struct _Date {
  unsigned int month; // 0 - 11
  unsigned int date;  // 0 - 30
  unsigned int week;  // 0 - 6
} Date;

Date* date_make(unsigned int month, unsigned int date, unsigned int week);
Date* date_get_today();

#endif