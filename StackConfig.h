/*
	Date: March 26, 2011
	File Name: StackConfig.h
	Version: 1.04
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file configures the options built into the Stack Library.
	The below set of defines allows the user to enable certain methods
	located inside the Stack library.

	It also allows the user to define how the Stack library will
	allocate and deallocate memory for new nodes.

	All methods are thread safe(re-entrant), with the potential exception 
	of StackCreate, StackAdd, StackRemove, and StackClear.  The reason
	for this is that it all depends on how the user defines the way the 
	Stack library will allocate, deallocate memory.
*/

#ifndef STACK_CONFIG_H
	#define STACK_CONFIG_H

/**
	*Set USING_STACK_PEEK_METHOD to 1 to enable the
	StackPeek method.
*/
#define USING_STACK_PEEK_METHOD							1

/**
	*Set USING_STACK_CLEAR_METHOD to 1 to enable the
	StackClear method.
*/ 
#define USING_STACK_CLEAR_METHOD						1

/**
	*Set USING_STACK_GET_SIZE_METHOD to 1 to enable the
	StackGetSize method.
*/
#define USING_STACK_GET_SIZE_METHOD						1

/**
	*Set USING_STACK_GET_SIZE_IN_BYTES_METHOD to 1 to enable the
	StackGetSizeInBytes method.
*/
#define USING_STACK_GET_SIZE_IN_BYTES_METHOD			1

/**
	*Set USING_STACK_GET_LIBRARY_VERSION to 1 to enable the
	StackGetLibraryVersion method.
*/
#define USING_STACK_GET_LIBRARY_VERSION					1

/**
	*Set STACK_SAFE_MODE to 1 to enable the portions of code
	inside the STACK Library that check to make sure all passed
	in parameters are of a valid nature.
*/
#define STACK_SAFE_MODE									1

/**
	*This defines what method the Stack library will use to 
	allocate memory and deallocated.  This allows the Stack 
	library to be integrated into an OS.
*/
#define StackMemAlloc(Mem)								malloc(Mem)

/**
	*The method used for freeing up memory.
*/
#define StackMemDealloc(Mem)							free(Mem)

/**
	*Define USE_MALLOC as 1 to enable the stdlib.h file included
	with Stack.c.
*/
#define USE_MALLOC										1

/*
	*Define the below as 1 if each STACK is to store a custom
	method for freeing a STACK_NODE.
*/
#define USING_STACK_DEPENDENT_FREE_METHOD				1

/**
	*If the user isn't using malloc then include the file that will
	be needed for accessing whatever method MemAlloc() and MemDealloc()
	implement, below.
*/
//#include "Your memory file here.h"

#endif // end of STACK_CONFIG_H
