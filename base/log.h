/**
 * \file
 * \brief This file contains declaration of logging functions - not currently used
 */
#ifndef CT_LOG_H
#define CT_LOG_H

#include <string>
#include <ctime>
#include <stdarg.h>

#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_ERROR 2

void Log(int, const char *, ...);

#endif
