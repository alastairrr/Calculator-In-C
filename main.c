#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "module.h"


int main( int argc, char *argv[] ) {


    /* ************************************** *
     * ---- INITIALISING LOCAL VARIABLES ---- *
     * ************************************** */

    int randInt; /* value to hold the random integer generated */
    int currNum = 0; /* current number being displayed on calculator screen */
    int digitCount = 0; /* value to hold the amount of digits currNum has */
    int currTotal = 0; /* current total value calculated */
    int exitStatus = FALSE; /* value to hold that decides if the program has been asked to exit by the user or not */

    int* piCurrCursorPos; /* curr position of the cursor */
    char inputCh; /* character input */
    char* pcOutFile; /* output file name */
    char** ppcKeyBoardArray = NULL; /* double pointer to the char array of the calculator keyboard */

    FILE* pInFile = NULL; /* output file */
    LinkedList* pList = NULL; /* linked list struct */


    /* ************* *
    * ---- MAIN ---- *
    * ************** */

    if ( argc != 2 ) { /* run if argument amount is satisfied */
        printf( "Please provide argument correctly: ./calculator <filename>\n" );
    }

    else {

        /* generate random number */
        srand( time( NULL ) );
        randInt = rand() % 2;

        /* set the outfile name to the command line argument */
        pcOutFile = argv[1];


        /* ************************************************* *
         * ---- PRE-ALLOCATE MEMORY FOR LIST AND ARRAYS ---- *
         * ************************************************* */

        /* create linked list */
        pList = createLinkedList();

        /* create keyboard */
        constructKeyboard( &ppcKeyBoardArray, randInt );

        /* malloc cursor position array */
        piCurrCursorPos = ( int* ) malloc( sizeof( int ) * 2 );
        piCurrCursorPos[0] = 1; piCurrCursorPos[1] = 0; /* initialise starting position */


        /* ************************* *
         * ---- CALCULATOR CORE ---- *
         * ************************* */
        
        /* # -- CALCULATOR BEGIN -- # */
        disableBuffer(); /* disable user input from being displayed */

        do {

            system("clear"); /* refresh terminal */
            displayCalculator( ppcKeyBoardArray, currNum, currTotal ); /* display calculator user interface */
            scanf( " %c", &inputCh ); /* get user input (w, a, s, d and e are only valid) */

            /* manages user interface and user's interactions, returns exitStatus; TRUE to exit the program, FALSE to keep looping */ 
            exitStatus = userInterfaceManager( ppcKeyBoardArray, piCurrCursorPos, &inputCh, &currNum, &digitCount, &currTotal, pList );
            
        } while ( exitStatus != TRUE ); /* while not exit menu */

        /* # -- CALCULATOR END -- # */
        enableBuffer(); /* enable user input from being displayed */

        pInFile = fopen( pcOutFile, "w" ); /* open a file to write to */
        writeDataToFile( pList, pInFile, currTotal, &freeData ); /* write the linked list sequences and total calculated number to file */


        /* ********************************************** *
         * ---- FREE MEMORY ALLOCATED AND FILE CLOSE ---- *
         * ********************************************** */
        
         /* free keyboard array */
        freeKeyboard( ppcKeyBoardArray );
        ppcKeyBoardArray = NULL;

        /* free cursor position array */
        free( piCurrCursorPos );
        piCurrCursorPos = NULL; 
        
        /* free linked list */
        freeLinkedList( pList, &freeData ); 
        pList = NULL;
        
        /* close output file */
        fclose( pInFile );
        pInFile = NULL;

    }

    /* Program End */
    return 0;
}