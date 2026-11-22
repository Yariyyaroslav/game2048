#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  int **board = NULL;
  int rows = 0;
  int columns = 0;
  int score = 0;
  int highScore = 0;
  int totalMoves = 0;
  int target = 2048;
  int targetReached = 0;
  int choice;
  while (1) {
    printf("\n=== 2048 ===\n\n");
    printf("1. New game\n");
    printf("2. Print board\n");
    printf("3. Move left\n");
    printf("4. Move right\n");
    printf("5. Move up\n");
    printf("6. Move down\n");
    printf("7. Show score\n");
    printf("8. Show statistics\n");
    printf("9. Save game\n");
    printf("10. Load game\n");
    printf("11. Restart game\n");
    printf("0. Exit\n");
    printf("Choose option: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input.\n");
      continue;
    }
    if (choice == 0) {
      freeBoard(board, rows);
      break;
    }
    switch (choice) {
    case 1:
      int newRows;
      int newCols;
      printf("Rows: ");
      scanf("%d", &newRows);
      printf("Columns: ");
      scanf("%d", &newCols);

      if (newRows < MIN_SIZE || newRows > MAX_SIZE || newCols < MIN_SIZE ||
          newCols > MAX_SIZE) {
        printf("Allowed size: %d %d\n", MIN_SIZE, MAX_SIZE);
        break;
      }

      freeBoard(board, rows);
      board = createBoard(newRows, newCols);
      if (!board) {
        rows = 0;
        columns = 0;
        printf("Memory error.\n");
        return 1;
      }

      rows = newRows;
      columns = newCols;
      score = 0;
      totalMoves = 0;
      targetReached = 0;

      clearBoard(board, rows, columns);
      addRandomTile(board, rows, columns);
      addRandomTile(board, rows, columns);

      printf("Score: %d\n", score);
      printBoard(board, rows, columns);
      break;
    case 2:
      if (board) {
        printf("Score: %d\n", score);
      }
      printBoard(board, rows, columns);
      break;
    case 3:
      if (!board) {
        printf("Start a new game first.\n");
        break;
      }
      if (canMove(board, rows, columns) != 0) {
        printf("Game Over!\nFinal score: %d\n", score);
        break;
      }
      if (moveLeft(board, rows, columns, &score)) {
        addRandomTile(board, rows, columns);
        totalMoves++;
        if (score > highScore) {
          highScore = score;
        }
        printf("Score: %d\n", score);
        printBoard(board, rows, columns);
        if (!targetReached && findLargestTile(board, rows, columns) >= target) {
          printf("You reached %d!\n", target);
          targetReached = 1;
        }
        if (canMove(board, rows, columns) != 0) {
          printf("Game Over!\nFinal score: %d\n", score);
        }
      } else {
        printf("Nothing changed.\n");
      }
      break;

    case 4:
      if (!board) {
        printf("Start a new game first.\n");
        break;
      }
      if (canMove(board, rows, columns) != 0) {
        printf("Game Over!\nFinal score: %d\n", score);
        break;
      }
      if (moveRight(board, rows, columns, &score)) {
        addRandomTile(board, rows, columns);
        totalMoves++;
        if (score > highScore) {
          highScore = score;
        }
        printf("Score: %d\n", score);
        printBoard(board, rows, columns);
        if (!targetReached && findLargestTile(board, rows, columns) >= target) {
          printf("You reached %d!\n", target);
          targetReached = 1;
        }
        if (canMove(board, rows, columns) != 0) {
          printf("Game Over!\nFinal score: %d\n", score);
        }
      } else {
        printf("Nothing changed.\n");
      }
      break;

    case 5:
      if (!board) {
        printf("Start a new game first.\n");
        break;
      }
      if (canMove(board, rows, columns) != 0) {
        printf("Game Over!\nFinal score: %d\n", score);
        break;
      }
      if (moveUp(board, rows, columns, &score)) {
        addRandomTile(board, rows, columns);
        totalMoves++;
        if (score > highScore) {
          highScore = score;
        }
        printf("Score: %d\n", score);
        printBoard(board, rows, columns);
        if (!targetReached && findLargestTile(board, rows, columns) >= target) {
          printf("You reached %d!\n", target);
          targetReached = 1;
        }
        if (canMove(board, rows, columns) != 0) {
          printf("Game Over!\nFinal score: %d\n", score);
        }
      } else {
        printf("Nothing changed.\n");
      }
      break;

    case 6:
      if (!board) {
        printf("Start a new game first.\n");
        break;
      }
      if (canMove(board, rows, columns) != 0) {
        printf("Game Over!\nFinal score: %d\n", score);
        break;
      }
      if (moveDown(board, rows, columns, &score)) {
        addRandomTile(board, rows, columns);
        totalMoves++;
        if (score > highScore) {
          highScore = score;
        }
        printf("Score: %d\n", score);
        printBoard(board, rows, columns);
        if (!targetReached && findLargestTile(board, rows, columns) >= target) {
          printf("You reached %d!\n", target);
          targetReached = 1;
        }
        if (canMove(board, rows, columns) != 0) {
          printf("Game Over!\nFinal score: %d\n", score);
        }
      } else {
        printf("Nothing changed.\n");
      }
      break;
    case 7:
      printf("Current score: %d\n", score);
      printf("High score: %d\n", highScore);
      break;

    case 8:
      if (!board) {
        printf("Start a new game first.\n");
        break;
      }
      printf("Score: %d\n", score);
      printf("Largest tile: %d\n", findLargestTile(board, rows, columns));
      printf("Empty cells: %d\n", countEmptyCells(board, rows, columns));
      printf("Total moves: %d\n", totalMoves);
      break;
    case 9:
                if (!board) {
                    printf("Start a new game first.\n");
                    break;
                }
                if (saveGame("save.txt", board, rows, columns, score, totalMoves, target) == 0) {
                    printf("Game saved.\n");
                } else {
                    printf("Save failed.\n");
                }
                break;

            case 10:
                if (loadGame("save.txt", &board, &rows, &columns, &score, &totalMoves, &target) == 0) {
                    if (score > highScore) {
                        highScore = score;
                    }
                    targetReached = 0;
                    if (findLargestTile(board, rows, columns) >= target) {
                        targetReached = 1;
                    }
                    printf("Game loaded.\n");
                    printf("Score: %d\n", score);
                    printBoard(board, rows, columns);
                } else {
                    printf("Load failed.\n");
                }
                break;

            case 11:
                if (!board) {
                    printf("Start a new game first.\n");
                    break;
                }
                score = 0;
                totalMoves = 0;
                targetReached = 0;
                clearBoard(board, rows, columns);
                addRandomTile(board, rows, columns);
                addRandomTile(board, rows, columns);
                printf("Score: %d\n", score);
                printBoard(board, rows, columns);
                break;
                default:
      printf("Invalid option.\n");
      break;
    }
  }
}