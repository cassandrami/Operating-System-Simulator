
/*
 * LOGLIST.H
 *
 * version 1.00
 * initial development February 2018
 *
 *

 */

 #include "functions.h"

typedef struct logNode
{

  char logText[90];
  struct logNode* next;

} logNode;

int logging( char* filename, logNode* firstNode );
logNode* addLogNode( logNode* firstNode, char* temp );
