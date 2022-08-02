#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "module.h"


/**
 * @brief  disables buffer
 * @note   disables user input buffer from showing in terminal. This function is given in the assignment materials.
 * @retval None
 */
void disableBuffer() {
    struct termios mode;

    tcgetattr( 0, &mode );
    mode.c_lflag &= ~( ECHO | ICANON );
    tcsetattr( 0, TCSANOW, &mode );
}


/**
 * @brief  enables buffer
 * @note   enables user input buffer from showing in terminal. This function is given in the assignment materials.
 * @retval None
 */
void enableBuffer() {
    struct termios mode;

    tcgetattr( 0, &mode );
    mode.c_lflag |= ( ECHO | ICANON );
    tcsetattr( 0, TCSANOW, &mode );
}


/**
 * @brief  constructs the calculator keyboard based on a given random integer.
 * @note   constructs the calculator keyboard with supplied pointer to keyboard array and may flip it if the received random integer is 1. 
 * * 50% chance randInt is 1 and 50% change randint is 0. Assumed starting point in table is always table[1][0].
 * @param  pppcKeyBoardArray: pointer to 2D Array of keyboard. (Type: Pointer to a Char 2D array).
 * @param  randInt: Random Integer between 1 and 0. 50% chance randInt is 1 and 50% change randint is 0.
 * @retval None
 */
void constructKeyboard( char *** pppcKeyBoardArray, int randInt ) {
    int row; 
    int rowSize = 8;
    int colSize = 3;
    char** table; /* construct table here first then assign to the pointer of ppcKeyBoardArray */

    /* generate 2d Array to hold keyboard elements */
    table = ( char** ) malloc( sizeof( char* ) * rowSize );
    
    for ( row = 0 ; row < rowSize ; row++ ) {
        table[row] = ( char* ) malloc( sizeof( char ) * colSize );
    }

    /* assign digits and symbols to array */
    table[0][0] = '1'; table[0][1] = '2'; table[0][2] = '3'; 

    table[1][0] = '^'; table[1][1] = ' '; table[1][2] = ' '; 

    table[2][0] = '4'; table[2][1] = '5'; table[2][2] = '6'; 

    table[3][0] = ' '; table[3][1] = ' '; table[3][2] = ' '; 

    table[4][0] = '7'; table[4][1] = '8'; table[4][2] = '9'; 

    table[5][0] = ' '; table[5][1] = ' '; table[5][2] = ' '; 

    table[6][0] = '+'; table[6][1] = '0'; table[6][2] = '='; 

    table[7][0] = ' '; table[7][1] = ' '; table[7][2] = ' '; 

    /* 50% chance randInt is 0, 50% chance randInt is 1, if randInt is 1 then flip the table layout 
       randomness should be determined in main */
    if ( randInt == 1 ) {
        table[6][0] = '1'; table[6][1] = '2'; table[6][2] = '3'; 
        table[0][0] = '+'; table[0][1] = '0'; table[0][2] = '='; 

        table[4][0] = '4'; table[4][1] = '5'; table[4][2] = '6'; 
        table[2][0] = '7'; table[2][1] = '8'; table[2][2] = '9'; 

    }

    *pppcKeyBoardArray = table; /* make the pointer of the 2d keyboard array, point to table */
}


/**
 * @brief  frees memory allocated for the keyboard generated (using constructKeyboard function).
 * @note   frees memory allocated for the keyboard generated supplied in a pointer to the array (using constructKeyboard function)
 * @param  ppcKeyBoardArray: 2D array of calculator keyboard. (Type: Char 2D array).
 * @retval None
 */
void freeKeyboard ( char** ppcKeyBoardArray ) {
    int row;
    int rowSize = 8;
    
    if ( ppcKeyBoardArray != NULL ) { /* check if keyboard array has been assigned/malloc'ed yet */

        /* free every row */
        for ( row = 0 ; row < rowSize ; row++ )
            {
                free( ppcKeyBoardArray[row] );
                ppcKeyBoardArray[row] = NULL;
            }
        
        /* free the keyboard array */
        free( ppcKeyBoardArray );
        ppcKeyBoardArray = NULL;
    }
}


