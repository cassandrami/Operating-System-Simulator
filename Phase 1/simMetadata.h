
/*
 * SIMMETADATA.H
 *
 * version 1.00
 * initial development January 2018
 *
 *

 */

#include "functions.h"

typedef struct Node
{
  char commCode;
  char action[12];
  int val;

  struct Node* next;

} Node;


int getMetaData( Node **newNode, char *fileName, char *logfile );
Node* addNode( Node *firstNode, Node *newNode );
Node* makeNode( char code, char *action, int value );
Node* clearList( Node *firstNode );
int logMetaData( Node *node, char *logfile );
int validateCommand( char temp );
