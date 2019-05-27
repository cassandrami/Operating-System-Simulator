
/*
 *
 * SIMCONFIG.C
 *
 * version 2.00
 * initial development January 2018
 * last edited February 2018
 *
 *

Some solutions and styles adapted from:
-Michael Leverington Linked List(.c, .h)

*/


#include "simConfig.h"


//reads in data from configuration file to the database (set)
int getData( Set *newSet, char *fileName )
{
  FILE *fPtr;
  int strIndex, currChar;
  char strBuffer[ MAXLEN ], dataBuffer[ MAXLEN ];
  int numColons = 0;

  fPtr = fopen( fileName, READ_ONLY );
  if ( fPtr ==  NULL )
  {
    return FILE_OPEN_ERR;
  }

  else
  {

    strIndex = 0;
    currChar = fgetc( fPtr );

    while (( feof( fPtr ) == 0 ) && currChar != (int) NEWLINE )
    {
      strBuffer[ strIndex ] = (char)( currChar );
      strIndex++;
      strBuffer[ strIndex ] = NULL_CHAR;
      currChar = fgetc( fPtr );
    }

    if( strCompare( strBuffer, "Start Simulator Configuration File" ) != 0 )
    {
      fclose( fPtr );
      return INCORRECT_FILE_ERR;
    }

    numColons = 0;

    while( feof( fPtr ) == 0 )
    {

      strIndex = 0;
      currChar = fgetc( fPtr );

      while ( currChar != (int)( COLON ) )
      {
        strBuffer[ strIndex ] = (char)( currChar );
        strIndex++;
        strBuffer[ strIndex ] = NULL_CHAR;
        currChar = fgetc( fPtr );


        if ( currChar == (int) PERIOD )
        {
          if( strCompare( strBuffer, "End Simulator Configuration File") == 0 )
          {
            fclose( fPtr );
            return NO_ERROR_MSG;
          }
          else
          {
            fclose( fPtr );
            return END_FILE_FOUND_MSG;
          }
        }
      }

    currChar = fgetc( fPtr );

    ++numColons;
    strIndex = 0;

    currChar = fgetc( fPtr );
    while ( currChar != (int) NEWLINE )

    {
      dataBuffer[ strIndex ] = (char)( currChar );
      strIndex++;
      dataBuffer[ strIndex ] = NULL_CHAR;
      currChar = fgetc( fPtr );
    }

    //switch cases that grab and validate data
    switch (numColons)
    {

    case VersionNum:
      if ( strCompare( strBuffer, "Version/Phase" ) == 0 )
      {
        newSet->version = strInt( dataBuffer );
        validateVersion( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case FilePath:
      if ( strCompare( strBuffer, "File Path" ) == 0 )
      {
        copyString( dataBuffer, newSet->fPath );
        validateFilePath( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case CPUSchedulingCode:
      if ( strCompare( strBuffer, "CPU Scheduling Code" ) == 0 )
      {
        copyString( dataBuffer, newSet->cSched );
        validateSCode( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case QuantumTime:
      if ( strCompare( strBuffer, "Quantum Time (cycles)" ) == 0 )
      {
        newSet->qTime = strInt( dataBuffer );
        validateQTime( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case MemoryAvailable:
      if ( strCompare( strBuffer, "Memory Available (KB)" ) == 0 )
      {
        newSet->memAvail = strInt( dataBuffer );
        validateMemAvail( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case ProcessorCycleTime:
      if ( strCompare( strBuffer, "Processor Cycle Time (msec)" ) == 0 )
      {
        newSet->pcTime = strInt( dataBuffer );
        validateCycleTime( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case IOCycleTime:
      if ( strCompare( strBuffer, "I/O Cycle Time (msec)" ) == 0 )
      {
        newSet->iocTime = strInt( dataBuffer );
        validateIOTime( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case LogTo:
      if ( strCompare( strBuffer, "Log To" ) == 0 )
      {
        copyString( dataBuffer, newSet->logTo );
        validateLogTo( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    case LogFilePath:
      if ( strCompare( strBuffer, "Log File Path" ) == 0 )
      {
        copyString( dataBuffer, newSet->logPath );
        validateFilePath( newSet );
      }
      else
      {
        return INCORRECT_FILE_ERR;
      }
      break;

    }
    }
  }
  return 0;
}

//appropriate validation tests for data conditions
int validateSCode( Set *newSet )
{
  if ( strCompare( newSet->cSched, "NONE" ) == 0 )
  {
    copyString( "FCFS-N", newSet->cSched );
    return 0;
  }
  else if (( strCompare(newSet->cSched, "FCFS-N") == 0 ) ||
           ( strCompare(newSet->cSched, "SJF-N") == 0 ) ||
           ( strCompare(newSet->cSched, "SRTF-P") == 0 ) ||
           ( strCompare(newSet->cSched, "FCFS-P") == 0 ) ||
           ( strCompare(newSet->cSched, "RR-P") == 0 ))
  {
    return 0;
  }

  else
  {
    return INCOMPLETE_FILE_ERR;
  }
}

int validateFilePath(Set *newSet)
{
  if ( strCompare( newSet->logTo, "Monitor" ) == 0 )
  {
    copyString( "nologfile", newSet->logPath );
    return 0;
  }
  else
  {
    return 0;
  }
}

int validateLogTo( Set *newSet )
{
  if (( strCompare(newSet->logTo, "Monitor" ) != 0) ||
      ( strCompare(newSet->logTo, "File" ) != 0) ||
      ( strCompare(newSet->logTo, "Both" ) != 0))
  {
    return INCOMPLETE_FILE_ERR;
  }
  else
  {
    return 0;
  }
}

int validateIOTime ( Set *newSet )
{
  if ((!( newSet->iocTime >= 1 )) || (!( newSet->iocTime <= 10000 )))
  {
    return INCORRECT_FILE_ERR;
  }
  else
  {
    return 0;
  }
}

int validateCycleTime( Set *newSet )
{
  if ((!( newSet->pcTime >= 1 )) || (!( newSet->memAvail <= 1000 )))
  {
    return INCORRECT_FILE_ERR;
  }
  else
  {
    return 0;
  }
}

int validateMemAvail( Set *newSet )
{
  if ((!( newSet->memAvail >= 0 )) || (!( newSet->memAvail <= 1048576 )))
  {
    return INCORRECT_FILE_ERR;
  }
  else
  {
    return 0;
  }
}

int validateQTime( Set *newSet )
{
  if ((!( newSet->qTime >= 0 )) || (!( newSet->qTime <= 100 )))
  {
    return INCORRECT_FILE_ERR;
  }
  else
  {
    return 0;
  }
}

int validateVersion( Set *newSet )
{
  if ((!( newSet->version >= 0 )) || (!( newSet->version <= 10 )))
  {
    return INCORRECT_FILE_ERR;
  }
  else
  {
    return 0;
  }
}
//end validation tests


//uploads data to monitor or file as specified
int logData( Set *newSet )
{

  FILE *filePointer;
  if ( strCompare( newSet->logPath, "nologfile" ) == 0 )
  {
    printf("No log file...\n\n\n");
    printf("Configuration File Log\n\n\n");
    printf("Version/Phase:          %d\n", newSet->version);
    printf("File Path:              %s\n", newSet->fPath);
    printf("CPU Scheduling Code:    %s\n", newSet->cSched);
    printf("Quantum Time:           %d\n", newSet->qTime);
    printf("Memory Available:       %d\n", newSet->memAvail);
    printf("Processor Cycle Time:   %d\n", newSet->pcTime);
    printf("I/O Cycle Time:         %d\n", newSet->iocTime);
    printf("Log To:                 %s\n", newSet->logTo);
    printf("Log File Path:          %s\n", newSet->logPath);
    printf("\n\n\n");
  }

  else
  {

    filePointer = fopen(newSet->logPath, "w");

    fprintf(filePointer, "Configuration File Log\n\n\n");
    fprintf(filePointer, "Version/Phase:          %d\n", newSet->version);
    fprintf(filePointer, "File Path:              %s\n", newSet->fPath);
    fprintf(filePointer, "CPU Scheduling Code:    %s\n", newSet->cSched);
    fprintf(filePointer, "Quantum Time:           %d\n", newSet->qTime);
    fprintf(filePointer, "Memory Available:       %d\n", newSet->memAvail);
    fprintf(filePointer, "Processor Cycle Time:   %d\n", newSet->pcTime);
    fprintf(filePointer, "I/O Cycle Time:         %d\n", newSet->iocTime);
    fprintf(filePointer, "Log To:                 %s\n", newSet->logTo);
    fprintf(filePointer, "Log File Path:          %s\n", newSet->logPath);
    fprintf(filePointer, "\n\n\n");

    fclose(filePointer);
  }

  return 0;
}
 
