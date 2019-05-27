
/*
 * LOGLIST.C
 *
 * version 1.00
 * initial development February 2018
 *
 *
 */

#include "logList.h"

logNode* addLogNode( logNode* firstNode, char* temp )
{
  if ( firstNode != NULL )
  {
    firstNode->next = addLogNode( firstNode->next, temp );
  }

  else
  {
    firstNode = malloc( sizeof( logNode ) );
    copyString( firstNode->logText, temp );
    firstNode->next = NULL;
  }

  return firstNode;
}


int logging( char* filename, logNode* firstNode )
{
  logNode *tempNode = firstNode;
  FILE* fptr = NULL;

    while ( tempNode != NULL )
    {
      fprintf( fptr, "%s", tempNode->logText );
      tempNode = tempNode->next;
    }

  fclose( fptr );
  return 0;

}
