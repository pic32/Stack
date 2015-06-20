/*
	Date: March 26, 2011
	File Name: Stack.c
	Version: 1.04
	IDE: Visual Studio 2010 Professional
	Compiler: C89

	Description:
	This file contains all the code which comprises 
	the Stack library.  For method descriptions see
	Stack.h.
*/

#include "Stack.h"

#if (USE_MALLOC == 1)
	#include "stdlib.h"
#endif // end of USE_MALLOC

STACK *CreateStack(STACK *Stack, void (*CustomFreeMethod)(void *Data))
{
	/*
		If Stack is equal to (STACK*)NULL then the user wants to
		create a new STACK in memory
	*/
	if(StackIsNull(Stack))
	{
		if((Stack = (STACK*)StackMemAlloc(sizeof(STACK))) == (STACK*)NULL)
		{
			return (STACK*)NULL;
		}
	}

	/*
		Initialize the STACK to it's defualt values.
	*/
	Stack->Size = (UINT32)0;
	Stack->TopOfStack = (STACK_NODE*)NULL;

	#if(USING_STACK_DEPENDENT_FREE_METHOD == 1)
		Stack->StackFreeMethod = (void (*)(void *))CustomFreeMethod;
	#endif // end of USING_STACK_DEPENDENT_FREE_METHOD

	return (STACK*)Stack;
}

BOOL StackPush(STACK *Stack, const void *Data)
{
	STACK_NODE *TempStackNode;

	#if (STACK_SAFE_MODE == 1)
		if(StackIsNull(Stack))
			return (BOOL)FALSE;
	#endif // end of STACK_SAFE_MODE

	/*
		Allocate room in memory for a new STACK_NODE.
	*/
	if((TempStackNode = (STACK_NODE*)StackMemAlloc(sizeof(STACK_NODE))) == (STACK_NODE*)NULL)
	{
		return (BOOL)FALSE;
	}

	/*
		Place the newly allocated STACK_NODE on top of the STACK have the new
		STACK_NODE point to the old top of stack.

		Also have the new STACK_NODE point to the data passed in by the user.

		Also increment the STACK size by 1 to reflect the new Stack size.
	*/
	TempStackNode->Next = (STACK_NODE*)(Stack->TopOfStack);
	TempStackNode->Data = (void*)Data;
	Stack->TopOfStack = (STACK_NODE*)TempStackNode;
	Stack->Size++;

	return (BOOL)TRUE;
}

void *StackPop(STACK *Stack)
{
	void *Data;
	STACK_NODE *TempStackNode;

	#if (STACK_SAFE_MODE == 1)
		if(StackIsNull(Stack))
			return (void*)NULL;
	
		if(StackIsEmpty(Stack))
			return (void*)NULL;
	#endif // end of STACK_SAFE_MODE

	/*
		Read in the top STACK_NODE's data to a temp pointer for returning later.
		Decrement the STACK's size to reflect the change and then free the top
		STACK_NODE from the STACK and have the new top of Stack point to the 
		next STACK_NODE in the Stack.
	*/
	TempStackNode = (STACK_NODE*)(Stack->TopOfStack);
	Data = (void*)(TempStackNode->Data);
	Stack->Size--;
	Stack->TopOfStack = (STACK_NODE*)(Stack->TopOfStack->Next);
	
	StackMemDealloc((void*)(TempStackNode));

	return (void*)Data;
}

#if (USING_STACK_PEEK_METHOD == 1)
	void *StackPeek(STACK *Stack)
	{
		#if (STACK_SAFE_MODE == 1)
			if(StackIsNull(Stack))
				return (void*)NULL;
		
			if(StackIsEmpty(Stack))
				return (void*)NULL;
		#endif // end of STACK_SAFE_MODE

		/*
			Return the data pointed to by the first STACK_NODE.
		*/
		return (void*)(Stack->TopOfStack->Data);
	}
#endif // end of USING_STACK_PEEK_METHOD

