#include <stdio.h>
#include <stdlib.h>

int **readFile(char *fileName){
    FILE *fptr = fopen(fileName, "r");
    if (fptr == NULL){
        printf("File not found.\n");
        exit(0);
        
    }
    int **grid = (int **)malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; i++) {
        grid[i] = (int *)malloc(9 * sizeof(int));
        fscanf(fptr, "%d %d %d %d %d %d %d %d %d",
               &grid[i][0], &grid[i][1], &grid[i][2],
               &grid[i][3], &grid[i][4], &grid[i][5],
               &grid[i][6], &grid[i][7], &grid[i][8]);
        
    }
    return grid;
    
}

void printArray(int **array){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
        printf("%d  ", array[i][j]);        
    }
    printf("\n");
}

int checkBox(int **sudoku, int x, int y, int i, int j, int step){
    // if they're in the same box
    if (i >= 0 && j >= 0 && i < 9 && j < 9){ //check bounds
        if ((x/3 == i/3) && (y/3 == j/3)){
            if(i != x && j != y && (sudoku[i][j] == sudoku[x][y])){
                return 0;
            }
            
            step++;
            if(step > 4){
                return 1;
            }
            
            int up, down, left, right;
            down = checkBox(sudoku, x, y, i, j-1, step);
            up = checkBox(sudoku, x, y, i, j+1, step);
            right = checkBox(sudoku, x, y, i+1, j, step);
            left = checkBox(sudoku, x, y, i-1, j, step);
                
            return up && down && left && right;
        }
    }
    return 1;
    // if they're not in the same box, the value doesn't matter
    // it doesn't invalidate
}

int solutionCheck(int **sudoku, int x, int y){ // returns 1 for solution valid, 0 for invalid
    // Get the current value
    int currentValue = sudoku[x][y];
    
    // Check horizontal
    for(int i = 0; i < 9; i++){
        if(i != x){
            int cellValue = sudoku[i][y];
            if(cellValue == currentValue){
                return 0;
            }
        }
    }
    
    // Check vertical
    for(int j = 0; j < 9; j++){
        if(j != y){
            int cellValue = sudoku[x][j];
            if(cellValue == currentValue){
                return 0;
            }
        }
    }

    
    // Check box
    return checkBox(sudoku, x, y, x, y, 0);
    
}


int main(){
    int **sudoku = readFile("sudoku.txt");
    
    printArray(sudoku);
    int correct = 1;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if(!solutionCheck(sudoku, i, j)){
                printf("Solution invalid\n");
                return 0;
            }
        }
    }
    printf("The solution is valid!\n");

}
