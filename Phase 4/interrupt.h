/*
 * INTERRUPT.H
 *
 * version 1.00
 * initial development April 2018
 *
 *

 */

#include "functions.h"

typedef struct Interrupt
{

  int processNum;
  float interruptTime;
  struct Interrupt* next;
  char opCode[20];
  char interrType[20];
  
} Interrupt;

Interrupt* getInterrupt( float interruptTime, Interrupt** first );
Interrupt* newInterrupt( int processNum, Interrupt* first, char opCode[20],
                         char interrType[20], float interruptTime );
