
/*
 * LOGLIST.C
 *
 * version 2.00
 * initial development April 2018
 *
 *
 */

#include "logList.h"

logNode* clearLogNode( logNode* firstNode )
{
	if ( firstNode == NULL )
	{
		return NULL;
	}
	else if ( firstNode->next != NULL )
	{
		clearLogNode( firstNode->next );
	}

	free( firstNode );
	firstNode = NULL;
	return firstNode;
}

void addLogNode( logNode* firstNode, char* temp )
{
	logNode* currLog;

  if ( firstNode != NULL )
  {
    currLog = firstNode;
		while ( currLog->next != NULL )
		{
			currLog = currLog->next;
		}

		currLog->next = malloc( sizeof( logNode )	);
		currLog = currLog->next;
		copyString( temp, currLog->logText );
		currLog->next = NULL;
  }

  else
  {
    firstNode = malloc( sizeof( logNode ) );
    copyString( temp, firstNode->logText );
    firstNode->next = NULL;
  }
}


void logging( char* filename, logNode* firstNode )
{
  logNode *tempNode = firstNode;
  FILE* fptr = fopen(filename, "w");

  while ( tempNode != NULL )
  {
    fprintf( fptr, "%s", tempNode->logText );
    tempNode = tempNode->next;
  }

  fclose( fptr );
}

void logRecords( Boolean logToFile, Boolean logToMonitor, logNode* newLog, char* logText )
{

	if ( logToFile )
  {
    addLogNode( newLog, logText );
  }

  if ( logToMonitor )
  {
    printf( "%s", logText );
  }
}
