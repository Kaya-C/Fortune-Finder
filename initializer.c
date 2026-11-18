/*
 * This file contains functions to generate a random game board. 
 * The board has two difficulty modes (Easy and Hard) and
 * contain a certain number of treasures, bombs, hints, and hidden cells 
 * depending on the mode. Functions include board initialization, 
 * random placement of items, and utility functions to locate item locations.
 *
 * Catherine, 2025/12/02, v2.0.2
 */

#include <stdlib.h>
#include <stdbool.h>

#define MAX_BOARD 6 //The maximum dimension (row/col) for the game board


//Stub functions that are used throughout this file
void randomizer(int *row, int *col, int size);
void place_items(int board[MAX_BOARD][MAX_BOARD], int size, int count, int itemNum);
bool has_item(int board[MAX_BOARD][MAX_BOARD], int r, int c);


/*
 * DESCRIPTION: Initializes the game board for the game.
 * Sets all cells to blank initially, then calls the places item function to place 
 * a certain amount of treasures, bombs, and hints
 * based on the selected difficulty mode (Easy or Hard). Remaining blank cells
 * are converted into hidden cells.
 *
 * PARAMETERS:
 *   board    - 2D array representing the game board (MAX_BOARD x MAX_BOARD)
 *   hardMode - Boolean flag to select difficulty; true = Hard, false = Easy
 *
 * SIDE EFFECTS:
 *   Modifies the 'board' array by placing an int value of the char that represents the 
 *   treasures (* = 42), bombs (B = 66), hints (? = 63), and hidden cells (. = 46).
 *
 */ 
void board_maker(int board[MAX_BOARD][MAX_BOARD], bool hardMode){
    // Initialize entire board with 0 (blank)
    int size = 0;
    for (int r = 0; r < MAX_BOARD; r++){
        for (int c = 0; c < MAX_BOARD; c++){
            board[r][c] = 0;
        }
    }

    if (hardMode){
        // Hard Mode (6×6)
        size = 6;
        place_items(board, size, 5, 42);  // 5 treasures (* = 42(ASCII))
        place_items(board, size, 8, 66);  // 8 bombs (B = 66 (ASCII))
        place_items(board, size, 3, 63);  // 3 hints (? = 63(ASCII))
    } 
    else{
        // Easy Mode (5×5)
        size = 5; //64 @
        place_items(board, size, 6, 42);  // 6 treasures (* = 42(ASCII))
        place_items(board, size, 4, 66);  // 4 bombs (B = 66 (ASCII))
        place_items(board, size, 5, 63);  // 5 hints (? = 63(ASCII))
    }

    //Converts remaining blank cells (0) into hidden cells (1)
    for (int r = 0; r < size; r++){
        for (int c = 0; c < size; c++){
            if (board[r][c] == 0){
                board[r][c] = 46; //(. = 46 (ASCII))
            }
        }
    }
}//end of board_maker


/*
 * DESCRIPTION: Generates random row and column indices within the bounds
 * of the board. The generated values can be used to place items at that index of the board.
 *
 * PARAMETERS:
 *   row  - Pointer to an integer where the random row index will be stored
 *   col  - Pointer to an integer where the random column index will be stored
 *   size - The size of the board (number of rows/columns)
 *
 * SIDE EFFECTS:
 *   The values pointed to by 'row' and 'col' are modified with random indices.
 */
void randomizer(int *row, int *col, int size){
    //Generates 2 random number between 0 and size-1 --> Array Index
    *row = rand() % size;
    *col = rand() % size;
}//end of randomizer


/*
 * DESCRIPTION: Checks whether a specific cell on the board already contains
 * a special item: treasure (* = 42), bomb (B = 66), or hint (? = 63).
 *
 * PARAMETERS:
 *   board - 2D array representing the game board (MAX_BOARD x MAX_BOARD)
 *   r     - Row index of the cell to check
 *   c     - Column index of the cell to check
 *
 * RETURNS:
 *   true  - if the cell contains a treasure, bomb, or hint
 *   false - if the cell does not contain any special item
 *
 */
bool has_item(int board[MAX_BOARD][MAX_BOARD], int r, int c){
    //special cells ASCII Values: treasures * = 42, bombs B = 66, hints ? = 63
    return (board[r][c] == 42 || board[r][c] == 66 || board[r][c] == 63); //if any of them are true, it returns true
}//end of has_item


/*
 * DESCRIPTION: Randomly places a specified number of items (treasures, bombs,
 * or hints) on empty cells of the board.
 *
 * PARAMETERS:
 *   board   - 2D array representing the game board (MAX_BOARD x MAX_BOARD)
 *   size    - Number of rows/columns to consider
 *   count   - Number of items to place
 *   itemNum - ASCII value of the item (*=42, B=66, ?=63)
 *
 * SIDE EFFECTS:
 *   Modifies the 'board' array by placing items in empty cells.
 */
void place_items(int board[MAX_BOARD][MAX_BOARD], int size, int count, int itemNum){
    int row = 0, col = 0;

    while (count > 0){ //if theres no item (function returns false), the item gets placed
        randomizer(&row, &col, size);

        if (!has_item(board, row, col)){
            board[row][col] = itemNum;
            count--;
        }//end of if
    }//end of while
}//end of place_items


/*
 * DESCRIPTION: Finds all row indices where a specific item appears on the board
 * and stores them in the passed array. Also returns the number of occurrences of item.
 *
 * PARAMETERS:
 *   board   - 2D array representing the game board (MAX_BOARD x MAX_BOARD)
 *   size    - Number of rows to consider
 *   itemNum - ASCII value of the item (*=42, B=66, ?=63)
 *   rows    - Array to store the row indices of found items
 *
 * RETURNS:
 *   The number of occurrences of the item
 *
 * SIDE EFFECTS:
 *   Modifies the 'rows' array by filling it with row indices of the item.
 */
int get_item_rows(int board[MAX_BOARD][MAX_BOARD], int size, int itemNum, int rows[]){
    int count = 0;
    for (int r = 0; r < size; r++){
        for (int c = 0; c < size; c++){
            if (board[r][c] == itemNum){
                rows[count] = r;
                count++;
            }
        }
    }
    return count;
}//end of get_item_rows

/*
 * DESCRIPTION: Finds all cols indices where a specific item appears on the board
 * and stores them in the passed array. Also returns the number of occurrences of item.
 *
 * PARAMETERS:
 *   board   - 2D array representing the game board (MAX_BOARD x MAX_BOARD)
 *   size    - Number of cols to consider
 *   itemNum - ASCII value of the item (*=42, B=66, ?=63)
 *   cols    - Array to store the cols indices of found items
 *
 * RETURNS:
 *   The number of occurrences of the item
 *
 * SIDE EFFECTS:
 *   Modifies the 'cols' array by filling it with cols indices of the item.
 */
int get_item_cols(int board[MAX_BOARD][MAX_BOARD], int size, int itemNum, int cols[]){
    int count = 0;
    for (int r = 0; r < size; r++){
        for (int c = 0; c < size; c++){
            if (board[r][c] == itemNum){
                cols[count] = c;
                count++;
            }
        }
    }
    return count;
}//end of get_item_cols