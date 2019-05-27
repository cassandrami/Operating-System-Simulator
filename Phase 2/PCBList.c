/*
 * PCBLIST.C
 *
 * version 1.00
 * initial development February 2018
 *
 *

 */

#include "PCBList.h"

PCBNode* addPCBNode( PCBNode* firstNode, PCBNode* newNode )
{
  if ( firstNode != NULL )
  {
      firstNode->nextPCB = addPCBNode( firstNode->nextPCB, newNode );
  }
  else
  {
    firstNode = ( PCBNode* )malloc( sizeof( PCBNode ) );
    firstNode->process = newNode->process;
    firstNode->state = newNode->state;
    firstNode->nextPCB = NULL;
  }

  return firstNode;
}

int getProcesses( Node* firstNode, PCBNode** firstPCB )
{
  PCBNode* tempPCB;
  Node* tempNode;

  while ( firstNode != NULL )
  {
    if ( firstNode->commCode == 'S' )
    {
      if ( strCompare( firstNode->action, "end" ) == 0 )
      {
        return NO_ERROR_MSG;
      }
    }

    if ( firstNode->commCode == 'A' )
    {
      tempPCB = ( PCBNode* )malloc( sizeof( PCBNode ) );

      tempPCB->nextPCB = NULL;
      tempPCB->process = NULL;
      tempPCB->state = New;

      firstNode = firstNode->next;

      while ( firstNode->commCode != 'A' )
      {

        tempNode = malloc( sizeof( Node ) );
        copyNode( firstNode, tempNode );
        tempPCB->process = addNode( tempPCB->process, tempNode );
        free ( tempNode );
        firstNode = firstNode->next;
      }

      *firstPCB = addPCBNode( *firstPCB, tempPCB );
      free( tempPCB );
    }

    firstNode = firstNode->next;
  }

  return END_FILE_FOUND_MSG;
}

