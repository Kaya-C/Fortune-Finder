/*
 * This file contains the main entry point and setup logic
 * for the 'Fortune Finder' grid-based logic game. It handles
 * command-line argument parsing, game initialization, and the
 * main game loop for player interaction.
 *
 * Parnia, 2025/12/02, v2.0.2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MODE_EASY 0 //Represents easy difficulty settings
#define MODE_HARD 1 //Represents hard difficulty settings
#include <time.h>
#include "functions.h"
#define MAX_BOARD 6 //The maximum dimension (row/col) for the game board

/**
 * Prints the game's welcome banner and introductory art to the console.
 */
void outputBanner(void){
    printf("========================================\n");
    printf("        🌟 *Fortune Finder* 🌟 \n");
    printf("========================================\n");
    printf("           [⬜] [⬜] [⬜]\n");
    printf("           [⬜] [✨] [⬜]\n");
    printf("           [❓] [⬜] [💥]\n");
    printf("           [⬜] [⬜] [⬜]\n");
    printf("\n");
    printf(" Find the treasures, avoid the bombs,\n");
    printf(" and use the hints to guide your path!\n");
    printf("           🍀 Good Luck 🍀!\n");
    printf("========================================\n");
}

/* Prints the exact usage line to stderr. */
void usage(){
    fprintf(stderr, "Usage: main [--mode | test easy | hard] [--help]\n");
}

/* Displays a brief help message showing options and examples. */
void help() {
    printf("fortune_finder - Grid Logic Game\n\n");
    printf("Description:\n");
    printf("  fortune_finder is a terminal-based logic and deduction game.\n");
    printf("  You explore a hidden grid containing treasures, bombs, and\n");
    printf("  hint boxes. Your goal is to uncover treasures while avoiding\n");
    printf("  bombs, using hints to guide your choices.\n");
    printf("\n");
    printf("Command-line usage:\n");
    printf("  fortuneFinder [--mode easy|hard] [--help]\n");
    printf("\n");
    printf("Options:\n");
    printf("  --mode easy   Start a normal game in easy mode (5x5, default).\n");
    printf("  --mode hard   Start a normal game in hard mode  (6x6).\n");
    printf("  --test easy   Start in easy TEST mode (fixed board layout).\n");
    printf("  --test hard   Start in hard TEST mode (fixed board layout).\n");
    printf("  --help        Show this help message and exit.\n\n");
    printf("Example commands:\n");
    printf("  ./fortuneFinder\n");
    printf("  ./fortuneFinder --mode hard\n");
    printf("  ./fortuneFinder --test easy\n");
    printf("  ./fortuneFinder --help\n\n");
    printf("How the grid works:\n");
    printf("At the start of the game, every box is hidden and is shown as its box number\n");
    printf("      ------------------------------\n");
    printf("      | 1 | | 2 | | 3 | | 4 | | 5 |\n");
    printf("      ------------------------------\n");
    printf("      | 6 | | 7 | | 8 | | 9 | | 10 |\n");
    printf("      ------------------------------\n");
    printf("      | 11 || 12 || 13 || 14 || 15 |\n");
    printf("      ------------------------------\n");
    printf("      | 16 || 17 || 18 || 19 || 20 |\n");
    printf("      ------------------------------\n");
    printf("      | 21 || 22 || 23 || 24 || 25 |\n");
    printf("      ------------------------------\n");
    printf("Legend:\n");
    printf("  *  : Treasure (increases your score)\n");
    printf("  B  : Bomb (game ends immediately)\n");
    printf("  ?  : Hint box (reveals a hint about nearby items)\n");
    printf("  .  : Revealed empty cell (no treasure, bomb, or hint)\n\n");
    printf("How to play:\n");
    printf("  - On each turn, enter a box number between 1 and N.\n");
    printf("  - If you reveal a treasure (*), your score increases.\n");
    printf("  - If you reveal a bomb (B), the game is over and you lose.\n");
    printf("  - If you reveal a hint (?), the game shows additional\n");
    printf("    information to help you choose future boxes: the prosibility\n");
    printf("    on the occurance of bomb or treasure near you. (ie. #of bombs / 8)\n");
    printf("  - When all treasures have been found, you win and the final\n");
    printf("    score is displayed.\n\n");
    printf("Input and quitting:\n");
    printf(" - Enter 0 at any time to quit the game early.\n");
    printf(" - If you enter a number outside the valid range, you will be.\n");
    printf("   asked to try again without changing the board.\n");
    printf(" - If a non-numeric value is entered, the game exits with an input error message.\n");
    printf("\n");
    printf("==================================================\n");
    printf(" MODULE OVERVIEW (components of the program)\n");
    printf("==================================================\n\n");
    printf("main.c (Core control & interface):\n");
    printf(" - Parses command-line options (--mode, --test, --help).\n");
    printf(" - Runs the main game loop and coordinates all modules.\n\n");
    printf("initializer.c (Board setup):\n");
    printf(" - Builds the hidden board for easy/hard or test layouts.\n");
    printf(" - Places treasures (*), bombs (B), and hints (?) on the grid.\n\n");
    printf("status.c (Game status and scoring):\n");
    printf(" - Evaluates the player's choice (treasure, bomb, hint, or empty).\n");
    printf(" - Updates the score and detects win/lose conditions for main.c.\n\n");
    printf("grid.c (Grid display & reveal helpers):\n");
    printf(" - Creates the numbered grid and prints the visible board to the screen.\n");
    printf(" - Reveals symbols under chosen tiles and supports debug printing.\n\n");
}

