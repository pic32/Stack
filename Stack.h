/*
	Date: March 26, 2011
	File Name: Stack.h
	Version: 1.04
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file contains all the the method headers for interfacing to the
	Stack library.  This should be included in any file that references
	a STACK.  All methods and macro's have their documentation above
	their declaration.
*/

/*! \mainpage Stack Library
 *  \brief This is a Library written in C for manipulating a Stack Data Structure.
 *  \author brodie
 *  \version 1.04
 *  \date   March 26, 2011
 */

#ifndef STACK_H
	#define STACK_H

#include "GenericTypeDefs.h"
#include "StackConfig.h"
#include "StackObject.h"

/*
	Function: STACK *CreateStack(STACK *Stack)

	Parameters: 
		STACK *Stack - The address at which the STACK will be inititalized.
		If NULL is passed in then this method will create a STACK out of a
		the heap with a call to StackMemAlloc()(User Supplied Define).

		void(*CustomFreeMethod)(void *Data) - A pointer to a method that the
		user defines.  Each time a STACK_NODE is deleted this method will
		be called to delete the data at the STACK_NODE.

	Returns:
		STACK* - The address at which the newly initialized STACK resides
		in memory.  If a new STACK could not be created then (STACK*)NULL is returned.

	Description: Creates a new STACK in memory.

	Notes: None
*/
/**
		* @brief Initializes a STACK, and can create a STACK.
		* @param *Stack- A pointer to an already allocate STACK or a NULL STACK 
		pointer to create a STACK from StackMemAlloc().
		* @param *CustomFreeMethod - A method called by the STACK Library to delete
		a piece of data that a STACK_NODE points to.
		* @return *STACK - The address of the STACK in memory.  If a STACK could
		not be allocated, returns a NULL STACK pointer.
		* @note None
		* @sa StackMemAlloc()
		* @since v1.0
*/
STACK *CreateStack(STACK *Stack, void (*CustomFreeMethod)(void *Data));

/*
	Function: BOOL StackPush(STACK *Stack, const void *Data)

	Parameters: 
		STACK *Stack - The address at which the STACK resides in memory.
		const void *Data - The data to store on top of the STACK.

	Returns:
		BOOL - Will return TRUE if the const void *Data was successfully
		stored in the STACK. Will return FALSE if the STACK pointer was
		NULL or if there is no more room in the heap to allocate for a new
		item on the STACK.

	Description: Pushes one item onto the STACK.

	Notes: None.
*/
/**
		* @brief Puts a new STACK_NODE with it's accompanying data on top of the STACK.
		* @param *Stack - The address at which the STACK resides in memory.
		* @param *Data \a- A void pointer to the address at which the data that 
		will be put into the STACK resides at.
		* @return BOOL - TRUE if the operation was successful.  FALSE if there 
		was not enough memory to add a STACK_NODE.
		* @note None
		* @sa StackMemAlloc()
		* @since v1.0
*/
BOOL StackPush(STACK *Stack, const void *Data);

/*
	Function: void *StackPop(STACK *Stack)

	Parameters: 
		STACK *Stack - The address at which the STACK resides in memory.

	Returns:
		void* - The data of the next item that was removed from the STACK.  
		If no items are available or if the Stack is a NULL reference
		then this method returns (void*)NULL.

	Description: Pops one item from the STACK.  That item is no longer
	in the STACK.  It is the users responsibility to free any memory which
	the returned void pointer is pointing to if necessary.

	Notes: None
*/
/**
		* @brief Removes and returns the next set of data on top of the STACK.
		* @param *Stack - The address at which the STACK resides in memory.
		* @return *void - The address in memory of the top STACK_NODE in the 
		passed in STACK, or (void*)NULL if unsuccessful.  The STACK_NODE 
		is torn down from memory with StackMemDealloc().
		* @note This method will free the top STACK_NODE with a call to StackMemDealloc().
		* @sa StackMemDealloc()
		* @since v1.0
*/
void *StackPop(STACK *Stack);

