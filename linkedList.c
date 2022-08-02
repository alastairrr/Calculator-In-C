#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

/**
 * @brief  print the data in the generic linked list.
 * @note   Assert the value of pData can be type casted to int* and dereferenced to access the integer. 
 * * Used for printLinkedList function in the file "linkedList.c".
 * @param  pData: Void pointer to a value with an assumed type of integer.
 * @retval None
 */
void printData( void* pData ) {
	printf( "data: %d\n", *( ( int* ) pData ) );
}


/**
 * @brief  free the data malloc'ed for the generic linked list.
 * @note   data malloc'ed is a integer pointer.
 * @param  pData: Void pointer to a value with an assumed type of integer.
 * @retval None
 */
void freeData( void* pData ) {
	free( pData ); 
}


/**
 * @brief  creates the generic linked list.
 * @note   Malloc's and creates the linked list, returns the linked list struct address.
 * @retval Returns Linked List Struct.
 */
LinkedList* createLinkedList() {
    LinkedList* pLinkedList = ( LinkedList* ) malloc( sizeof( LinkedList ) );
    pLinkedList -> head = NULL;
    pLinkedList -> size = 0;

    return pLinkedList;
}


/**
 * @brief  Inserts last to the generic linked list.
 * @note   Inserts a pointer to the corresponding data last to the generic linked list.
 * @param  pList: linked list that holds pointers (void*) to values as it's data field (Type: Pointer to a type defined struct called "LinkedList").
 * @param  pData: data in the generic linked list's nodes that holds a pointer to a value (Type: Void Pointer).
 * @retval None
 */
void insertLast( LinkedList* pList, void* pData ) {
	LinkedListNode* pNode = ( LinkedListNode* ) malloc ( sizeof( LinkedListNode ) );
	pNode->data = pData;
	pNode->next = NULL;
		
	if ( pList->head == NULL ) { /* if linked list is empty */
		pList->head = pNode; /* set head to node created */
	}
	else { /* else if linked list is not empty */ 
		pList->tail->next = pNode; /* set the next pointer of current tail of the linked list to the node created */
	}
	
	pList->tail = pNode; /* set the tail pointer to the node created */
	( pList->size )++; /* increment linked list's size field */
}


/**
 * @brief  remove last from the generic linked list.
 * @note   remove last element from the generic linked list. If deleted node data had memory allocations, freeData() should be called after removeLast().
 * @param  pList: linked list that holds pointers (void*) to values as it's data field (Type: Pointer to a type defined struct called "LinkedList").
 * @retval returns void pointer to the value of the removed node.
 */
void* removeLast( LinkedList* pList ) {
    void * retVal = NULL;
    LinkedListNode* currNode = pList->head; /* start at linked list head */

    while ( currNode ) { /* traverse to the end of the linked list if not empty */

        if ( pList->size == 1 ) { /* if size of linked list 1 */
            retVal = currNode->data; /* assign retVal to the node's data*/

			pList->tail = NULL; /* nullify the tail pointer */
            free( pList->head ); /* free the head */
            pList->head = NULL; /* nullify the head, linked list should now be empty */

            currNode = NULL; /* exit out of loop */
        }

        else if ( currNode->next->next == NULL ) { /* if at the end of linked list */
            retVal = currNode->next->data; /* assign retVal to the node's data */

			pList->tail = currNode; /* update the tail pointer */
            free( currNode->next ); /* free the next node */

            currNode->next = NULL; /* nullify the currNode's next value */

            currNode = NULL; /* exit out of loop */
        }

        else {
            currNode = currNode->next; /* else traverse until the end of the linked list */
        }
    }
    ( pList->size )--; /* decrement the linked list's size field */

    return retVal; /* return the pointer to the value */
}


/**
 * @brief  free the memory allocated for the linked list
 * @note   frees the malloc'ed nodes and uses the freeData function to free the node's data field if necessary
 * @param  pList: linked list that holds pointers (void*) to values as it's data field (Type: Pointer to a type defined struct called "LinkedList").
 * @param  fpFreeDataFunc: function pointer used to free the data malloc'ed for the generic linked list. (Type: Address of function pointer 'FunPtr' )
 * @retval None
 */
void freeLinkedList( LinkedList* pList, FunPtr fpFreeDataFunc) {
	LinkedListNode* currNode = pList->head; /* start at the head */
	LinkedListNode* pTemp; /* temporary storage to traverse the linked list */
	
	while ( currNode ) { /* while currnode exists */
		pTemp = currNode->next; /* set the temp storage to the next node */
		
		( *fpFreeDataFunc )( currNode->data ); /* calls function pointer and free the node's data field if needed*/

		/* Nullify the current node's fields */
		currNode->data = NULL;
		currNode->next = NULL;
		free( currNode ); /* free the current node */
		
		currNode = pTemp; /* set the current node to the next node to traverse */		
	}	
	
	free( pList ); /* finally free the linked list once all nodes have been freed */
}


/**
 * @brief  function to print the contents of the linked list 
 * @note   the function pointer fpPrintDataFunc performs the 'printf' function
 * @param  pList: linked list that holds pointers (void*) to values as it's data field (Type: Pointer to a type defined struct called "LinkedList").
 * @param  fpPrintDataFunc: function pointer used to print the data for the generic linked list. (Type: Address of function pointer 'FunPtr' )
 * @retval None
 */
void printLinkedList( LinkedList* pList, FunPtr fpPrintDataFunc ) {
	LinkedListNode* currNode = pList->head; /* set current node to the head */
	
	while ( currNode ) { /* while not end of linked list */
		( *fpPrintDataFunc )( currNode->data ); /* print the node */
		currNode = currNode->next; /* go to the next node */
	}
}

