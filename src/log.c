/*-------------------------------------------------------------------------
 *
 * log.c
 *	  log system for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/log.c
 *
 *
 * NOTES
 *	  log system
 *
 *-------------------------------------------------------------------------
 */
#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define LOG_BUFSZ 1024
static FILE *log_fp = NULL;
static enum LOG_LEVEL log_level = LOG_LEVEL_INFO;

void log_set_file(const char *file) { log_fp = fopen(file, "a+"); }
void log_set_level(enum LOG_LEVEL level) { log_level = level; };

void log_internal(enum LOG_LEVEL level, const char *level_str, const char *file,
                  int line, const char *func, const char *fmt, ...) {
  if (level < log_level) return;
  char buf[LOG_BUFSZ] = {0};
  snprintf(buf, sizeof(buf), "[%s] %s:%d %s() ", level_str, file, line, func);
  if (strlen(buf) + 1 < sizeof(buf)) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), fmt, ap);
    va_end(ap);
  }
  fprintf(log_fp == NULL ? stderr : log_fp, "%s\n", buf);
}
