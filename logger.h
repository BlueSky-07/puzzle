#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef unsigned int LoggerLevel;
#define LOGGER_LEVEL_ERROR    1
#define LOGGER_LEVEL_SUCCESS  2
#define LOGGER_LEVEL_INFO     3
#define LOGGER_LEVEL_VERBOSE  4
#define LOGGER_LEVEL_DEBUG    5

typedef unsigned int LoggerNewLine;
#define LOGGER_NO_NEW_LINE    0
#define LOGGER_NEW_LINE       1

typedef unsigned int LoggerIsEnabled;
#define LOGGER_DISABLED  0
#define LOGGER_ENABLED   1

extern LoggerIsEnabled _logger_global_is_enabled;
extern LoggerLevel _logger_global_level;
extern FILE* _logger_global_stream_out;
extern FILE* _logger_global_stream_err;

void set_logger_global_level(LoggerLevel level);
void set_logger_global_level_from_env();
void set_logger_global_is_enabled(LoggerIsEnabled enabled);
void set_logger_global_is_enabled_from_env();
void set_logger_global_from_env();

int logger_level_is_ok(LoggerLevel level);
int logger_level_is_error_ok();
int logger_level_is_success_ok();
int logger_level_is_info_ok();
int logger_level_is_verbose_ok();
int logger_level_is_debug_ok();

void logger_error(const char *format, ...);
void logger_success(const char *format, ...);
void logger_info(const char *format, ...);
void logger_verbose(const char *format, ...);
void logger_debug(const char *format, ...);

void logger_println(LoggerLevel level, const char *format, ...);
void logger_print(LoggerLevel level, const char *format, ...);
void logger_vprint(LoggerLevel level, LoggerNewLine new_line, const char *format, va_list args);

char* logger_level_to_string(LoggerLevel level, int short_format);
int logger_level_from_string(char* level_string);
FILE* logger_level_to_stream(LoggerLevel level);

#endif