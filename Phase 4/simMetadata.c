
/*
 * SIMMETADATA.C
 *
 * version 2.00
 * initial development January 2018
 * last edited February 2018
 *
 *
 Some solutions and styles here adapted from:
 -Michael Leverington Linked List(.c, .h)

 */


#include "simMetadata.h"

int getMetaData( Node **firstNode, char *fileName, char *logfile )
{
  FILE * fPtr;
  int strIndex, currChar;
  char temp;
  char strBuffer[ MAXLEN ], actionBuffer[ MAXLEN ];

  Node *newNode = NULL;

  fPtr = fopen( fileName, READ_ONLY );
  if ( fPtr ==  NULL )
  {
    return FILE_OPEN_ERR;
  }

  strIndex = 0;
  currChar = fgetc( fPtr );

  while ( ( feof( fPtr ) == 0 ) && currChar != ( int ) NEWLINE )
  {
    strBuffer[ strIndex ] = ( char )( currChar );
    strIndex++;
    strBuffer[ strIndex ] = NULL_CHAR;
    currChar = fgetc( fPtr );
  }


  if( strCompare( strBuffer, "Start Program Meta-Data Code:" ) != 0 )
  {
    fclose( fPtr );
    return INCORRECT_FILE_ERR;
  }

  while( feof( fPtr ) == 0 )
  {

    currChar = fgetc( fPtr );

    if ( feof( fPtr ) == 0 )
    {
      strIndex = 0;

      while ( currChar == (int) SPACE || currChar == ( int )( NEWLINE ) )
      {
        currChar = fgetc( fPtr );
      }

      int test = currChar == ( int )( 'E' );

      if ( test )
      {
        strIndex = 0;

        while ( currChar != ( int )( PERIOD ) )
        {
          strBuffer[ strIndex ] = ( char )( currChar );
          strIndex++;
          strBuffer[ strIndex ] = NULL_CHAR;
          currChar = fgetc( fPtr );
        }

        if( strCompare( strBuffer, "End Program Meta-Data Code" ) == 0 )
        {
          fclose( fPtr );
          return NO_ERROR_MSG;
        }
        fclose( fPtr );
        return FILE_END_ERR;
      }

      temp = ( char ) currChar;

      if ( validateCommand( temp ) == False )
      {
        return INCORRECT_FILE_ERR;
      }

      currChar = fgetc( fPtr );

      if (currChar != ( int )('(') )
      {
        return INCORRECT_FILE_ERR;
      }

      currChar = fgetc( fPtr );
      while ( currChar != (int)( ')' ) )
      {
        actionBuffer[ strIndex ] = ( char )( currChar );
        strIndex++;
        actionBuffer[ strIndex ] = NULL_CHAR;
        currChar = fgetc( fPtr );
      }

      currChar = fgetc( fPtr );

      strIndex = 0;
      while ( currChar != ( int )( SEMICOLON ) && currChar != ( int )( PERIOD ) )
      {
        strBuffer[ strIndex ] = ( char )( currChar );
        strIndex++;
        strBuffer[ strIndex ] = NULL_CHAR;
        currChar = fgetc( fPtr );
      }

      newNode = makeNode( temp, actionBuffer, strInt( strBuffer ) );
      *firstNode = addNode( *firstNode, newNode );
      free ( newNode );

    }
  }
  return 0;
}

Node* makeNode( char code, char *action, int value )
{
    Node *newNode = ( Node * )malloc( sizeof( Node ) );

    newNode->commCode = code;
    copyString( action, newNode->action );
    newNode->val = value;
    newNode->next = NULL;

    return newNode;
}

Node* addNode( Node *firstNode, Node *newNode )
{
    if ( firstNode != NULL )
    {
        firstNode->next = addNode( firstNode->next, newNode );
    }
    else
    {
      firstNode = makeNode( newNode->commCode, newNode->action, newNode->val );
    }
    return firstNode;
}

Node* clearList( Node *firstNode )
{
    if ( firstNode == NULL )
    {
        return NULL;
    }

    if ( firstNode->next != NULL )
    {
        clearList( firstNode->next );
    }

    free ( firstNode );
    firstNode = NULL;
    return firstNode;
}

int validateCommand( char temp )
{
  if ( temp != 'S' && temp != 'A'
       && temp != 'P' && temp != 'M'
       && temp != 'I' && temp != 'O' )
  {
    return False;
  }
  return True;
}

int logMetaData( Node *node, char *logfile )
{
  Node *tempNode = node;

  printf( "\n\n\n" );
  printf( "MetaData File Log:\n\n\n" );

  while (tempNode != NULL)
  {
    printf( "The component letter is: %c\n", tempNode->commCode );
    printf( "The operation string is: %s\n", tempNode->action );
    printf( "The cycle time is: %i\n", tempNode->val );
    printf( "\n\n" );

    tempNode = tempNode->next;
  }

  if ( strCompare( logfile, "nologfile" ) == 0 )
  {
    FILE *filePointer;

    filePointer = fopen( logfile, "a" );
    fprintf( filePointer, "\n\n\n" );
    fprintf( filePointer, "MetaData File Log:\n\n\n" );



    while (tempNode != NULL)
    {
      fprintf( filePointer, "The component letter is: %c\n", tempNode->commCode );
      fprintf( filePointer, "The operation string is: %s\n", tempNode->action );
      fprintf( filePointer, "The cycle time is: %i\n", tempNode->val );
      fprintf( filePointer, "\n\n");

      printf( "The component letter is: %c\n", tempNode->commCode );
      printf( "The operation string is: %s\n", tempNode->action );
      printf( "The cycle time is: %i\n", tempNode->val );
      printf( "\n\n" );

      tempNode = tempNode->next;
    }

    fclose( filePointer );
  }

  return 0;
}

void copyNode( Node* currNode, Node* destNode )
{
  destNode->commCode = currNode->commCode;
  copyString(currNode->action, destNode->action);
  destNode->val = currNode->val;
}