/**
 * @brief  displays the calculator keyboard in the character 2d array.
 * @note   prints out the calculator with the given array, current display number and current total
 * @param  ppcKeyBoardArray: 2D array of calculator keyboard. (Type: Char 2D array).
 * @param  currNum: Current display number (Type: Integer).
 * @param  currTotal: Current calculated total (Type: Integer).
 * @retval None
 */
void displayCalculator( char** ppcKeyBoardArray, int currNum, int currTotal ) {

    int row, col;
    int rowSize = 8, colSize = 3;

    printf( "---------\n|%7d|\n---------\n", currNum ); /* top box display */
    printf( "\n" );

    /* iterate through 2D array and output out */
    for ( row = 0 ;  row < rowSize ; row++ ) {

        for ( col = 0 ;  col < colSize ; col++ ) {

            printf( "%c ", ppcKeyBoardArray[row][col] );
        
        }

        printf( "\n" );
    }
    
    printf( "\ncurrent total : %d\n", currTotal ); /* print total */

}


/**
 * @brief  User Interface control manager that takes a character input to perform the actions 
 * * demanded by the user (traverse keyboard, add, equate, etc..).
 * @note   Keyboard size is assumed to be the equal in all functions and related files. Directly above the current user's 
 * * cursor (represented by '^') in the keyboard array is always assumed to be a valid number or arithmetic operation.
 * @param  ppcKeyBoardArray: 2D array of calculator keyboard. (Type: Char 2D array).
 * @param  pcInputCh: user input (i.e. w,a,s or d). (Type: Pointer to the Char input value).
 * @param  piCurrCursorPos: array holding current position of cursor (Type: Pointer to the Char input value).
 * @param  piCurrNum: current display number in the calculator (Type: Pointer to the Char input value).
 * @param  piCurrTotal: current total calculated number in the calculator (Type: Pointer to the Char input value).
 * @param  piDigitCount: current digit count of the display number (Type: Pointer to the Char input value). 
 * @param  pList: linked list that holds the input sequences for the calculator (Type: Pointer to a type defined struct called "LinkedList").
 * @retval returns TRUE or FALSE depending if the calculator program should end or not (based on user input, inputting "=" in the calculator.
 *  will end the program.* )
 */
