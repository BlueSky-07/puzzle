#include "date.h"

Date* date_make(unsigned int month, unsigned int date, unsigned int week) {
  Date* result = malloc(sizeof(Date));
  result->month = month;
  result->date = date;
  result->week = week;
  return result;
}

Date* date_get_today() {
  return date_get_today_next(0);
}

Date* date_get_today_next(int days) {
  time_t currentTime = time(NULL);
  currentTime += days * 24 * 60 * 60;
  struct tm *localTime = localtime(&currentTime);

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

void date_time_print(time_t t, LoggerNewLine new_line) {
  struct tm *localTime = localtime(&t);
  printf(
    "%04d/%02d(%s)/%02d %s %02d:%02d:%02d",
    localTime->tm_year + 1900,
    localTime->tm_mon + 1,
    MONTH_TEXTS[localTime->tm_mon],
    localTime->tm_mday,
    WEEK_TEXTS[localTime->tm_wday],
    localTime->tm_hour,
    localTime->tm_min,
    localTime->tm_sec
  );

  if (new_line) printf("\n");
}

void date_current_time_print(LoggerNewLine new_line) {
  date_time_print(time(NULL), new_line);
}