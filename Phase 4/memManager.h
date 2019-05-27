/*
 * memManager.H
 *
 * version 1.00
 * initial development April 2018
 *
 *
 */

#include "functions.h"

typedef struct MMUList
{
	int processNum;
	int commValue;
	struct MMUList* next;

} MMUList;

int calcBase( int commValue );
int calcOffset( int commValue );
int calcSegment( int commValue );

MMUList* clearMMU( MMUList* first );
MMUList* addMMUNode( MMUList* first, int commValue, int processNum );

Boolean didAllocate( MMUList* first, int commValue );
Boolean didAccess( MMUList* first, int commValue, int processNum );
