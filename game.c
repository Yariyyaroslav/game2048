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
  if (!board)
    return;
  for (int i = 0; i < rows; i++) {
    free(board[i]);
  }
  free(board);
}
void clearBoard(int **board, int rows, int columns) {
  if (!board)
    return;
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
        for (int i = 0; i < rows; i++){
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
            if (pos < rows){
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