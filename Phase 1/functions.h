
/*
 * FUNCTIONS.H
 *
 * version 1.00
 * initial development January 2018
 *
 *

 */

#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdio.h>
#include <stdlib.h>

//constants
const int MAXLEN;
const int STDLEN;
const char SEMICOLON;
const char SPACE;
const char COLON;
const char NEWLINE;
const char NULL_CHAR;
const char READ_ONLY[ 1 ];
const char PERIOD;
const char E_CHAR;

typedef int Boolean;
const Boolean True;
const Boolean False;

enum MESSAGE_CODES { UNKNOWN_ERR = -1000, FILE_OPEN_ERR = 0,
                   INCOMPLETE_FILE_ERR = 0, NO_ERROR_MSG = 0,
                   INCORRECT_FILE_ERR = 80, FILE_END_ERR = 80,
                   END_FILE_FOUND_MSG = 80};

//declaring functions written in functions.c
int strCompare( char *first, char *second );
int strInt( char *str );
int copyString( char *first, char *second );

#endif
