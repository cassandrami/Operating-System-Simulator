
/*
 * LOGLIST.H
 *
 * version 2.00
 * initial development April 2018
 *
 *

 */

 #include "functions.h"

typedef struct logNode
{

  char logText[90];
  struct logNode* next;

} logNode;

logNode *clearLogNode( logNode* firstNode );
int logging( char* filename, logNode* firstNode );
logNode* addLogNode( logNode* firstNode, char* temp );
