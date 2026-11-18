//Protoype Functions
#define MAX_BOARD 6
int randomizer(int *row, int *col);
void board_maker(int board[MAX_BOARD][MAX_BOARD], bool hardMode);
void place_items(int board[MAX_BOARD][MAX_BOARD], int count, int itemNum);
bool has_item(int board[MAX_BOARD][MAX_BOARD], int r, int c);

int get_item_rows(int board[MAX_BOARD][MAX_BOARD], int size, int itemNum, int rows[]);
int get_item_cols(int board[MAX_BOARD][MAX_BOARD], int size, int itemNum, int cols[]);

void printGrid(int size, int (*print)[size]);
void makeGrid(int size, int (*grid)[size]);
void updateVisibleGrid(int size, int reveal, int board[MAX_BOARD][MAX_BOARD], int (*intGrid)[size]);

int checkchoice(int userInput, int mode,
                 int treasureRows[], int treasureCols[],
                 int bombRows[], int bombCols[],
                 int hintRows[], int hintCols[],
                 int *score);

int status(int userInput, int mode,
                 int treasureRows[], int treasureCols[],
                 int bombRows[], int bombCols[],
                 int hintRows[], int hintCols[],
                 int *score);