int userInterfaceManager( char** ppcKeyBoardArray, int* piCurrCursorPos, char* pcInputCh, int* piCurrNum, int* piDigitCount, int* piCurrTotal, LinkedList* pList ) {
    int retExit = FALSE; /* return Exit Status. End program (user is done with calculator program by inputting "=") if retExit = TRUE */
    
    switch ( *pcInputCh ) { 
        
        /* KEYBOARD TRAVERSING */
        case 'w': /* move up */
            if ( piCurrCursorPos[0] != 1 ) { /* if cursor is not already on the first traversable row */
                /* update current position of cursor */
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = ' ';
                piCurrCursorPos[0] = piCurrCursorPos[0] - 2;
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = '^';   
            }
            break;

        case 'a': /* move left */
            if ( piCurrCursorPos[1] != 0 ) { /* if cursor is not already on the first column */
                /* update current position of cursor */
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = ' ';
                piCurrCursorPos[1] = piCurrCursorPos[1] - 1;
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = '^';
            }
            break;

        case 's': /* move down */
            if ( piCurrCursorPos[0] != 7 ) { /* if cursor is not already on the last traversable row */
                /* update current position of cursor */
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = ' ';
                piCurrCursorPos[0] = piCurrCursorPos[0] + 2;
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = '^';   
            }
            break;

        case 'd': /* move right */
            if ( piCurrCursorPos[1] != 2 ) { /* if cursor is not already on the last column */
                /* update current position of cursor */
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = ' ';
                piCurrCursorPos[1] = piCurrCursorPos[1] + 1;
                ppcKeyBoardArray[piCurrCursorPos[0]][piCurrCursorPos[1]] = '^';
            }
            break;

        /* KEYBOARD INPUT CONFIRM */
        case 'e': /* confirm the input as the current character the user's cursor is pointing to */

            /* if cursor is currently on '=', */
            if ( ppcKeyBoardArray[piCurrCursorPos[0] - 1][piCurrCursorPos[1]] == '=' ) { 
                retExit = TRUE; /* exit the code */
            }

            /* if cursor is currently on '+', */
            else if ( ppcKeyBoardArray[piCurrCursorPos[0] - 1][piCurrCursorPos[1]] == '+' ) {
                if ( * piCurrNum != 0 ) { /* if the current displayed number is not 0 */
                    /* if displayed number is 0, do not add to linked list/ malloc-ing, no point adding */
                    
                    /* allocate memory for int * to assign to the linked list's void * data */
                    int * linkedListData = malloc( sizeof ( int * ) );                     
                    *linkedListData = *piCurrNum; /* assign to the current display number */

                    insertLast( pList, linkedListData ); /* insert display number to last posiiton in the linked list */
                    *piCurrTotal += *piCurrNum; /* add to current total */ 

                    /* reset current display number */ 
                    *piCurrNum = 0; 
                    *piDigitCount = 0;
                }
            }

            /* else if cursor is not on '+' or '=' then modify current display number */
            else {
                if ( *piDigitCount != 7 ) { /* if digit count is not 7, maximum displayable digits is 7 */

                    /* algorithm to append current input number to the current displayed number */
                    *piCurrNum *= 10; /* move the current display value to the next higher place value, 
                       i.e. displayed number: 342 -> 3420 */

                    /* add the current number cursor is on to the current displayed number; 
                       i.e. confirmed number cursor is on: 5, displayed number: 3420 -> 3425 */
                    *piCurrNum += ( int ) ppcKeyBoardArray[piCurrCursorPos[0] - 1][piCurrCursorPos[1]] - 48;
                    /* typecast integer then subtract 48 to get the integer version of the ASCII character */
                    
                    /* if current display number is not 0 then increase digit count. If the current display 
                       number is still 0 however, the above won't have any effect (i.e. 0*10 = 0, 48-48 = 0) */
                    if ( *piCurrNum != 0 ) {
                        *piDigitCount += 1; /* increase digit count */
                    }
                }
            }
            break;
    }
    return retExit; /* return exit status */
}


/**
 * @brief  Write calculated data and linked list data in sequence to a specified output file and free the data of any nodes removed in linked list.
 * @note   Frees the data in the node using a function pointer, data is of type void * so a special function is needed for this. 
 * @param  pList: linked list that holds the input sequences for the calculator (Type: Pointer to a type defined struct called "LinkedList").
 * @param  pInFile: output file used for writing the addition sequences and final calculated sum of the program to the file. (Type: Pointer to the type 'FILE').
 * @param  currTotal: value that holds the current total calculated value (Type: Integer).
 * @param  fpFreeDataFunc: function pointer used for freeing the data stored in the void pointer of the linked list's nodes (Type: Address of function pointer 'FunPtr').
 * @retval None
 */
void writeDataToFile( LinkedList* pList, FILE* pInFile, int currTotal, FunPtr fpFreeDataFunc ) {
        
    if ( pList->size > 1 ) { /* if size is greater than 1, addition sequences are involved */
        while ( pList->head != NULL ) { /* loop while list is not empty */

            void * retVal = removeLast( pList ); /* remove the last element in the linked list */
            int value = *( ( int* ) retVal ); /* type cast to an integer */

            fprintf( pInFile, "%d", value ); /* output the integer to the file */

            ( *fpFreeDataFunc )( retVal ); /* free the malloc'ed data in the void pointer */

            if ( pList->size > 0 ) { 
                /* if the linked list size is greater than 0 add the '+' sign. Will not 
                add if last value in linked list was just added. Prevents the following bad output; '1 + 2 + 3 +  = 6' */ 

                fprintf( pInFile, " + " ); /* add the '+' sign */
            }

        }

        /* add the equal sign and current total if original size of linked list is greater than 1 */
        fprintf( pInFile, " = %d\n", currTotal );
    }

    else { /* else don't add equal sign, just write the current total number to the file */
        fprintf( pInFile, "%d\n", currTotal ); 
        /* this is so that if we just enter 700 in the calculator and exit (press '='), we don't get '700 = 700', we get just '700'*/

    }
}