/*
 * DESCRIPTION: The inputCheck function parses command-line arguments to set the game mode and test flag.
 * It validates the argument count and displays the optional flags if entered by the user.
 *
 * PARAMETERS:
 *   argc: number of command-line arguments.
 *   argv: array of argument strings.
 *   mode: pointer to an integer to store the determined game mode.
 *   test: pointer to a boolean to indicate if test mode (fixed seed) should be used.
 * RETURNS:
 *   returns 0 upon successful argument check
 * EXIT CODES:
 *   exits 1 if user types an unknown option
 *   exits 2 if user chooses an unknown mode
 *   exits 3 if user types too many arguments
 */
int inputCheck(int argc, char *argv[], int *mode,bool *test){
    //Check if no arguments are provided; default to easy mode
    if(argc == 1){
        *mode = MODE_EASY;
        return 0;
    }

    if (argc == 2){
        //Check if user entered the '--help' option
        if (strcmp(argv[1], "--help") == 0){
            help();
            exit (EXIT_SUCCESS);
        }else{
            fprintf(stderr, "Error: unknown option '%s'.\n", argv[1]);
            usage();
            exit(1);
        }
    }

    //Handle case with exactly 3 arguments
    if (argc == 3){
        //Check for the '--mode' option and set the game difficulty, otherwise print error if no option is provided
        if(strcmp(argv[1], "--mode") == 0){
            if(strcmp(argv[2], "easy") == 0){
                *mode = MODE_EASY;
                return 0;
            }else if (strcmp(argv[2], "hard") == 0){
                *mode = MODE_HARD;
                return 0;
            }else{
                fprintf(stderr, "Error: unknown mode '%s' (expected 'easy' or 'hard').\n", argv[2]);
                usage();
                exit(2);
            }
        }

        //Check for the '--test' option and set the test flag and difficulty
        if(strcmp(argv[1],"--test")==0){
            if (strcmp(argv[2],"easy")==0){
                *mode = MODE_EASY;
                *test = true;
                return 0;
            }else if (strcmp(argv[2],"hard")==0){
                *mode = MODE_HARD;
                *test = true;
                return 0;
            }else{
                fprintf(stderr,"Error: unknown test mode '%s'(expected 'easy' or 'hard').\n",argv[2]);
                usage();
                exit(2);
            }
        }
        
        //Arguments are 3 but do not match expected options
        fprintf(stderr, "Error: no such flag exists.\n");
        usage();
        exit(3);
    }
    //Handle case with more then 3 arguments
    fprintf(stderr, "Error: too many arguments.\n");
    usage();
    exit(3);
}

