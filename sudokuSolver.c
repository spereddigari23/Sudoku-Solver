#include <stdio.h>
#include <stdlib.h>
int sudoku[9][9];
int hold[2];
void printSudoku(){
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            printf("%d  ",sudoku[i][j]);
        }
        printf("\n");
    }
    return;
}
int checkRow(int number, int row){
    for(int i = 0; i<9; i++){
        if(sudoku[row][i] == number){
            return 0;
        }
    }
    return 1;
}
int checkColumn(int number, int col){
    for(int i = 0; i<9; i++){
        if(sudoku[i][col] == number){
            return 0;
        }
    }
    return 1;
}
int checkGrid(int row, int col, int number){
    row = (row/3)*3;
    col = (col/3)*3;
    for(int i = row; i<row+3; i++){
        for(int j = col; j<col+3; j++){
            if(sudoku[i][j] == number){
                return 0;
            }
        }
    }
    return 1;
}
void unassigned(){
    hold[0] = -1;
    hold[1] = -1;

    for(int row = 0; row<9; row++){
        for(int col = 0; col<9; col++){
            if(sudoku[row][col] == 0){
                hold[0] = row;
                hold[1] = col;
                return;
            }
        }
    }
    return;
}
int sudokuSolver(){
    unassigned();
    if(hold[0] == -1){
        return 1;
    }
    int row = hold[0];
    int col = hold[1];
    for(int number = 1; number<=9; number++){
        if(checkColumn(number, col) == 1 && checkRow(number, row) == 1 && checkGrid(row, col, number) == 1){
            sudoku[row][col] = number;
            int check = sudokuSolver();
            if(check == 1){
                return 1;
            }
            sudoku[row][col] = 0;
        }
    }
    return 0;
}
int main(int argc, char *filename[argc+1]){
    FILE *file = fopen(filename[1], "r");
    if(file == NULL){
        printf("ERROR, FILE NOT FOUND");
        EXIT_FAILURE;
    }
    char values[40];
    int cindex = 0;
    int rindex = 0;
    while(rindex != 9){
        fgets(values, 40, file);
        for(int i = 0; i<=32; i+=4){
            char c = values[i];
            if(c == '-'){
                sudoku[rindex][cindex] = 0;
                cindex++;
            }else{
                int val = atoi(&c);
                sudoku[rindex][cindex] = val;
                cindex++;
            }
        }
        cindex = 0;
        rindex++;
    }
    sudokuSolver();
    printSudoku();
}