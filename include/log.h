#ifndef LOGH
#define LOGH

#include <stdio.h>
#include "list.h"

#define DO_LOG_DUMP(logInfo, list) {                           \
	logDump(logInfo, __func__, list);                          \
}

const int sizeOfBuf = 100;

void logInit(FILE * logFile, LogInfo * log);

void logDump(LogInfo * log, const char * func, List * list);

void dump(List * list, char * pathToDot);

void logClose(LogInfo * log);

#endif // LOGH
