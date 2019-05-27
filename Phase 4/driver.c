/*
 * DRIVER.C
 *
 * version 2.00
 * initial development April 2018
 *
 *

 */

#include "driver.h"

int main( int argc, char *argv[] )
{

  Set *mySet = malloc( sizeof ( Set ) );

  if ( argv[1] ==  NULL )
  {
    printf( "No file input, cannot run!\n" );
    return INCOMPLETE_FILE_ERR;
  }

  getData( mySet, argv[1] );
  Node *myNode = NULL;
  getMetaData( &myNode, mySet->fPath, mySet->logPath );

	PCBNode* newPCB = NULL;
	getProcesses( myNode, &newPCB, mySet );

  if ( strCompare( mySet->cSched, "FCFS-N" ) == 0 || strCompare( mySet->cSched, "SJF-N" ) == 0 )
	{
    runProcesses( mySet, newPCB );
  }
  else
  {
    runPreemptiveProcesses( mySet, newPCB );
  }

  clearList( myNode );
	clearPCB( newPCB );

  free ( mySet );
  mySet = NULL;

  return 1;




}
