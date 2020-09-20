#include "log.h"

#include "options.h"

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
    printf("%d:%d:%d DEBG ",
	   timeinfo->tm_hour,
	   timeinfo->tm_min,
	   timeinfo->tm_sec);
  } else if (facility == LOG_INFO) {
    printf("%d:%d:%d INFO ",
	   timeinfo->tm_hour,
	   timeinfo->tm_min,
	   timeinfo->tm_sec);
  } else if (facility == LOG_ERROR) {
    printf("%d:%d:%d ERRR ",
	   timeinfo->tm_hour,
	   timeinfo->tm_min,
	   timeinfo->tm_sec);
  }

  vprintf(format, argptr);
  puts("");

  va_end(argptr);
#endif
}
