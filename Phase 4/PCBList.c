/*
 * PCBLIST.C
 *
 * version 3.00
 * initial development April 2018
 *
 *

 */

#include "PCBList.h"

PCBNode* checkAlgorithm( PCBNode* firstPCB, char* instruction )
{
	if ( firstPCB == NULL )
	{
		return NULL;
	}

	else if ( strCompare( instruction, "FCFS-N" ) == 0 || strCompare( instruction, "FCFS-P" ) == 0 )
	{
		return firstPCB;
	}

	else if ( strCompare( instruction, "SJF-N" ) == 0 || strCompare( instruction, "SRTF-P" ) == 0 )
	{
		firstPCB = sortProcesses( firstPCB );
	}


	else if ( strCompare( instruction, "RR-P" ) == 0 )
	{
		firstPCB = sortRR( firstPCB );
	}

	return firstPCB;
}

PCBNode* sortRR( PCBNode* firstPCB )
{
	int tempTime;
	int tempPNum;
	int tempState;

	Boolean didSwap;
	Node* tempProcess;
	PCBNode* first;
	PCBNode* currNode;

	currNode = NULL;

	if ( firstPCB == NULL )
	{
		return NULL;
	}

	do
	{
		didSwap = False;
		first = firstPCB;

		while ( first->nextPCB != currNode )
		{
			if ( first->state == Blocked )
			{

				tempTime = first->processTime;
				tempPNum = first->processNum;
				tempState = first->state;
				tempProcess = first->process;

				first->processTime = first->nextPCB->processTime;
				first->processNum = first->nextPCB->processNum;
				first->state = first->nextPCB->state;
				first->process = first->nextPCB->process;

				first->nextPCB->processTime = tempTime;
				first->nextPCB->processNum = tempPNum;
				first->nextPCB->state = tempState;
				first->nextPCB->process = tempProcess;

				didSwap = True;
			}
			first = first->nextPCB;
		}
		currNode = first;

	} while ( didSwap == True );

	return firstPCB;
}

PCBNode* sortProcesses( PCBNode* firstPCB )
{
	int tempTime;
	int tempPNum;
	int tempState;

	Boolean didSwap;
	Node* tempProcess;
	PCBNode* first;
	PCBNode* currNode;

	currNode = NULL;

	if ( firstPCB == NULL )
	{
		return NULL;
	}

	do
	{

		didSwap = False;
		first = firstPCB;

		while ( first->nextPCB != currNode )
		{
			if ( first->processTime > first->nextPCB->processTime )
			{

				tempTime = first->processTime;
				tempPNum = first->processNum;
				tempState = first->state;
				tempProcess = first->process;

				first->processTime = first->nextPCB->processTime;
				first->processNum = first->nextPCB->processNum;
				first->state = first->nextPCB->state;
				first->process = first->nextPCB->process;

				first->nextPCB->processTime = tempTime;
				first->nextPCB->processNum = tempPNum;
				first->nextPCB->state = tempState;
				first->nextPCB->process = tempProcess;

				didSwap = True;
			}
			first = first->nextPCB;
		}
		currNode = first;

	} while ( didSwap == True );

	return firstPCB;
}

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
		firstNode->currProcess = newNode->process;

		firstNode->processNum = newNode->processNum;
		firstNode->processTime = newNode->processTime;

  }

  return firstNode;
}

int getProcesses( Node* firstNode, PCBNode** firstPCB, Set* currSet )
{
  PCBNode* tempPCB;
  Node* tempNode;
	int counter = 0;

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

	  tempPCB->processNum = counter;
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

		tempPCB->processTime = getRunTime( tempPCB->process, currSet );

        *firstPCB = addPCBNode( *firstPCB, tempPCB );
        free( tempPCB );
		counter++;
    }

    firstNode = firstNode->next;
  }

  return END_FILE_FOUND_MSG;
}

