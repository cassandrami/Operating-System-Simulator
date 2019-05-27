/*

 * INTERRUPT.C

 * version 1.00
 * initial development April 2018

 */

#include "interrupt.h"

Interrupt* getInterrupt(float interruptTime, Interrupt** first)
{
  Interrupt* storeFirst = (*first);

  if (*first != NULL)
  {
    if ((*first)->interruptTime <= interruptTime)
    {
      (*first) = (*first)->next;
      return storeFirst;
    }
  }

  return NULL;
}

Interrupt* newInterrupt(int processNum, Interrupt* first, char opCode[20],
                        char interrType[20], float interruptTime)
{
  Interrupt* temp;
  Interrupt* curr;

  if (first == NULL)
  {
    first = malloc(sizeof(Interrupt));

    first->processNum = processNum;
    first->interruptTime = interruptTime;
    copyString(opCode, first->opCode);
    copyString(interrType, first->interrType);
    first->next = NULL;

    return first;
  }

  else if (interruptTime <= first->interruptTime)
  {
    curr = first;
    first = malloc(sizeof(Interrupt));

    first->processNum = processNum;
    first->interruptTime = interruptTime;
    copyString(opCode, first->opCode);
    copyString(interrType, first->interrType);
    first->next = curr;

    return first;
  }

  curr = first;
  while (curr->next != NULL)
  {
    if (interruptTime <= curr->next->interruptTime)
    {
      temp = curr->next;
      curr->next = malloc(sizeof(Interrupt));

      curr->next->processNum = processNum;
      curr->next->interruptTime = interruptTime;
      copyString(opCode, curr->next->opCode);
      copyString(interrType, curr->next->interrType);
      curr->next->next = temp;

      return first;
    }
    curr = curr->next;
  }

  curr->next = malloc(sizeof(Interrupt));

  curr->next->processNum = processNum;
  curr->next->interruptTime = interruptTime;
  copyString(opCode, curr->next->opCode);
  copyString(interrType, curr->next->interrType);
  curr->next->next = NULL;

  return first;

}
