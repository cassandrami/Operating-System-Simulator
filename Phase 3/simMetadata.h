
/*
 * SIMMETADATA.H
 *
 * version 2.00
 * initial development January 2018
 * last edited February 2018
 *
 *

 */

#ifndef functions_h
#define functions_h

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
void copyNode( Node* currNode, Node* destNode );

#endif