#if (USING_STACK_CLEAR_METHOD == 1)
	BOOL StackClear(STACK *Stack)
	{
		STACK_NODE *TempStackNode;
	
		#if (STACK_SAFE_MODE == 1)
			if(StackIsNull(Stack))
				return (BOOL)FALSE;
	
			if(StackIsEmpty(Stack))
				return (BOOL)TRUE;
		#endif // end of STACK_SAFE_MODE

		/*
			Use TempStackNode as an iterator to go through the STACK.
			Start off at the beginning of the STACK.
		*/
		TempStackNode = (STACK_NODE*)(Stack->TopOfStack);
	
		/*
			Whie TempStackNode is not NULL then proceed to free it's current
			STACK_NODE, and the data if required by user with calls to 
			StackMemDealloc().
		*/
		while(TempStackNode != (STACK_NODE*)NULL)
		{
			Stack->TopOfStack = (STACK_NODE*)(Stack->TopOfStack->Next);
	
			#if(USING_STACK_DEPENDENT_FREE_METHOD == 1)
				if(Stack->StackFreeMethod)
					Stack->StackFreeMethod((void*)(TempStackNode->Data));
			#endif // of USING_STACK_DEPENDENT_FREE_METHOD

			StackMemDealloc((void*)TempStackNode);  // StackMemDealloc defined in StackConfig.h

			TempStackNode = (STACK_NODE*)(Stack->TopOfStack); 
		}
	
		/*
			Set the STACK back to as if it was just newly created.  Stack->TopOfStack
			was automatically placed to (STACK*)NULL when it did it's last iteration
			in the above while loop.  So as a result we don't need to set it to 
			(STACK_NODE*)NULL.  It was already done for us.
		*/
		Stack->Size = (UINT32)0;
	
		return (BOOL)TRUE;
	}
#endif // end of USING_STACK_CLEAR_METHOD

#if (USING_STACK_GET_SIZE_METHOD == 1)
	UINT32 StackGetSize(STACK *Stack)
	{
		#if (STACK_SAFE_MODE == 1)
			if(StackIsNull(Stack))
				return (UINT32)0;
		#endif // end of STACK_SAFE_MODE

		/*
			Return the Stack's size.
		*/
		return (UINT32)(Stack->Size);
	}
#endif // end of USING_STACK_GET_SIZE_METHOD

#if (USING_STACK_GET_SIZE_IN_BYTES_METHOD == 1)
	UINT32 StackGetSizeInBytes(STACK *Stack, UINT32 DataSizeInBytes)
	{
		UINT32 Size;
	
		#if (STACK_SAFE_MODE == 1)
			if(StackIsNull(Stack))
				return (UINT32)0;	
		#endif // end of STACK_SAFE_MODE	

		/*
			If the STACK is empty then we just need to return
			the size of a STACK in bytes.
		*/
		if(StackIsEmpty(Stack))
			return (UINT32)sizeof(STACK);
	
		/*
			Start off with the size of a STACK in bytes.
		*/
		Size = (UINT32)sizeof(STACK);
	
		/*
			If the user passed in a value for DataSizeInBytes then use this value
			to calculate the size of the STACK.  Otherwise we just use the number
			of STACK_NODE's multiplied by the size of the STACK.
		*/
		if(DataSizeInBytes)
		{
			Size += (UINT32)((Stack->Size) * (DataSizeInBytes + (UINT32)sizeof(STACK_NODE)));
		}
		else
		{
			Size += (UINT32)((Stack->Size) * (UINT32)sizeof(STACK_NODE));
		}
	
		return (UINT32)Size;
	}
#endif // end of USING_STACK_GET_SIZE_IN_BYTES_METHOD

#if (USING_STACK_GET_LIBRARY_VERSION == 1)

	const BYTE *StackLibraryVersion[] = {"Stack Lib v1.04\0"};

	const BYTE *StackGetLibraryVersion(void)
	{
		return (const BYTE*)StackLibraryVersion;
	}

#endif // end of USING_STACK_GET_LIBRARY_VERSION