/*
 * DESCRIPTION: The main function initializes the game, handles the argument check,
 * sets up the board based on the selected mode, and runs the main game loop.
 *
 * RETURNS:
 *   returns EXIT_SUCCESS upon on normal completion or user quit, otherwise exit code 1-3
 */
int main(int argc, char *argv[]){
    int mode; //Stores the selected game difficulty
    bool test = false; //Flag to determine if the game should use a fixed seed for testing
    inputCheck(argc, argv, &mode, &test);

    //Use a fixed seed for predictable boards in test mode
    if (test){
        srand(1234);
    }
    //Use the current time to seed for random boards in regular play
    else {
        srand(time(NULL));
    }
    outputBanner();


    int score = 0; //Tracks the plyer's current score
    int board[MAX_BOARD][MAX_BOARD]; //The hidden grid storing the actual game items
    int size = 1; //Dimension of the game grid
    
    //Item counts, configured by game mode
    int treasures;
    int bombs;
    int hints;
    bool hard = false; //Boolean flag to easily pass mode info to helper functions
    
    //Set parameters for HARD mode (6x6 board, 5 treasures, 8 bombs, 3 hints)
    if (mode == MODE_HARD){
        hard = true;
        size=6;
        treasures = 5;
        bombs = 8;
        hints = 3;
        printf("Starting game in hard mode.\n");
        
    //Set parameters for EASY mode (5x5 board, 6 treasures, 4 bombs, 5 hints)
    }else{
        size=5;
        treasures=6;
        bombs=4;
        hints=5;
        printf("Starting game in easy mode.\n");
    }

    //Display grid to the player with numbers as placeholders and populate with items
    int intGrid[size][size];
    printf("Score has been reset to %d.\n", score);
    makeGrid(size, intGrid);
    board_maker(board, hard);
    printGrid(size, intGrid); 
    
    int userInput;
    
    //Arrays to store the row and column indices of all hidden items
    //treasures (* = 42)
    int treasureRows[MAX_BOARD*MAX_BOARD];
    int treasureCols[MAX_BOARD*MAX_BOARD];
    get_item_rows(board, size, 42, treasureRows);
    get_item_cols(board, size, 42, treasureCols);

    //Bombs (B = 66)
    int bombRows[MAX_BOARD*MAX_BOARD];
    int bombCols[MAX_BOARD*MAX_BOARD];
    get_item_rows(board, size, 66, bombRows);
    get_item_cols(board, size, 66, bombCols);

    //Hints (? = 63)
    int hintRows[MAX_BOARD*MAX_BOARD];
    int hintCols[MAX_BOARD*MAX_BOARD];
    get_item_rows(board, size, 63, hintRows);
    get_item_cols(board, size, 63, hintCols);
    
    int gameOver = 0;//Flag to control the main game loop

    //Loop until gameOver flag is set to 1
    while (!gameOver){
        printf("\n====================================\n");
        printf("\nEnter a box number between 1 and %d (or 0 to quit): ", size * size);
        
        //Check if the suer input is a valid integer
        if (scanf("%d", &userInput) != 1){
            printf("Input error. Exiting game. \n\n");
            break;
        }

        //Check if the user entered '0' to quit the game
        if (userInput == 0){
            printf("You chose to quit. Final score %d.\n", score);
            break;
        }

        //Check if the input box number is within valid range
        if (userInput < 1 || userInput > size * size){
            printf("Invalid box number. Please try again. \n\n");
            continue;
        }
        updateVisibleGrid(size, userInput, board, intGrid);
        printGrid(size, intGrid);
        printf("\n");
        int result = status(userInput, mode, treasureRows, treasureCols, bombRows, bombCols, hintRows, hintCols, &score);
        
        //Check if the status function signaled that the game is over 
        if (result == 1){
            gameOver = 1;
        }
    }
    printf("\n");

    return EXIT_SUCCESS;

}