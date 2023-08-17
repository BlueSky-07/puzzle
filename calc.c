#include "calc.h"

unsigned int calc_negative_to_positive(int number, unsigned int max) {
  if (number == 0) return 0;
  int result = number;
  while (result < 0) {
    result = result + max + 1;
  }
  result = result % max;
  result = result ? result : max;
  return result;
}