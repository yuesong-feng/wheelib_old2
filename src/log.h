/*-------------------------------------------------------------------------
 *
 * log.h
 *	  log system for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/log.h
 *
 *
 * NOTES
 *	  log system
 *
 *-------------------------------------------------------------------------
 */
#ifndef LOG_H
#define LOG_H

enum LOG_LEVEL {
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR
};

#ifdef __GNUC__
#define CHECK_FMT(a, b) __attribute__((format(printf, a, b)))
#else
#define CHECK_FMT(a, b)
#endif

void log_set_file(const char* file);
void log_set_level(enum LOG_LEVEL level);
void log_internal(enum LOG_LEVEL level, const char* level_str, const char* file,
                  int line, const char* func, const char* fmt, ...);

#define LOG_DEBUG(fmt, ...) do { \
    log_internal(LOG_LEVEL_DEBUG, "DEBUG", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);    \
} while(0)

#define LOG_INFO(fmt, ...) do { \
    log_internal(LOG_LEVEL_INFO, "INFO", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);    \
} while(0)

#define LOG_WARN(fmt, ...) do { \
    log_internal(LOG_LEVEL_WARN, "WARN", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);    \
} while(0)

#define LOG_ERROR(fmt, ...) do { \
    log_internal(LOG_LEVEL_ERROR, "ERROR", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__);    \
} while(0)

#endif