/*
	Function: void *StackPeek(STACK *Stack)

	Parameters: 
		STACK *Stack - The address at which the STACK resides in memory.

	Returns:
		void* - The data of the next item to be removed from the STACK.  
		If no items are available or if the Stack is NULL then this 
		method returns NULL.  The node which holds the returned data still
		resides in the STACK.

	Description: Returns but does not delete the next piece of data in the
	STACK.

	Notes: USING_STACK_PEEK_METHOD in StackConfig.h must be defined as 1 to use method.
*/
/**
		* @brief Returns the next set of data on top of the STACK.
		* @param *Stack - The address at which the STACK resides in memory.
		* @return void* - The address of the next piece of data on top of the STACK, 
		or (void*)NULL if unsuccessful.
		* @note This method will return but not remove from the STACK, the next 
		set of data on top of the STACK.  USING_STACK_PEEK_METHOD in StackConfig.h must be defined as 1 to use method.
		* @sa None
		* @since v1.0
*/
#if (USING_STACK_PEEK_METHOD == 1)
	void *StackPeek(STACK *Stack);
#endif // end of USING_STACK_PEEK_METHOD

/*
	Function: BOOL StackClear(STACK *Stack)

	Parameters: 
		STACK *Stack - The address at which the STACK resides in memory.

	Returns:
		BOOL - TRUE if the STACK was successfully torn down out of memory, or it
			   the Stack had a size of 0.
		FALSE - If a NULL referenced STACK was passed in.

	Description: This method will free up all the memory used up by the
	STACK_NODE's within the STACK.  It will free all nodes with a call
	to StackMemDealloc(), and will only free the data of a node if a method
	was supplied at the stack's creation.  The STACK structure will still
	exist.

	Notes: USING_STACK_CLEAR_METHOD in StackConfig.h must be defined as 1 to use method.
*/
/**
		* @brief Frees from memory all of a STACK's nodes and data(optional).
		* @param *Stack - The address at which the STACK resides in memory.
		* @return BOOL - TRUE if all the STACK_NODE's and data was successfully freed,
		FALSE otherwise.
		* @note This method will free up all the memory used up by the
		STACK_NODE's within the STACK.  It will free all nodes with a call
		to StackMemDealloc(), and will only free the data of a node if a method
		was supplied at the stack's creation.  The STACK structure will still
		exist.  USING_STACK_CLEAR_METHOD in StackConfig.h must be defined as 1 to use method, and
		USING_STACK_DEPENDENT_FREE_METHOD must be defined as 1 to enable the custion free method.
		* @sa StackMemDealloc()
		* @since v1.0
*/
	// add in a method for deleting data
#if (USING_STACK_CLEAR_METHOD == 1)
	BOOL StackClear(STACK *Stack);
#endif // end of USING_STACK_CLEAR_METHOD

/*
	Function: UINT32 StackGetSize(STACK *Stack)

	Parameters: 
		STACK *Stack - The address at which the STACK resides in memory.

	Returns:
		UINT32 - The number of elements currently found in the STACK 
		passed in.  If the STACK referenced is NULL then this method will 
		return 0.

	Description: Returns the size of the referenced STACK.

	Notes: USING_STACK_GET_SIZE_METHOD in StackConfig.h must be defined as 1 to use method.
*/
/**
		* @brief Will return the number of STACK_NODES within a STACK.
		* @param *Stack - The address at which the STACK resides in memory.
		* @return UINT32 - The number of STACK_NODE's in the STACK.  
		If the Stack is eqaul to (STACK*)NULL then 0 is returned.
		* @note USING_STACK_GET_SIZE_METHOD in StackConfig.h must be defined as 1 to use method.
		* @sa None
		* @since v1.0
*/
#if (USING_STACK_GET_SIZE_METHOD == 1)
	UINT32 StackGetSize(STACK *Stack);
#endif //end of USING_STACK_GET_SIZE

