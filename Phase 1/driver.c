/*
 * DRIVER.C
 *
 * version 1.00
 * initial development January 2018
 *
 *

 */

#include "driver.h"

int main( int argc, char *argv[] )
{
  Set *mySet = malloc( sizeof( Set ) );
  getData( mySet, argv[1] );
  Node *myNode = NULL;
  getMetaData( &myNode, mySet->fPath, mySet->logPath );
  clearList( myNode );

  free ( mySet );
  mySet = NULL;

  return 1;




}
