/*
 * This file contains utility functions for generating,
 * and displaying the game board. It handles the creation of both the
 * visible (numbered) layer and the hidden (symbol/item) layer.
 *
 * Zain, 2025/12/02, v2.0.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_BOARD 6 //The maximum dimension (row/col) for the game board

/*
 * DESCRIPTION: Prints the visible layer of the grid to the console, applying ANSI color codes
 * to revealed symbols for better visibility (e.g., red for 'B', yellow for '*').
 *
 * PARAMETERS:
 *   size: The size (dimension) of the square grid
 *   print: The 2D array representing the visible grid
 */
void printGrid(int size, int (*print)[size]) {
    //Loop through each row of the grid
    for (int i = 0; i < size; i++) {
        printf("\n");
        //Print the top border for the current row
        for (int j = 0; j < size; j++){
            printf("------");   // column labels      
        }
        printf("\n");
        
        //Loop through each colum to print the cell content
        for (int j = 0; j < size; j++) {
            printf("|");
            //Check the cell content and apply ANSI color codes if it's a revealed symbol.
            if(print[i][j] == 66) //Print 'B' in red
                printf("\033[31m%3c \033[0m", print[i][j]);
            else if(print[i][j] == 42)  //Print '*' in yellow
                printf("\033[33m%3c \033[0m", print[i][j]);  
            else if(print[i][j] == 63)  //Print '?' in purple
                printf("\033[35m%3c \033[0m", print[i][j]); 
            else if(print[i][j] == 46)  //Print '.' in default color
                printf("%3c ", print[i][j]); //normal
            else{
                printf("%3d ", print[i][j]); 
            } 
            printf("|");
        }
            
    }
    printf("\n");
    for (int j = 0; j < size; j++){
            printf("------");       
    }
}

/*
 * DESCRIPTION: The makeGrid function initializes the visible grid by filling it sequentially with box numbers
 * starting from 1 up to s*s.
 *
 * PARAMETERS:
 *   size: The size (dimension) of the square grid
 *   grid: The 2D array that will be populated with numbered tiles
 */
void makeGrid(int size, int (*grid)[size]){
    int index=1; 
    //Iterate through all rows and columns and sign the current box number (index) to the cell
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = index;
            index++;
        }
    }
}

/*
 * DESCRIPTION: The updateVisibleGrid function reveals the symbol underneath the chosen numbered tile 
 * by updating the visible grid.
 *
 * PARAMETERS:
 *   size: The size (dimension) of the grid
 *   reveal: The chosen box number (1-based) to reveal
 *   board: The hidden symbols layer (MAX_BOARD x MAX_BOARD) used as the source of the symbol
 *   intGrid: The visible number layer (VLA sized s x s) which will be modified to show the symbol
 */
void updateVisibleGrid(int size, int reveal, int board[MAX_BOARD][MAX_BOARD], int (*intGrid)[size]){
    //Iterate through all cells to find the matching box number
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //Check if the current cell contains the box number 'rev'
            if (intGrid[i][j] == reveal){
                intGrid[i][j] = board[i][j]; 
            }
            
        }
    }
}