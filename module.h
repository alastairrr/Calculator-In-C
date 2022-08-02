#ifndef MODULE_H
#define MODULE_H


#define FALSE 0
#define TRUE !FALSE
#include "linkedList.h"

void disableBuffer();
void enableBuffer();
void constructKeyboard( char *** ppcKeyBoardArray, int randInt );
void displayCalculator( char** ppcKeyBoardArray, int currNum, int currTotal );
void freeKeyboard ( char** ppcKeyBoardArray );
int userInterfaceManager( char** ppcKeyBoardArray, int* piCurrCursorPos, char* piInputCh, int* piCurrNum, int* piDigitCount, int* piCurrTotal, LinkedList* pList );
void writeDataToFile( LinkedList* pList, FILE* pInFile, int currTotal, FunPtr fpFreeDataFunc);


#endif