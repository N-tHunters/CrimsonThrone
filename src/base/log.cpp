/**
 * \file
 * \brief This file contains implementation of logging - not currently used
 */
#include "log.hpp"

#include "options.hpp"

/**
 * Log message with facility
 * \param facility Facility of message
 * \param format Format of message (like in printf)
 * \param ... Arguments for format (like in printf)
 */
void Log(int facility, const char * format, ...) {
#ifdef LOGGING
  if (facility < min_facility) return;
  
  time_t t;
  struct tm * timeinfo;

  time(&t);
  timeinfo = localtime(&t);

  va_list argptr;
  va_start(argptr, format);

  if(facility == LOG_DEBUG) {
    printf("%02d:%02d:%02d DEBG ",
	   timeinfo->tm_hour,
	   timeinfo->tm_min,
	   timeinfo->tm_sec);
  } else if (facility == LOG_INFO) {
    printf("%02d:%02d:%02d INFO ",
	   timeinfo->tm_hour,
	   timeinfo->tm_min,
	   timeinfo->tm_sec);
  } else if (facility == LOG_ERROR) {
    printf("%02d:%02d:%02d ERRR ",
	   timeinfo->tm_hour,
	   timeinfo->tm_min,
	   timeinfo->tm_sec);
  }

  vprintf(format, argptr);
  puts("");

  va_end(argptr);
#endif
}