int runProcesses( Set* currSet, PCBNode* currPCB )
{

  Boolean logToMonitor;
  Boolean logToFile;
  int processNum;
  int* runTime;
  char logText[90];
  char timeText[90];
  Node* currInstr;
  logNode* newLog = NULL;
  pthread_t tid;

  if ( strCompare( currSet->logTo, "Monitor" ) == 0 )
  {
    logToMonitor = True;
    logToFile = False;
  }

  else if ( strCompare( currSet->logTo, "File" ) == 0 )
  {
    logToFile = True;
    logToMonitor = False;
  }

  else
  {
    logToFile = True;
    logToMonitor = True;
  }

  accessTimer( ZERO_TIMER, timeText );
  sprintf( logText, "Time: %s, System Start\n", timeText );

  if ( logToFile )
  {
    addLogNode( newLog, logText );
  }

  if ( logToMonitor )
  {
    printf( "%s", logText );
  }

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: Begin PCB Creation\n", timeText );

  if ( logToFile )
  {
    addLogNode( newLog, logText );
  }

  if ( logToMonitor )
  {
    printf( "%s", logText );
  }

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: All processes initialized in 'new' state\n", timeText );

  if ( logToFile )
  {
    addLogNode( newLog, logText );
  }

  if ( logToMonitor )
  {
    printf( "%s", logText );
  }

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: All processes now set in 'ready' state\n", timeText );

  if ( logToFile )
  {
    addLogNode( newLog, logText );
  }

  if ( logToMonitor )
  {
    printf( "%s", logText );
  }

  while ( currPCB != NULL )
  {
    currInstr = currPCB->process;
    accessTimer( LAP_TIMER, timeText );
    sprintf( logText, "Time: %s, OS: FCFS-N strategy selects process %d with time: %d milliseconds\n",
            timeText, processNum, getRunTime( currPCB->process, currSet ) );

    if ( logToFile )
    {
      addLogNode( newLog, logText );
    }

    if ( logToMonitor )
    {
      printf( "%s", logText );
    }

    while ( currInstr != NULL )
    {

      accessTimer( LAP_TIMER, timeText );

      if ( currInstr->commCode == 'P' )
      {
        sprintf( logText, "Time: %s, Process %d, run operation start \n", timeText, processNum );

        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }

        runTime = malloc( sizeof( int ) );
        *runTime = ( currInstr->val * currSet->pcTime );
        pthread_create( &tid, NULL, runThread, ( void* ) runTime );
        pthread_join( tid, NULL );
        free ( runTime );

        accessTimer( LAP_TIMER, timeText );
        sprintf( logText, "Time: %s, Process %d, run operation end \n", timeText, processNum );
        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }
      }

      else if ( currInstr->commCode == 'I' )
      {
        sprintf( logText, "Time: %s, Process %d, %s input start \n", timeText, processNum, currInstr->action );

        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }

        runTime = malloc( sizeof( int ) );
        *runTime = ( currInstr->val * currSet->iocTime );
        pthread_create( &tid, NULL, runThread, ( void* ) runTime );
        pthread_join( tid, NULL );
        free ( runTime );

        accessTimer( LAP_TIMER, timeText );
        sprintf( logText, "Time: %s, Process %d, %s input end \n", timeText, processNum, currInstr->action );
        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }
      }

      else if ( currInstr->commCode == 'O' )
      {
        sprintf( logText, "Time: %s, Process %d, %s output start \n", timeText, processNum, currInstr->action );

        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }

        runTime = malloc( sizeof( int ) );
        *runTime = ( currInstr->val * currSet->iocTime );
        pthread_create( &tid, NULL, runThread, ( void* ) runTime );
        pthread_join( tid, NULL );
        free ( runTime );

        accessTimer( LAP_TIMER, timeText );
        sprintf( logText, "Time: %s, Process %d, %s output end \n", timeText, processNum, currInstr->action );
        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }
      }

      else if ( currInstr->commCode == 'M' )
      {
        sprintf( logText, "Time: %s, Process %d, Memory management %s action start \n", timeText, processNum, currInstr->action );
        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }

        accessTimer( LAP_TIMER, timeText );

        sprintf( logText, "Time: %s, Process %d, Memory management %s action end\n", timeText, processNum, currInstr->action );
        if ( logToFile )
        {
          addLogNode( newLog, logText );
        }

        if ( logToMonitor )
        {
          printf( "%s", logText );
        }
      }

      else
      {
        return INCORRECT_FILE_ERR;
      }

      currInstr = currInstr->next;
    }

	accessTimer( LAP_TIMER, timeText );
	currPCB->state = Exit;
	sprintf( logText, "Time: %s, Process %d, set in exit state\n", timeText, processNum );

	if ( logToFile )
	{
	  addLogNode( newLog, logText );
	}

	if ( logToMonitor )
	{
	  printf( "%s", logText );
	}

    currPCB = currPCB->nextPCB;
    processNum ++;
  }

  accessTimer( LAP_TIMER, timeText );

  sprintf( logText, "Time: %s, System stop\n", timeText );
  if ( logToFile )
  {
		addLogNode( newLog, logText );
		logging( currSet->fPath, newLog );
  }

  if ( logToMonitor )
  {
		printf( "%s", logText );
  }

  return NO_ERROR_MSG;

}

int getRunTime( Node* currNode, Set* currSet )
{
  int count = 0;

  while ( currNode != NULL )
  {
    if ( currNode->commCode == 'P' )
    {
      count += ( currNode->val * currSet->pcTime );
    }

    else if ( currNode->commCode == 'I' || currNode->commCode == 'O' )
    {
      count += ( currNode->val * currSet->iocTime );
    }
    currNode = currNode->next;
  }

  return count;
}

PCBNode* clearPCB( PCBNode* firstNode )
{
	if ( firstNode == NULL )
	{
		return NULL;
	}

	if ( firstNode->nextPCB != NULL )
	{
		clearPCB( firstNode->nextPCB );
	}

	clearList( firstNode->process );
	free( firstNode );
	firstNode = NULL;
	return firstNode;

}

void* runThread( void* time )
{
	runTimer( *( int* ) time );
	pthread_exit( NULL );
}
