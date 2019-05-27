/*
 * PCBLIST.H
 *
 * version 2.00
 * initial development April 2018
 *
 *

 */

#include "simtimer.h"
#include "simMetadata.h"
#include "simConfig.h"
#include "logList.h"
#include <pthread.h>
#include "memManager.h"

 enum STATE_NAMES { New = 1, Running = 2,
                 Ready = 3, Exit = 4};

 typedef struct PCBNode
 {

   int state;
   struct PCBNode* nextPCB;
   Node* process;
	 int processNum;
	 int processTime;

 } PCBNode;


PCBNode* checkAlgorithm( PCBNode* firstPCB, char* instruction );
PCBNode* sortProcesses( PCBNode* firstPCB );

int getProcesses( Node* firstNode, PCBNode** firstPCB, Set* currSet );
int runProcesses( Set* currSet, PCBNode* currPCB );
int getRunTime( Node* currNode, Set* currSet );

PCBNode* clearPCB( PCBNode* firstNode );
PCBNode* addPCBNode( PCBNode* firstNode, PCBNode* newNode );
void logRecords( Boolean logToFile, Boolean logToMonitor, logNode* newLog, char* logText );

void* runThread( void* time );