PCBNode* findReadyProcess( PCBNode* first )
{
	while ( first != NULL )
	{
		if ( first->state == Ready )
		{
			return first;
		}
		first = first->nextPCB;
	}
	return NULL;
}

int runProcesses( Set* currSet, PCBNode* currPCB )
{

  Boolean logToMonitor;
  Boolean logToFile;

  int* runTime;

  char logText[90];
  char timeText[90];

  Node* currInstr;
  logNode* newLog = NULL;
  MMUList* firstMMU = NULL;
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
		newLog = (logNode*)malloc( sizeof( logNode ) );
  }

  else
  {
    logToFile = True;
    logToMonitor = True;
		newLog = (logNode*)malloc( sizeof( logNode ) );
  }

  accessTimer( ZERO_TIMER, timeText );
  sprintf( logText, "Time: %s, System Start\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: Begin PCB Creation\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: All processes initialized in 'new' state\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

  currPCB = checkAlgorithm( currPCB, currSet->cSched );
  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: All processes now set in 'ready' state\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

  while ( currPCB != NULL )
  {
    currInstr = currPCB->process;
    accessTimer( LAP_TIMER, timeText );
    sprintf( logText, "Time: %s, OS: %s strategy selects process %d with time: %d milliseconds\n",
            timeText, currSet->cSched, currPCB->processNum, getRunTime( currPCB->process, currSet ) );

    logRecords( logToFile, logToMonitor, newLog, logText );

    while ( currInstr != NULL )
    {

      accessTimer( LAP_TIMER, timeText );

      if ( currInstr->commCode == 'P' )
      {
        sprintf( logText, "Time: %s, Process %d, run operation start \n", timeText, currPCB->processNum );

        logRecords( logToFile, logToMonitor, newLog, logText );

        runTime = malloc( sizeof( int ) );
        *runTime = ( currInstr->val * currSet->pcTime );
        pthread_create( &tid, NULL, runThread, ( void* ) runTime );
        pthread_join( tid, NULL );
        free ( runTime );

        accessTimer( LAP_TIMER, timeText );
        sprintf( logText, "Time: %s, Process %d, run operation end \n", timeText, currPCB->processNum );

        logRecords( logToFile, logToMonitor, newLog, logText );
      }

      else if ( currInstr->commCode == 'I' )
      {
        sprintf( logText, "Time: %s, Process %d, %s input start \n", timeText, currPCB->processNum, currInstr->action );

        logRecords( logToFile, logToMonitor, newLog, logText );

        runTime = malloc( sizeof( int ) );
        *runTime = ( currInstr->val * currSet->iocTime );
        pthread_create( &tid, NULL, runThread, ( void* ) runTime );
        pthread_join( tid, NULL );
        free ( runTime );

        accessTimer( LAP_TIMER, timeText );
        sprintf( logText, "Time: %s, Process %d, %s input end \n", timeText, currPCB->processNum, currInstr->action );

        logRecords( logToFile, logToMonitor, newLog, logText );
      }

      else if ( currInstr->commCode == 'O' )
      {
        sprintf( logText, "Time: %s, Process %d, %s output start \n", timeText, currPCB->processNum, currInstr->action );

        logRecords( logToFile, logToMonitor, newLog, logText );

        runTime = malloc( sizeof( int ) );
        *runTime = ( currInstr->val * currSet->iocTime );
        pthread_create( &tid, NULL, runThread, ( void* ) runTime );
        pthread_join( tid, NULL );
        free ( runTime );

        accessTimer( LAP_TIMER, timeText );
        sprintf( logText, "Time: %s, Process %d, %s output end \n", timeText, currPCB->processNum, currInstr->action );

        logRecords( logToFile, logToMonitor, newLog, logText );
      }

      else if ( currInstr->commCode == 'M' )
      {
        sprintf( logText, "Time: %s, Process %d, MMU %s: %d/%d/%d start \n",
				 				timeText, currPCB->processNum, currInstr->action,
				 				calcSegment( currInstr->val ), calcBase( currInstr->val ), calcOffset( currInstr->val ) );

        logRecords( logToFile, logToMonitor, newLog, logText );

				if ( strCompare( currInstr->action, "allocate" ) == 0 )
				{
					if( didAllocate( firstMMU, currInstr->val ) )
					{
						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, Process %d, MMU %s: successful\n",
										 timeText, currPCB->processNum, currInstr->action );

		        logRecords( logToFile, logToMonitor, newLog, logText );
					}

					else
					{
						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, Process %d, MMU %s: failed\n",
										 timeText, currPCB->processNum, currInstr->action );

		        logRecords( logToFile, logToMonitor, newLog, logText );

						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, OS: Process %d, Segmentation Fault - Process ended\n",
										 timeText, currPCB->processNum );

		        logRecords( logToFile, logToMonitor, newLog, logText );

						break;
					}
				}

				else if ( strCompare( currInstr->action, "access" ) == 0 )
				{
					if( didAccess( firstMMU, currInstr->val, currPCB->processNum ) )
					{
						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, Process %d, MMU %s: successful\n",
										 timeText, currPCB->processNum, currInstr->action );

		        logRecords( logToFile, logToMonitor, newLog, logText );
					}

					else
					{
						accessTimer( LAP_TIMER, timeText );

						sprintf( logText, "Time: %s, Process %d, MMU %s: failed\n",
										 timeText, currPCB->processNum, currInstr->action );

						logRecords( logToFile, logToMonitor, newLog, logText );

						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, OS: Process %d, Segmentation Fault - Process ended\n",
										 timeText, currPCB->processNum );

		        logRecords( logToFile, logToMonitor, newLog, logText );

						break;
					}
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
		sprintf( logText, "Time: %s, OS: Process %d, set in exit state\n", timeText, currPCB->processNum );

		logRecords( logToFile, logToMonitor, newLog, logText );

    currPCB = currPCB->nextPCB;
  }

  accessTimer( LAP_TIMER, timeText );

  sprintf( logText, "Time: %s, System stop\n", timeText );
  if ( logToFile )
  {
		addLogNode( newLog, logText );
		printf("pls");
		logging( currSet->logPath, newLog );
  }

  if ( logToMonitor )
  {
		printf( "%s", logText );
  }

	clearLogNode( newLog );

  return NO_ERROR_MSG;

}

