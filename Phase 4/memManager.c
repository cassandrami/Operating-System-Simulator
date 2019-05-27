/*
 * memManager.c
 *
 * version 1.00
 * initial development April 2018
 *
 *
 */

#include "memManager.h"


int calcBase( int commValue )
{
	return ( int )( ( commValue / OFF_FACTOR ) % OFF_FACTOR );
}


int calcOffset( int commValue )
{
	return ( commValue % OFF_FACTOR );
}


int calcSegment( int commValue )
{
	return ( ( int )( commValue / BASE_FACTOR ) );
}


MMUList* clearMMU( MMUList* first )
{

	if ( first == NULL )
	{
		return NULL;
	}

	if ( first->next != NULL )
	{
		clearMMU( first->next );
	}

	free( first );
	first = NULL;
	return first;
}


MMUList* addMMUNode( MMUList* first, int commValue, int processNum )
{
	if ( first != NULL )
	{
		first->next = addMMUNode( first->next, commValue, processNum );
	}

	else
	{
		first = malloc( sizeof( MMUList ) );
		first->commValue = commValue;
		first->processNum = processNum;
		first->next = NULL;
	}
	return first;
}

Boolean didAllocate( MMUList* first, int commValue )
{
	int base = calcBase( commValue );
	int offset = calcOffset( commValue );
	int segment = calcSegment( commValue );

	int currBase;
	int currOffset;
	int currSegment;

	MMUList* currNode = first;

	while ( currNode != NULL )
	{
		currBase = calcBase( currNode->commValue );
		currOffset = calcOffset( currNode->commValue );
		currSegment = calcSegment( currNode->commValue );

		if ( segment == currSegment )
		{
			if ( base == currBase )
			{
				return False;
			}

			else if ( base > currBase )
			{
				if ( base < ( currBase + currOffset - 1 ) )
				{
					return False;
				}
			}

			else if ( base < currBase )
			{
				if ( ( base + offset - 1 ) > currBase )
				{
					return False;
				}
			}
		}

		currNode = currNode->next;
	}

	return True;
}


Boolean didAccess( MMUList* first, int commValue, int processNum )
{
	int base = calcBase( commValue );
	int offset = calcOffset( commValue );
	int segment = calcSegment( commValue );

	int currProcessNum;
	int currBase;
	int currOffset;
	int currSegment;
	MMUList* currNode = first;

	while ( currNode != NULL )
	{
		currBase = calcBase( currNode->commValue );
		currOffset = calcOffset( currNode->commValue );
		currSegment = calcSegment( currNode->commValue );
		currProcessNum = currNode->processNum;

		if ( segment == currSegment )
		{
			if ( base >= currBase )
			{
				if ( ( base + offset - 1 ) <= ( currBase + currOffset - 1 ) )
				{
					if ( currProcessNum == processNum )
					{
						return True;
					}
				}
			}

			else if ( base < currBase )
			{
				currNode = currNode->next;
				continue;
			}
		}

		currNode = currNode->next;
	}

	return False;
}
