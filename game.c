#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int **createBoard(int rows, int columns) {
  int **board = malloc(rows * sizeof(int *));
  if (!board) {
    return NULL;
  }
  for (int i = 0; i < rows; i++) {
    board[i] = malloc(columns * sizeof(int));
    if (!board[i]) {
      for (int j = 0; j < i; j++) {
        free(board[j]);
      }
      free(board);
      return NULL;
    }
  }
  return board;
}
void freeBoard(int **board, int rows) {
  if (!board){
     return;
  }
   
  for (int i = 0; i < rows; i++) {
    free(board[i]);
  }
  free(board);
}
void clearBoard(int **board, int rows, int columns) {
  if (!board){
    return;
  }
    
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      board[i][j] = 0;
    }
  }
}
void printBoard(int **board, int rows, int columns) {
  if (!board) {
    printf("Board is not created.\n");
    return;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("+------");
    }
    printf("+\n");

    for (int j = 0; j < columns; j++) {
      if (board[i][j] == 0) {
        printf("|      ");
      } else {
        printf("| %4d ", board[i][j]);
      }
    }
    printf("|\n");
  }

  for (int j = 0; j < columns; j++) {
    printf("+------");
  }
  printf("+\n");
}
int moveLeft(int **board, int rows, int columns, int *score) {
  int changed = 0;
  int *temp = malloc(columns * sizeof(int));
  if (!temp) {
    return 1;
  }

  for (int i = 0; i < rows; i++) {
    int pos = 0;
    for (int j = 0; j < columns; j++) {
      temp[j] = 0;
    }
    for (int j = 0; j < columns; j++) {
      if (board[i][j] != 0) {
        temp[pos] = board[i][j];
        pos++;
      }
    }
    for (int j = 0; j < pos - 1; j++) {
      if (temp[j] != 0 && temp[j] == temp[j + 1]) {
        temp[j] *= 2;
        *score += temp[j];
        temp[j + 1] = 0;
        j++;
      }
    }
    pos = 0;
    for (int j = 0; j < columns; j++) {
      int val = 0;
      while (pos < columns && temp[pos] == 0) {
        pos++;
      }
      if (pos < columns) {
        val = temp[pos];
        pos++;
      }

      if (board[i][j] != val) {
        changed = 1;
        board[i][j] = val;
      }
    }
  }

  free(temp);
  return changed;
}
int moveRight(int **board, int rows, int columns, int *score) {
  int changed = 0;
  int *temp = malloc(columns * sizeof(int));
  if (!temp) {
    return 1;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      temp[j] = 0;
    }

    int pos = columns - 1;
    for (int j = columns - 1; j >= 0; j--) {
      if (board[i][j] != 0) {
        temp[pos] = board[i][j];
        pos--;
      }
    }
    for (int j = columns - 1; j > pos + 1; j--) {
      if (temp[j] != 0 && temp[j] == temp[j - 1]) {
        temp[j] *= 2;
        *score += temp[j];
        temp[j - 1] = 0;
        j--;
      }
    }
    pos = columns - 1;
    for (int j = columns - 1; j >= 0; j--) {
      int val = 0;
      while (pos >= 0 && temp[pos] == 0) {
        pos--;
      }
      if (pos >= 0) {
        val = temp[pos];
        pos--;
      }

      if (board[i][j] != val) {
        changed = 1;
        board[i][j] = val;
      }
    }
  }

  free(temp);
  return changed;
}
int moveUp(int **board, int rows, int columns, int *score) {
  int changed = 0;
  int *temp = malloc(rows * sizeof(int));
  if (!temp) {
    return 1;
  }

  for (int j = 0; j < columns; j++) {
    int pos = 0;
    for (int i = 0; i < rows; i++) {
      temp[i] = 0;
    }

    for (int i = 0; i < rows; i++) {
      if (board[i][j] != 0) {
        temp[pos] = board[i][j];
        pos++;
      }
    }
    for (int i = 0; i < pos - 1; i++) {
      if (temp[i] != 0 && temp[i] == temp[i + 1]) {
        temp[i] *= 2;
        *score += temp[i];
        temp[i + 1] = 0;
        i++;
      }
    }
    pos = 0;
    for (int i = 0; i < rows; i++) {
      int val = 0;
      while (pos < rows && temp[pos] == 0) {
        pos++;
      }
      if (pos < rows) {
        val = temp[pos];
        pos++;
      }

      if (board[i][j] != val) {
        changed = 1;
        board[i][j] = val;
      }
    }
  }

  free(temp);
  return changed;
}
int moveDown(int **board, int rows, int columns, int *score) {
  int changed = 0;
  int *temp = malloc(rows * sizeof(int));
  if (!temp) {
    return 1;
  }

  for (int j = 0; j < columns; j++) {
    for (int i = 0; i < rows; i++) {
      temp[i] = 0;
    }

    int pos = rows - 1;
    for (int i = rows - 1; i >= 0; i--) {
      if (board[i][j] != 0) {
        temp[pos] = board[i][j];
        pos--;
      }
    }

    for (int i = rows - 1; i > pos + 1; i--) {
      if (temp[i] != 0 && temp[i] == temp[i - 1]) {
        temp[i] *= 2;
        *score += temp[i];
        temp[i - 1] = 0;
        i--;
      }
    }

    pos = rows - 1;
    for (int i = rows - 1; i >= 0; i--) {
      int val = 0;
      while (pos >= 0 && temp[pos] == 0) {
        pos--;
      }
      if (pos >= 0) {
        val = temp[pos];
        pos--;
      }
      if (board[i][j] != val) {
        changed = 1;
        board[i][j] = val;
      }
    }
  }

  free(temp);
  return changed;
}
int countEmptyCells(int **board, int rows, int columns) {
  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (board[i][j] == 0) {
        count++;
      }
    }
  }
  return count;
}
int addRandomTile(int **board, int rows, int columns) {
  int emptyCount = countEmptyCells(board, rows, columns);
  if (emptyCount == 0) {
    return 1;
  }

  int targetIndex = rand() % emptyCount;
  int current = 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (board[i][j] == 0) {
        if (current == targetIndex) {
          if (rand() % 10 == 0) {
            board[i][j] = 4;
          } else {
            board[i][j] = 2;
          }
          return 0;
        }
        current++;
      }
    }
  }
  return 0;
}
int findLargestTile(int **board, int rows, int columns) {
    int maxTile = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] > maxTile) {
                maxTile = board[i][j];
            }
        }
    }
    return maxTile;
}
int canMove(int **board, int rows, int columns) {
    if (countEmptyCells(board, rows, columns) > 0) {
        return 0;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j + 1 < columns && board[i][j] == board[i][j + 1]){
                 return 0;
            }
            if (i + 1 < rows && board[i][j] == board[i + 1][j]){
                 return 0;
            }
        }
    }
    return 1;
}
int saveGame(const char *filename, int **board, int rows, int columns, int score, int totalMoves, int target) {
    if (!board){
         return 1;
    }
    FILE *file = fopen(filename, "w");
    if (!file){
         return 1;
    }

    fprintf(file, "%d %d\n", rows, columns);
    fprintf(file, "%d\n", score);
    fprintf(file, "%d\n", totalMoves);
    fprintf(file, "%d\n\n", target);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%d ", board[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}
int loadGame(const char *filename, int ***board, int *rows, int *columns, int *score, int *totalMoves, int *target) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return 1;
    }

    int newRows, newCols, newScore, newMoves, newTarget = 2048;
    if (fscanf(file, "%d %d", &newRows, &newCols) != 2) {
        fclose(file);
        return 1;
    }
    if (newRows < MIN_SIZE || newRows > MAX_SIZE || newCols < MIN_SIZE || newCols > MAX_SIZE) {
        fclose(file);
        return 1;
    }
    if (fscanf(file, "%d %d", &newScore, &newMoves) != 2) {
        fclose(file);
        return 1;
    }
    fscanf(file, "%d", &newTarget);

    int **newBoard = malloc(newRows * sizeof(int *));
    if (!newBoard) {
        fclose(file);
        return 1;
    }

    for (int i = 0; i < newRows; i++) {
        newBoard[i] = malloc(newCols * sizeof(int));
        if (!newBoard[i]) {
            freeBoard(newBoard, i);
            fclose(file);
            return 1;
        }
    }

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            if (fscanf(file, "%d", &newBoard[i][j]) != 1) {
                freeBoard(newBoard, newRows);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);

    if (*board != NULL) {
        freeBoard(*board, *rows);
    }

    *board = newBoard;
    *rows = newRows;
    *columns = newCols;
    *score = newScore;
    *totalMoves = newMoves;
    *target = newTarget;
    return 0;
}