int runPreemptiveProcesses( Set* currSet, PCBNode* currPCB )
{

  Boolean logToMonitor;
  Boolean logToFile;

	int memAvailable = currSet->memAvail;
	int quantumTime;

	float currTime;
	float ioTime;

  char logText[90];
  char timeText[90];

  logNode* newLog = NULL;
  MMUList* firstMMU = NULL;

	PCBNode* tempPCB;
	PCBNode* storeFirst;

	Interrupt* list = NULL;
	Interrupt* currInterr = NULL;

  if ( strCompare( currSet->logTo, "Monitor" ) == 0 )
  {
    logToMonitor = True;
    logToFile = False;
  }

	else if ( strCompare( currSet->logTo, "File" ) == 0 )
  {
    logToFile = True;
    logToMonitor = False;
		newLog = (logNode*)malloc( sizeof( logNode ) );
  }

  else
  {
    logToFile = True;
    logToMonitor = True;
		newLog = (logNode*)malloc( sizeof( logNode ) );
  }

  accessTimer( ZERO_TIMER, timeText );
  sprintf( logText, "Time: %s, System Start\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: Begin PCB Creation\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: All processes initialized in 'new' state\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );

	storeFirst = currPCB;

	while ( currPCB != NULL )
	{
		currPCB->state = Ready;
		currPCB = currPCB->nextPCB;
	}

  accessTimer( LAP_TIMER, timeText );
  sprintf( logText, "Time: %s, OS: All processes now set in 'ready' state\n", timeText );

  logRecords( logToFile, logToMonitor, newLog, logText );


  while ( !isFinished( storeFirst ) )
  {
		if ( isIdle( storeFirst ) )
		{
			accessTimer( LAP_TIMER, timeText );
			sprintf( logText, "Time: %s, OS: CPU idle\n", timeText );
			logRecords( logToFile, logToMonitor, newLog, logText );
		}

		while ( isIdle( storeFirst ) )
		{
			accessTimer( LAP_TIMER, timeText );
			currTime = strFloat( timeText );
			currInterr = getInterrupt( currTime, &list );

			while ( currInterr != NULL)
			{
				accessTimer( LAP_TIMER, timeText );
				sprintf( logText, "Time: %s, OS: Interrupt, process %d\n", timeText, currInterr->processNum );
				logRecords( logToFile, logToMonitor, newLog, logText );

				accessTimer( LAP_TIMER, timeText );
				sprintf( logText, "Time: %s, Process %d, %s %s end\n", timeText, currInterr->processNum,
				 					currInterr->opCode, currInterr->interrType );
				logRecords( logToFile, logToMonitor, newLog, logText );

				tempPCB = storeFirst;
				while ( tempPCB != NULL )
				{
					if ( tempPCB->processNum == currInterr->processNum )
					{
						tempPCB->state = Ready;
						break;
					}

					tempPCB = tempPCB->nextPCB;
				}

				accessTimer( LAP_TIMER, timeText );
				sprintf( logText, "Time: %s, OS: Process %d set in ready state \n", timeText, currInterr->processNum );
				logRecords( logToFile, logToMonitor, newLog, logText );

				free( currInterr );

				storeFirst = checkAlgorithm( storeFirst, currSet->cSched );
				currInterr = getInterrupt( currTime, &list );
			}
		}


		storeFirst = checkAlgorithm( storeFirst, currSet->cSched );
		currPCB = findReadyProcess( storeFirst );

    accessTimer( LAP_TIMER, timeText );
    sprintf( logText, "Time: %s, OS: %s strategy selects process %d with time: %d milliseconds\n",
            timeText, currSet->cSched, currPCB->processNum, getRunTime( currPCB->currProcess, currSet ) );

    logRecords( logToFile, logToMonitor, newLog, logText );
		currPCB->state = Running;

		accessTimer( LAP_TIMER, timeText );
		sprintf( logText, "Time: %s, OS: Process %d set in running state \n", timeText, currPCB->processNum );
		logRecords( logToFile, logToMonitor, newLog, logText );

		quantumTime = currSet->qTime;

    while ( currPCB->currProcess != NULL && getRunTime( currPCB->currProcess, currSet ) &&
						quantumTime > 0 )
    {

      accessTimer( LAP_TIMER, timeText );

      if ( currPCB->currProcess->commCode == 'P' )
      {
				if ( quantumTime == currSet->qTime )
				{
					sprintf( logText, "Time: %s, Process %d, run operation start \n", timeText, currPCB->processNum );
	        logRecords( logToFile, logToMonitor, newLog, logText );
				}

				runTimer( currSet->pcTime );
				currPCB->currProcess->val -= 1;
				quantumTime -= 1;

				if ( currPCB->currProcess->val == 0 )
				{
					accessTimer( LAP_TIMER, timeText );
	        sprintf( logText, "Time: %s, Process %d, run operation end \n", timeText, currPCB->processNum );
	        logRecords( logToFile, logToMonitor, newLog, logText );

					currPCB->currProcess = currPCB->currProcess->next;

					accessTimer( LAP_TIMER, timeText );
	        sprintf( logText, "Time: %s, Process %d, run operation start \n", timeText, currPCB->processNum );
	        logRecords( logToFile, logToMonitor, newLog, logText );
				}

				currTime = strFloat( timeText );
				currInterr = getInterrupt( currTime, &list );

				if ( currInterr != NULL )
				{
					break;
				}
      }

      else if ( currPCB->currProcess->commCode == 'I' )
      {
        sprintf( logText, "Time: %s, Process %d, %s input start \n", timeText, currPCB->processNum,
				 				currPCB->currProcess->action );
        logRecords( logToFile, logToMonitor, newLog, logText );

        currTime = strFloat( timeText );
				ioTime = currPCB->currProcess->val * currSet->iocTime * .001;
				currTime += ioTime;

				list = newInterrupt( currPCB->processNum, list, currPCB->currProcess->action, "input", currTime );
				currPCB->currProcess = currPCB->currProcess->next;
				currPCB->state = Blocked;
				break;
      }

      else if ( currPCB->currProcess->commCode == 'O' )
      {
				sprintf( logText, "Time: %s, Process %d, %s output start \n", timeText, currPCB->processNum,
				 					currPCB->currProcess->action );
        logRecords( logToFile, logToMonitor, newLog, logText );

        currTime = strFloat( timeText );
				ioTime = currPCB->currProcess->val * currSet->iocTime * .001;
				currTime += ioTime;

				list = newInterrupt( currPCB->processNum, list, currPCB->currProcess->action, "output", currTime );
				currPCB->currProcess = currPCB->currProcess->next;
				currPCB->state = Blocked;
				break;
      }

      else if ( currPCB->currProcess->commCode == 'M' )
      {
        sprintf( logText, "Time: %s, Process %d, MMU %s: %d/%d/%d start \n",
				 				timeText, currPCB->processNum, currPCB->currProcess->action,
				 				calcSegment( currPCB->currProcess->val ), calcBase( currPCB->currProcess->val ),
								calcOffset( currPCB->currProcess->val ) );

        logRecords( logToFile, logToMonitor, newLog, logText );

				if ( strCompare( currPCB->currProcess->action, "allocate" ) == 0 )
				{

					if ( didAllocate( firstMMU, currPCB->currProcess->val )
							 && calcOffset( currPCB->currProcess->val ) <= memAvailable )
					{

						firstMMU = addMMUNode( firstMMU, currPCB->currProcess->val, currPCB->processNum );
						memAvailable -= calcOffset( currPCB->currProcess->val );

						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, Process %d, MMU %s: successful\n",
										 timeText, currPCB->processNum, currPCB->currProcess->action );

		        logRecords( logToFile, logToMonitor, newLog, logText );
						currPCB->currProcess = currPCB->currProcess->next;
					}

					else
					{
						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, Process %d, MMU %s: failed\n",
										 timeText, currPCB->processNum, currPCB->currProcess->action );

		        logRecords( logToFile, logToMonitor, newLog, logText );

						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, OS: Process %d, Segmentation Fault - Process ended\n",
										 timeText, currPCB->processNum );

		        logRecords( logToFile, logToMonitor, newLog, logText );
						currPCB->state = Exit;
						break;
					}
				}

				else if ( strCompare( currPCB->currProcess->action, "access" ) == 0 )
				{
					if( didAccess( firstMMU, currPCB->currProcess->val, currPCB->processNum ) )
					{

						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, Process %d, MMU %s: successful\n",
										 timeText, currPCB->processNum, currPCB->currProcess->action );

		        logRecords( logToFile, logToMonitor, newLog, logText );
						currPCB->currProcess = currPCB->currProcess->next;
					}

					else
					{
						accessTimer( LAP_TIMER, timeText );

						sprintf( logText, "Time: %s, Process %d, MMU %s: failed\n",
										 timeText, currPCB->processNum, currPCB->currProcess->action );

						logRecords( logToFile, logToMonitor, newLog, logText );

						accessTimer( LAP_TIMER, timeText );

		        sprintf( logText, "Time: %s, OS: Process %d, Segmentation Fault - Process ended\n",
										 timeText, currPCB->processNum );

		        logRecords( logToFile, logToMonitor, newLog, logText );
						currPCB->state = Exit;
						break;
					}
				}
      }

      else
      {
        return INCORRECT_FILE_ERR;
      }
    }

		if( currPCB->state == Blocked )
		{
			accessTimer( LAP_TIMER, timeText );
			sprintf( logText, "Time: %s, OS: Process %d, set in blocked state\n",
			 					timeText, currPCB->processNum );
			logRecords( logToFile, logToMonitor, newLog, logText );
		}

		else if ( getRunTime( currPCB->currProcess, currSet ) == 0 || currPCB->state == Exit )
		{
			accessTimer( LAP_TIMER, timeText );
			currPCB->state = Exit;
			sprintf( logText, "Time: %s, OS: Process %d, set in exit state\n", timeText, currPCB->processNum );

			logRecords( logToFile, logToMonitor, newLog, logText );
		}

		else if ( currInterr != NULL )
		{
			while ( currInterr != NULL)
			{
				accessTimer( LAP_TIMER, timeText );
				sprintf( logText, "Time: %s, OS: Interrupt, process %d\n", timeText, currInterr->processNum );
				logRecords( logToFile, logToMonitor, newLog, logText );

				if ( currPCB->state != Ready )
				{
					currPCB->state = Ready;
					accessTimer( LAP_TIMER, timeText );
					sprintf( logText, "Time: %s, OS: Process %d set in ready state \n", timeText, currPCB->processNum );
					logRecords( logToFile, logToMonitor, newLog, logText );

				}
				accessTimer( LAP_TIMER, timeText );
				sprintf( logText, "Time: %s, Process %d, %s %s end\n", timeText, currInterr->processNum, currInterr->opCode, currInterr->interrType );
				logRecords( logToFile, logToMonitor, newLog, logText );

				tempPCB = storeFirst;
				while ( tempPCB != NULL )
				{
					if ( tempPCB->processNum == currInterr->processNum )
					{
						tempPCB->state = Ready;
						break;
					}

					tempPCB = tempPCB->nextPCB;
				}

				accessTimer( LAP_TIMER, timeText );
				sprintf( logText, "Time: %s, OS: Process %d set in ready state \n", timeText, currInterr->processNum );
				logRecords( logToFile, logToMonitor, newLog, logText );

				free( currInterr );
				storeFirst = checkAlgorithm( storeFirst, currSet->cSched );
				currInterr = getInterrupt( currTime, &list );
			}
		}

		else if ( currPCB->state == Running )
		{
			accessTimer( LAP_TIMER, timeText );
			sprintf( logText, "Time: %s, OS: Process %d quantum time out\n", timeText, currInterr->processNum );
			logRecords( logToFile, logToMonitor, newLog, logText );

			currPCB->state = Ready;

			accessTimer( LAP_TIMER, timeText );
			sprintf( logText, "Time: %s, OS: Process %d set in ready state \n", timeText, currInterr->processNum );
			logRecords( logToFile, logToMonitor, newLog, logText );
		}
  }

  accessTimer( LAP_TIMER, timeText );

  sprintf( logText, "Time: %s, System stop\n", timeText );
  if ( logToFile )
  {
		addLogNode( newLog, logText );
		logging( currSet->logPath, newLog );
  }

  if ( logToMonitor )
  {
		printf( "%s", logText );
  }

	clearLogNode( newLog );

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

Boolean isIdle( PCBNode* first )
{
	while ( first != NULL )
	{
		if ( first->state == Ready )
		{
			return False;
		}

		first = first->nextPCB;
	}

	return True;
}

Boolean isFinished( PCBNode* first )
{
	while ( first != NULL )
	{
		if ( first->state != Exit )
		{
			return False;
		}

		first = first->nextPCB;
	}

	return True;
}