/*
	Function: UINT32 StackGetSizeInBytes(STACK *Stack, UINT32 DataSizeInBytes)

	Parameters: 
		STACK *Stack - The address at which the STACK resides in memory.
		UINT32 DataSizeInBytes - The size in bytes of the data being stored
								 at each STACK_NODE for the referenced STACK.

	Returns:
		UINT32 - The size in bytes that the entire STACK Data Structure takes up.  This
		takes into account the size of each STACK_NODE within the STACK, the size of a 
		STACK and the size of each data element a STACK_NODE is pointing to.  If the user
		is not pointing to anything with the STACK_NODES's then DataSizeInBytes should be 
		set to 0.  If the STACK referenced is NULL then this method will return 0.

	Description: Returns the size of the referenced STACK in bytes.

	Notes: This method does not take into account how much memory is used to allocate 
	memory through StackMemAlloc().  USING_STACK_GET_SIZE_IN_BYTES_METHOD in StackConfig.h must be defined as 1 to use method.
*/
/**
		* @brief Returns how much memory in bytes a STACK consumes.
		* @param *Stack - The address at which the STACK resides in memory.
		* @param DataSizeInBytes - The size in bytes of the data being stored 
		at each STACK_NODE for the referenced STACK.  Should be 0 if the data
		in each STACK_NODE is not used as a pointer.
		* @return UINT32 - Returns the size of the referenced STACK in bytes.  Will
		return 0 if unsuccessful.
		* @note This method will take into account the sizeof STACK, plus
		the size of each STACK_NODE.  This method will not take into account
		the amount of memory needed to allocate memory from StackMemAlloc().
		USING_STACK_GET_SIZE_IN_BYTES_METHOD in StackConfig.h must be defined as 1 to use method.
		* @sa None
		* @since v1.0
*/
#if (USING_STACK_GET_SIZE_IN_BYTES_METHOD == 1)
	UINT32 StackGetSizeInBytes(STACK *Stack, UINT32 DataSizeInBytes);
#endif // end of USING_STACK_GET_SIZE_IN_BYTES_METHOD

/*
	Function: const BYTE *StackGetLibraryVersion(void)

	Parameters: 
		None

	Returns:
		const BYTE* - The library version of the Stack Library.  This string is 
		(BYTE)NULL terminated.

	Description: Returns the version number of the Stack Library.

	Notes: USING_STACK_GET_LIBRARY_VERSION in StackConfig.h must be defined as 1 to use method.
*/
/**
		* @brief Returns the version number of the Stack Library.
		* @param None
		* @return const BYTE* - The library version of the Stack Library.
		* @note This string is (BYTE)NULL terminated.   USING_STACK_GET_LIBRARY_VERSION in StackConfig.h must be defined as 1 to use method.
		* @sa None
		* @since v1.03
*/
#if (USING_STACK_GET_LIBRARY_VERSION == 1)
	const BYTE *StackGetLibraryVersion(void);
#endif // end of USING_STACK_GET_LIBRARY_VERSION

/*
	Macro: UINT32 StackGetSizeOfNodeInBytes(UINT32 DataSizeInBytes)

	Parameters: 
		UINT32 DataSizeInBytes - The size in bytes of the data being stored in a STACK.

	Returns:
		UINT32 - The size in bytes that the STACK_NODE takes up with it's accompaning
		data.

	Description: Returns the size of a STACK_NODE and it's data in bytes.

	Notes: This method does not take into account how much memory is used to allocate 
	memory through StackMemAlloc().
*/
#define StackGetSizeOfNodeInBytes(Size)			(UINT32)(Size + sizeof(STACK_NODE))

/*
	Macro: BOOL StackIsNull(STACK *Stack)

	Parameters: 
		STACK *Stack - The STACK to check if it's NULL or not.

	Returns:
		BOOL - TRUE if the STACK is NULL, FALSE otherwise.

	Description: Checks to see if a STACK is NULL or not.

	Notes: None
*/
#define StackIsNull(Stack)						(Stack == (STACK*)NULL)

/*
	Macro: BOOL StackIsEmpty(STACK *Stack)

	Parameters: 
		STACK *Stack - The STACK to check if it's empty or not.

	Returns:
		BOOL - TRUE if the STACK is empty, FALSE otherwise.

	Description: Checks to see if the STACK is empty.

	Notes: None
*/
#define StackIsEmpty(Stack)						(Stack->Size == (UINT32)0)

#endif // end of STACK_H
