#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void printSudoku(int sudoku[9][9]);
int isNumberInRow(int sudoku[9][9], int row, int number);
int isNumberInColumn(int sudoku[9][9], int column, int number);
int isNumberInSubgrid(int sudoku[9][9], int startRow, int startCol, int number);
void generateRandomSudoku(int sudoku[9][9], int numRandomValues);
int isValidMove(int sudoku[9][9], int row, int col, int number);
int isSudokuSolved(int sudoku[9][9]);

int main() {
    srand(time(NULL));

    int sudoku[9][9] = { {0} };
    int numRandomValues;

    printf("Enter the number of random values to fill in the Sudoku: ");
    scanf("%d", &numRandomValues);

    if (numRandomValues < 0 || numRandomValues > 81) {
        printf("Invalid number. Please enter a number between 0 and 81.\n");
        return 1;
    }

    generateRandomSudoku(sudoku, numRandomValues);

    printSudoku(sudoku);

    while (!isSudokuSolved(sudoku)) {
        int row, col, number;

        do {
            printf("Enter row (1-9) (0 to quit): ");
            scanf("%d", &row);
            if (row == 0) {
                printf("Game abandoned.\n");
                break;
            } 
        } while (row < 1 || row > 9);  

        if (row == 0)
            break;

        do {
            printf("Enter column (1-9) (0 to quit): ");
            scanf("%d", &col);
            if (col == 0) {
                printf("Game abandoned.\n");
                break;
            }
        } while (col < 1 || col > 9);

        if (col == 0)
            break;

        do {
            printf("Enter number (1-9) separated by spaces (0 to quit): ");
            scanf("%d", &number);
            if (number == 0) {
                printf("Game abandoned.\n");
                break;
            }
        } while (number < 1 || number > 9);

        if (number == 0)
            break;

        if (isValidMove(sudoku, row - 1, col - 1, number)) {
            sudoku[row - 1][col - 1] = number;
            printSudoku(sudoku);
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    if (isSudokuSolved(sudoku)) {
        printf("Congratulations! Sudoku solved.\n");
    }

    return 0;
}

void printSudoku(int sudoku[9][9]) {
    write(1, "\n", 1);
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i > 0) {
            for (int k = 0; k < 21; k++) {
                write(1, "-", 1);
            }
            write(1, "\n", 1);
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j > 0) {
                write(1, "| ", 2);
            }
            printf("%d ", sudoku[i][j]);
        }
        write(1, "\n", 1);
    }
    write(1, "\n", 1);
}

int isNumberInRow(int sudoku[9][9], int row, int number) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == number) {
            return 1;
        }
    }
    return 0;
}

int isNumberInColumn(int sudoku[9][9], int column, int number) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][column] == number) {
            return 1;
        }
    }
    return 0;
}

int isNumberInSubgrid(int sudoku[9][9], int startRow, int startCol, int number) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == number) {
                return 1;
            }
        }
    }
    return 0;
}

void generateRandomSudoku(int sudoku[9][9], int numRandomValues) {
    for (int k = 0; k < numRandomValues; k++) {
        int i, j, num;
        do {
            i = rand() % 9;
            j = rand() % 9;
            num = rand() % 9 + 1;
        } while (sudoku[i][j] != 0 || isNumberInRow(sudoku, i, num) || isNumberInColumn(sudoku, j, num) || isNumberInSubgrid(sudoku, i - i % 3, j - j % 3, num));
        sudoku[i][j] = num;
    }
}

int isValidMove(int sudoku[9][9], int row, int col, int number) {
    return !isNumberInRow(sudoku, row, number) && !isNumberInColumn(sudoku, col, number) && !isNumberInSubgrid(sudoku, row - row % 3, col - col % 3, number);
}

int isSudokuSolved(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                return 0; 
            }
        }
    }
    return 1;
}
