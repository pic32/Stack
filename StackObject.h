/*
	Date: March 26, 2011
	File Name: StackObject.h
	Version: 1.04
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file contains the definition of the STACK
	data structure.  This file was created just to 
	further seperate out the structure of the library.
*/

#ifndef STACK_OBJECT_H
	#define STACK_OBJECT_H

#include "GenericTypeDefs.h"

/*
	The following struct is a node within the Stack.
	Each node points to a piece of data that the user
	passed in when calling StackPush().
*/
struct _StackNode
{
	/**
	* A pointer to the data that the STACK_NODE will point to.
	*/
	void *Data;

	/**
	* A pointer to the next STACK_NODE in the STACK.
	*/
	struct _StackNode *Next;
};

typedef struct _StackNode STACK_NODE;

/*
	The following struct is the Stack Head itself.
	There is only one of these per Stack, and it points
	to the beginning of the Stack (the first STACK_NODE).
*/
struct _Stack
{
	/**
	* The current size of a STACK.  When initialized a STACK has a size of 0.
	*/
	UINT32 Size;

	/**
	* A pointer to the first STACK_NODE in the STACK.  This will point to (STACK_NODE*)NULL
	* if there are no STACK_NODE's currently in the STACK.
	*/
	STACK_NODE *TopOfStack;

	#if(USING_STACK_DEPENDENT_FREE_METHOD == 1)
		void (*StackFreeMethod)(void *Data);
	#endif // end of USING_STACK_DEPENDENT_FREE_METHOD
};

typedef struct _Stack STACK;

#endif // end of STACK_OBJECT_H
