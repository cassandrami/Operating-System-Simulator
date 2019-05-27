
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

logNode* addLogNode( logNode* firstNode, char* temp )
{
  if ( firstNode != NULL )
  {
    firstNode->next = addLogNode( firstNode->next, temp );
  }

  else
  {
    firstNode = malloc( sizeof( logNode ) );
    copyString( temp, firstNode->logText );
    firstNode->next = NULL;
  }

  return firstNode;
}


int logging( char* filename, logNode* firstNode )
{
  logNode *tempNode = firstNode;
  FILE* fptr = fopen(filename, "w");

    while ( tempNode != NULL )
    {
      fprintf( fptr, "%s", tempNode->logText );
      tempNode = tempNode->next;
    }

  fclose( fptr );
  return 0;

}
