#define MIN_SIZE 2
#define MAX_SIZE 20

int **createBoard(int rows, int columns);
void freeBoard(int **board, int rows);
void clearBoard(int **board, int rows, int columns);
void printBoard(int **board, int rows, int columns);

int moveLeft(int **board, int rows, int columns, int *score);
int moveRight(int **board, int rows, int columns, int *score);
int moveUp(int **board, int rows, int columns, int *score);
int moveDown(int **board, int rows, int columns, int *score);

int addRandomTile(int **board, int rows, int columns);
int countEmptyCells(int **board, int rows, int columns);
int findLargestTile(int **board, int rows, int columns);
int canMove(int **board, int rows, int columns);

int saveGame(const char *filename, int **board, int rows, int columns, int score, int totalMoves, int target);
int loadGame(const char *filename, int ***board, int *rows, int *columns, int *score, int *totalMoves, int *target);