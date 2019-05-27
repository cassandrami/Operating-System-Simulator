
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
const int BASE_FACTOR = 1000000;
const int OFF_FACTOR = 1000;

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
    while ( *first == *second)
    {

      if ( *first == '\0' && *second == '\0' )
      {
        return 0;
      }

      first++;
      second++;
    }

    return ( int )( *first ) - ( int )( *second );
}

//atoi
int strInt( char *str )
{
    if ( str == NULL )
    {
      return 0;
    }

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

//string to float
float strFloat( char *str )
{
  int num;
  int decimal;

  float rmndr = 0;
  float factor = 1;

  for ( decimal = 0; *str; str++ )
  {
    if ( *str == '.' )
    {
      decimal = 1;
      continue;
    }

    num = *str - '0';

    if ( num >= 0 && num <= 9 )
    {
      if ( decimal )
      {
        factor /= 10.0f;
      }

      rmndr = rmndr * 10.0f + (float)num;
    }
  }
  return rmndr * factor;
}
