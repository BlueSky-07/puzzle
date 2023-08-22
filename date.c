#include "date.h"

Date* date_make(unsigned int month, unsigned int date, unsigned int week) {
  Date* result = malloc(sizeof(Date));
  result->month = month;
  result->date = date;
  result->week = week;
  return result;
}

Date* date_get_today() {
  time_t currentTime;
  struct tm *localTime;
  currentTime = time(NULL);
  localTime = localtime(&currentTime);

  logger_debug(
    "date_get_today: %04d/%02d/%02d <=> %s %s %s",
    localTime->tm_year + 1900,
    localTime->tm_mon + 1,
    localTime->tm_mday,
    MONTH_TEXTS[localTime->tm_mon],
    DATE_TEXTS[localTime->tm_mday - 1],
    WEEK_TEXTS[localTime->tm_wday]
  );

  return date_make(localTime->tm_mon, localTime->tm_mday - 1, localTime->tm_wday);
}