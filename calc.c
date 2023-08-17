#include "calc.h"

unsigned int calc_negative_to_positive(int number, unsigned int max) {
  int result = (number + max) % max;
  logger_debug("calc_negative_to_positive: max %d, %d => %d", max, number, result);
  return result;
}