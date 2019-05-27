
/*
 *
 * FUNCTIONS.C
 *
 * version 1.00
 * initial development January 2018
 *
 *

Some solutions and styles here adapted from:

-https://stackoverflow.com/questions/232693/
-https://www.geeksforgeeks.org/write-your-own-atoi/
-https://stackoverflow.com/questions/40703055/

*/

#include "functions.h"

//constants
const int MAXLEN = 120;
const int STDLEN = 60;
const char SEMICOLON = ';';
const char SPACE = ' ';
const char COLON = ':';
const char NEWLINE = '\n';
const char NULL_CHAR = '\0';
const char READ_ONLY[] = "r";
const char PERIOD = '.';
const char E_CHAR = 'E';

//strcmp
int strCompare( char *first, char *second )
{
    while ( *first && *second && *first == *second ) { ++first; ++second; }
    return ( unsigned char )( *first ) - ( unsigned char )( *second );
}

//atoi
int strInt( char *str )
{
    if ( str == NULL )
       return 0;

    int result = 0;
    int counter = 0;


    for (; str[ counter ] != '\0' && str[ counter ] != '.'; counter++ )
    {
        result = result*10 + str[ counter ] - '0';
    }

    return result;

}

//strcpy
int copyString( char *first, char *second )
{
  int counter = 0;
  while ( first[counter] != '\0' )
  {
    second[ counter ] = first[ counter ];
    counter++;
  }
  second[ counter ] = '\0';
  return 0;
}
