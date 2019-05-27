
/*
 * simConfig.H
 *
 * version 1.00
 * initial development January 2018
 *
 *

Some solutions and styles here adapted from:
-Michael Leverington Linked List(.c, .h)

*/

#ifndef CONFIG
#define CONFIG

#include "functions.h"

//switch case variable names
enum CASE_NAMES { VersionNum = 1, FilePath = 2,
                CPUSchedulingCode = 3, QuantumTime = 4,
                MemoryAvailable = 5, ProcessorCycleTime = 6,
                IOCycleTime = 7, LogTo = 8,
                LogFilePath = 9 };

//structure declaration
typedef struct Set
{
  int version;
  int qTime;
  int memAvail;
  int pcTime;
  int iocTime;
  char fPath[30];
  char cSched[8];
  char logTo[8];
  char logPath[8];

} Set;

//declaring functions written in simConfig.c
int getData( Set *newSet, char *fileName );

int validateVersion( Set *newSet );
int validateSCode( Set *newSet );
int validateQTime(Set *newSet);
int validateMemAvail( Set *newSet );
int validateCycleTime( Set *newSet );
int validateIOTime( Set *newSet );
int validateLogTo( Set *newSet );
int validateFilePath( Set *newSet );

int logData( Set *newSet );

#endif
