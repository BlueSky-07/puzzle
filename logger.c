#include "logger.h"

LoggerIsEnabled _logger_global_is_enabled = LOGGER_DISABLED;
LoggerLevel _logger_global_level = LOGGER_LEVEL_INFO;
FILE* _logger_global_stream_out = NULL; // todo
FILE* _logger_global_stream_err = NULL; // todo

void logger_global_set_level(LoggerLevel level) {
  _logger_global_level = level;
}

char* _string_lowercase(char* string) {
  int len = strlen(string);
  char* result = malloc(sizeof(char) * len);

  for (int i = 0; i < len; i++) result[i] = tolower(string[i]);
  return result;
}

int logger_level_from_string(char* level_string) {
  if (level_string == NULL) return -1;

  char* lower_level_string = _string_lowercase(level_string);
  int result = -1;
  if (strcmp("error", lower_level_string) == 0) result = LOGGER_LEVEL_ERROR;
  else if (strcmp("success", lower_level_string) == 0) result = LOGGER_LEVEL_SUCCESS;
  else if (strcmp("info", lower_level_string) == 0) result = LOGGER_LEVEL_INFO;
  else if (strcmp("verbose", lower_level_string) == 0) result = LOGGER_LEVEL_VERBOSE;
  else if (strcmp("debug", lower_level_string) == 0) result = LOGGER_LEVEL_DEBUG;

  free(lower_level_string);
  return result;
}

void logger_global_set_level_from_env() {
  char* level_string = getenv("LOGGER_LEVEL");
  int level = logger_level_from_string(level_string);
  if (level < 0) return;
  logger_global_set_level(level);
}

void logger_global_set_is_enabled(LoggerIsEnabled enabled) {
  _logger_global_is_enabled = enabled;
}

int _bool_from_string(char* string) {
  if (string == NULL) return -1;

  char* lower_string = _string_lowercase(string);
  int result = -1;
  if (strcmp("off", lower_string) == 0
   || strcmp("false", lower_string) == 0
  ) result = 0;
  else if (strcmp("on", lower_string) == 0
        || strcmp("true", lower_string) == 0
  ) result = 1;

  free(lower_string);
  return result;
}

void logger_global_set_is_enabled_from_env() {
  char* enabled_string = getenv("LOGGER");

  int enabled = _bool_from_string(enabled_string);
  if (enabled < 0) return;
  logger_global_set_is_enabled(enabled);
}

void logger_global_set_all_from_env() {
  logger_global_set_is_enabled_from_env();
  logger_global_set_level_from_env();
}

int logger_level_is_ok(LoggerLevel level) {
  return _logger_global_is_enabled && level <= _logger_global_level;
}

int logger_level_is_error_ok() {
  return logger_level_is_ok(LOGGER_LEVEL_ERROR);
}

int logger_level_is_success_ok() {
  return logger_level_is_ok(LOGGER_LEVEL_SUCCESS);
}

int logger_level_is_info_ok() {
  return logger_level_is_ok(LOGGER_LEVEL_INFO);
}

int logger_level_is_verbose_ok() {
  return logger_level_is_ok(LOGGER_LEVEL_VERBOSE);
}

int logger_level_is_debug_ok() {
  return logger_level_is_ok(LOGGER_LEVEL_DEBUG);
}

void logger_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(LOGGER_LEVEL_ERROR, LOGGER_NEW_LINE, format, args);
  va_end(args);
}

void logger_success(const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(LOGGER_LEVEL_SUCCESS, LOGGER_NEW_LINE, format, args);
  va_end(args);
}

void logger_info(const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(LOGGER_LEVEL_INFO, LOGGER_NEW_LINE, format, args);
  va_end(args);
}

void logger_verbose(const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(LOGGER_LEVEL_VERBOSE, LOGGER_NEW_LINE, format, args);
  va_end(args);
}

void logger_debug(const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(LOGGER_LEVEL_DEBUG, LOGGER_NEW_LINE, format, args);
  va_end(args);
}


void logger_println(LoggerLevel level, const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(level, LOGGER_NEW_LINE, format, args);
  va_end(args);
}

void logger_print(LoggerLevel level, const char *format, ...) {
  va_list args;
  va_start(args, format);
  logger_vprint(level, LOGGER_NO_NEW_LINE, format, args);
  va_end(args);
}

void logger_vprint(LoggerLevel level, LoggerNewLine new_line, const char *format, va_list args) {
  if (!logger_level_is_ok(level)) return;

  unsigned int len = strlen(format)      // original
                     + 4                 // prefix
                     + new_line          // new line
                     + 1;                // end

  char* new_format = malloc(sizeof(char) * len);
  new_format[0] = '\0';  // init

  strcat(new_format, logger_level_to_string(level, 1)); // prefix
  strcat(new_format, " ");                              // prefix
  strcat(new_format, format);                           // original
  if (new_line) strcat(new_format, "\n");               // new line
  new_format[len - 1] = '\0';                           // end

  // for (int i = 0; i < len; i ++)
  //   printf("%c", new_format[i]); // output format

  vfprintf(logger_level_to_stream(level), new_format, args);

  free(new_format);
}

char* logger_level_to_string(LoggerLevel level, int short_format) {
  switch (level) {
    case LOGGER_LEVEL_ERROR:
      return short_format ? "[E]" : "ERR";
    case LOGGER_LEVEL_SUCCESS:
      return short_format ? "[S]" : "SUC";
    case LOGGER_LEVEL_INFO:
      return short_format ? "[I]" : "INF";
    case LOGGER_LEVEL_VERBOSE:
      return short_format ? "[V]" : "VER";
    case LOGGER_LEVEL_DEBUG:
      return short_format ? "[D]" : "DEB";

    default:
      return "";
  }
}

FILE * logger_level_to_stream(LoggerLevel level) {
  switch (level) {
    case LOGGER_LEVEL_ERROR:
      return _logger_global_stream_err ? _logger_global_stream_err : stderr;
    case LOGGER_LEVEL_SUCCESS:
    case LOGGER_LEVEL_INFO:
    case LOGGER_LEVEL_VERBOSE:
    case LOGGER_LEVEL_DEBUG:
    default:
      return _logger_global_stream_out ? _logger_global_stream_out : stdout;
  }
}