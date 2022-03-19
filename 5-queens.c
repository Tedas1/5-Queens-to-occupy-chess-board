#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// 1 - for attacked square
// 2 - for square captured by Queen
int N = 8;
int rows = 8, columns = 8, max = 5;
int** cleanArray() {
    int **Board = (int **)calloc(rows, sizeof(int));
    for (int i = 0; i < columns; ++i){
        Board[i] = (int *)calloc(columns, sizeof(int));
    }    
    return Board;
}

bool checkSolution(int **Board) {
    int countSquares = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (Board[i][j] >= 1) {
                ++countSquares;
            }
        }
    }
    if(countSquares == N*N) {
        return true;
    }
    return false;
}

void printSolution(int **Board) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            printf("%d", Board[i][j]);
        }
        puts("");
    }
    puts("");
}

int** attackEmptyOnes(int **Board, int row, int column) {
    for (int i = 0; i < columns; ++i) {
        if(Board[row][i] != 2) {
            Board[row][i] = 1;
        }
    }
    for (int i = 0; i < rows; ++i) {
        if(Board[i][column] != 2) {
            Board[i][column] = 1;
        }
    }
    int tempRow = row;
    int tempColumn = column;
    ++row;
    ++column;
    int negativeSlope = N - abs(row - column);
    int positiveSlope = N - abs(row + column - N - 1);
    if(positiveSlope != 1) {
        int upper, lower;
        if (column + row <= N+1) {
            upper = positiveSlope - column;
            lower = column - 1;
        } else {
            upper = N - column;
            lower = N - row;
        }
        for (int i = 0; i < upper; ++i) {
            if (Board[tempRow-1-i][tempColumn+1+i] != 2) {
                Board[tempRow-1-i][tempColumn+1+i] = 1;
            }
        }
        for (int i = 0; i < lower; ++i) {
            if (Board[tempRow+1+i][tempColumn-1-i] != 2) {
                Board[tempRow+1+i][tempColumn-1-i] = 1;
            }
        }
    }
    if(negativeSlope != 1) {
        int upper, lower;
        if ((column + row) / row < 2) {
            lower = negativeSlope - column;
            upper = negativeSlope - lower - 1;
        } else {
            lower = N - column;
            upper = negativeSlope - lower - 1;
        }
        for (int i = 0; i < upper; ++i) {
            if (Board[tempRow-1-i][tempColumn-1-i] != 2) {
                Board[tempRow-1-i][tempColumn-1-i] = 1;
            }
        }
        for (int i = 0; i < lower; ++i) {
            if (Board[tempRow+1+i][tempColumn+1+i] != 2) {
                Board[tempRow+1+i][tempColumn+1+i] = 1;
            }
        }
    }
    return Board;
}

bool solve(int **Board,  int currentRow, int currentColumn, int queenCount){  
    int tempBoard[N][N];
    while (1) {
        if (queenCount == max) { 
            if(checkSolution(Board)) {
                printSolution(Board);
            } 
            return false;                
        } else {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j){
                    tempBoard[i][j] = Board[i][j];
                }
            }
        }
        if (currentColumn == N) {
            currentColumn = 0;
            ++currentRow;
            if (currentRow == N) {
                return false;
            }
        }
        Board[currentRow][currentColumn] = 2;
        Board = attackEmptyOnes(Board, currentRow, currentColumn);

        if (solve(Board, currentRow, currentColumn + 1, queenCount + 1)) {    
            return true;
        } else {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    Board[i][j] = tempBoard[i][j]; // backTracking
                }
            }
            ++currentColumn;
        }
    }
}

int main() {
    int **Board = cleanArray();
    solve(Board, 0, 0, 0);
}
