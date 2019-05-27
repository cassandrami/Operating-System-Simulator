/*
 * PCBLIST.H
 *
 * version 1.00
 * initial development February 2018
 *
 *

 */

#include "simtimer.h"
#include "simMetadata.h"
#include "simConfig.h"
#include "logList.h"
#include <pthread.h>

 enum STATE_NAMES { New = 1, Running = 2,
                 Ready = 3, Exit = 4};

 typedef struct PCBNode
 {

   int state;
   struct PCBNode* nextPCB;
   Node* process;

 } PCBNode;

int getProcesses( Node* firstNode, PCBNode** firstPCB );
PCBNode* addPCBNode( PCBNode* firstNode, PCBNode* newNode );
int runProcesses( Set* currSet, PCBNode* currPCB );
int getRunTime( Node* currNode, Set* currSet );
PCBNode* clearPCB( PCBNode* firstNode );
void* runThread( void* time );
