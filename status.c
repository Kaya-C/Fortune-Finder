/*The file contains the function 'checkchoice' and 'status' to evaluate
 *user input and output the current gaming status to user.
 *
 * Joanna 2025/12/02, v2.0.2
 */
#include <stdio.h>
#include <stdlib.h>

/*DESCRIPTION: The function  evaluates the userinput based on the generated treasure, bombs, and hints
 *locations. Support two game modes with different size and numbers of treasures, bombs
 *and hints.

 *Check bomb: Return 1 if the user choses a bomb location
 *Check hint: Display the percentage chances of treasures and bombs beside chosen location.
 *Check treasure: Increase the score by 1 when the user choses a treasure location.
 *Eempty location: Displays the number of treasure and bombs beside chosen location.
 *
 * PARAMETERS:
 *   userInput: The integer represents the position that user chooses
 *   mode: The integer represent mode selection 0=easymode; 1=hardmode
 *   treasureRows: The array contains row numbers of all the treasures
 *   treasureCols: The array contains column numbers of all the treasures
 *   bombRows: The array contains row numbers of all the bombs
 *   bombCols: The array contains column numbers of all the bombs
 *   hintRows: The array contains row numbers of all the hints
 *   hintCols: The array contains column numbers of all the hints
 *   socre: The score represents the number of found treasures till current game round
 * RETURNS:
 *   returns 1 if the user chooses a bomb
 *   returns 0 if user chooses a treasure/hint/empty place
 */


int checkchoice (int userInput, int mode,
                 int treasureRows[], int treasureCols[],
                 int bombRows[], int bombCols[],
                 int hintRows[], int hintCols[],
                 int *score)
{
    int size;
    int treasureNum;
    int bombNum;
    int hintNum;

    //Easy mode
    if (mode == 0){
        size = 5;
        treasureNum = 6;
        bombNum = 4;
        hintNum = 5;
    //Hard mode
    }else {
        size = 6;
        treasureNum = 5;
        bombNum = 8;
        hintNum = 3;
    }
    
    //Convert box number into row/col (0-based). 
    int inputRow = (userInput-1) / size;
    int inputCol = (userInput-1) % size;

    //Check bombs       
    for (int i = 0; i < bombNum; i++){
        if (bombRows[i]==inputRow && bombCols[i]==inputCol){
            return 1;
        }
    }

    //check treasure
    for (int i = 0;i < treasureNum; i++){
        if (treasureRows[i]==inputRow && treasureCols[i]==inputCol){
            *score += 1;
            printf("You find a treasure!\n");
            return 0;
        }
    }

    //Check Hints
    for (int i = 0; i < hintNum; i++){
        if (hintRows[i]==inputRow && hintCols[i]==inputCol){
            int treasure_beside = 0;
            int bomb_beside = 0;

            //Count nearby treasures
            for (int t = 0; t < treasureNum; t++){
                if (abs(treasureRows[t]-inputRow)<=1 && abs(treasureCols[t]-inputCol)<=1 && !((treasureRows[t]==inputRow)&&(treasureCols[t]==inputCol))){
                    treasure_beside += 1;
                }
            }

            //Count nearby bombs
            for (int b = 0; b < bombNum; b++){
                if (abs(bombRows[b]-inputRow)<=1 && abs(bombCols[b]-inputCol)<=1 && !((bombRows[b]==inputRow)&&(bombCols[b]==inputCol))){
                    bomb_beside +=1;
                }
            }
            
            printf("This is a hint box!\n");
            if (treasure_beside + bomb_beside == 0){
                printf("Nothing Nearby!\n");
            }else {
                double treasure_percent = treasure_beside / 8.0 * 100.0;
                double bomb_percent = bomb_beside / 8.0 * 100.0;
                printf("Treasure chances near you: %.1f%%\n", treasure_percent);
                printf("Bomb chances near you: %.1f%%\n", bomb_percent);
            }
            return 0;
        }
    }
    
    //Handle empty cells
    int treasure_beside = 0;
    int bomb_beside = 0;

    for (int t = 0; t < treasureNum; t++){
        if (abs(treasureRows[t]-inputRow)<=1 && abs(treasureCols[t]-inputCol)<=1 && !((treasureRows[t]==inputRow)&&(treasureCols[t]==inputCol))){
            treasure_beside += 1;
        }
    }

    for (int b = 0; b < bombNum; b++){
        if (abs(bombRows[b]-inputRow)<=1 && abs(bombCols[b]-inputCol)<=1 && !((bombRows[b]==inputRow)&&(bombCols[b]==inputCol))){
            bomb_beside +=1;
        }
    }

    printf("There are %d treasures and %d bombs besides you\n", treasure_beside, bomb_beside);
    return 0;
}

/*DESCRIPTION: The function calls checkchoice to check user input and then return 
 *the current game status, including display the current score and the 
 *total number of bombs and hints.

 *Bomb detected (checkchoice return 1): Display a message shows game end and the current score. Return 1
 *All treasure found: Display a message shows all treasures have been found. Return 1
 *Other situation: Display the message shows current game status. Return 0
 *
 * PARAMETERS:
 *   userInput: The integer represents the position that user chooses
 *   mode: The integer represent mode selection 0=easymode; 1=hardmode
 *   treasureRows: The array contains row numbers of all the treasures
 *   treasureCols: The array contains column numbers of all the treasures
 *   bombRows: The array contains row numbers of all the bombs
 *   bombCols: The array contains column numbers of all the bombs
 *   hintRows: The array contains row numbers of all the hints
 *   hintCols: The array contains column numbers of all the hints
 *   socre: The score represents the number of found treasures till current game round
 * RETURNS:
 *   returns 1 if the user chooses a bomb or user find all treasures so game ends
 *   returns 0 if the game continues
 */


int status (int userInput, int mode,
                 int treasureRows[], int treasureCols[],
                 int bombRows[], int bombCols[],
                 int hintRows[], int hintCols[],
                 int *score)
{
    int treasureNum;
    int bombNum;
    int hintNum;
    int size;
    
    if (mode == 0){
        size = 5;
        treasureNum = 6;
        bombNum = 4;
        hintNum = 5;
    }else{
        size = 6;
        treasureNum = 5;
        bombNum = 8;
        hintNum = 3;
    }

    int result = checkchoice(userInput, mode,
                             treasureRows, treasureCols,
                             bombRows, bombCols,
                             hintRows, hintCols,
                             score);

    if (result == 1) {
        printf("You touched a bomb! Game over!\n");
        printf("Final score: %d/%d treasures found.\n", *score, treasureNum);
        return 1; 
    }

    if (*score == treasureNum){
        printf("\nYou have found all the treasures!\n");
        return 1;
    }

    printf("\nYour current score: %d/%d\n", *score, treasureNum);
    printf("There are %d bombs and %d hints in total.\n", bombNum, hintNum);
    return 0;
}