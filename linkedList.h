#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListNode
{
	void* data;
	struct LinkedListNode* next;
} LinkedListNode;

typedef struct LinkedList
{
	LinkedListNode* head;
	LinkedListNode* tail;
	int size;	
} LinkedList;

typedef void (*FunPtr)(void* data);


LinkedList* createLinkedList();
void insertLast( LinkedList* pList, void* pData );
void* removeLast( LinkedList* pList );
void freeData( void * pData );
void freeLinkedList( LinkedList* pList, FunPtr fpFreeDataFunc );
void printData(void* pData);
void printLinkedList(LinkedList* pList, FunPtr fpPrintDataFunc);

#endif