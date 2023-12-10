#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "colours.h"

#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

/*--------------------------------------------------------------------------------------------------------------*/
///global variable for number of rows and columns
int mapRow = 11;
int mapC = 32;

///changing the colours of the walls, pacman, ghosts, and dots
#include <TargetConditionals.h>
#include <cstdio>
#include <cstdlib>
int colourChange(int colour) {
    switch (colour) {
        case BLUE:   printf("\x1b[34m"); break;
        case YELLOW: printf("\x1b[33m"); break;
        case PINK:   printf("\x1b[35m"); break;
        case WHITE:  printf("\x1b[0m"); break;
        default:     return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*--------------------------------------------------------------------------------------------------------------*/
///prints new map corresponding to the players input
void printMap(char **map){ //double pointer to map
    for (int i = 0; i<mapRow;i++) { //nested for loop to loop through map
        for (int n = 0;n<mapC;n++) {
            printf("%c", map[i][n]); //prints map
        }
    }
    printf("\n");
}

/*--------------------------------------------------------------------------------------------------------------*/
///function to see if player won the game
int winCheck(char **map){
    for (int i = 0; i < mapRow; i++){
        for (int n = 0; n < mapC; n++){
            if (map[i][n] == DOT){ //if there are still dots left in the map
                return 0; //player did not win
            }
        }
    }

}

/*--------------------------------------------------------------------------------------------------------------*/
///function to see if player lost game.
int loseCheck(int pX, int pY, int g1X, int g1Y, int g2X, int g2Y){
    if (pX == g1X){
        if (pY == g1Y){
            printf("Sorry, you lose. Press any key to exit the game\n");
            getchar();
            exit(0); //exits game
        }
    }

    else if (pX == g2X){
        if (pY == g2Y) {
            printf("Sorry, you lose. Press any key to exit the game\n");
            getchar();
            exit(0); //exits game
        }
    }



}

/*--------------------------------------------------------------------------------------------------------------*/
///function to see if player hits a wall
int isWall(char input, int y, int x, char **map){ //the x and y position of the pacman/ghost is inputted into this function, also gets the input of user
    if (input == UP){ //if user input is 'w'
        if (map[y-1][x] == WALL) {
            return 0; //there is a wall
        } else {
            return 1; //no wall
        }
    }
    if (input == DOWN){
        if (map[y+1][x] == WALL) {
            return 0; //there is a wall
        } else {
            return 1; //no wall and can move
        }
    }
    if (input == RIGHT){
        if (map[y][x+3] == WALL) {
            return 0; //there is a wall
        } else {
            return 1;
        }
    }
    if (input == LEFT){
        if (map[y][x-3] == WALL) {
            return 0; //there is a wall
        } else {
            return 1;
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------*/
///ghost 1 movement
int g1Movement(char **map, int g1Y, int g1X){

    //generates random number, the random number will correspond to how the ghost moves
    srand(time(NULL));
    int random = rand() % 4;

    if (random == 0){ //if the random number is zero, the ghosts moves up
        //check isWall
        if (isWall(UP, g1Y, g1X, map)==1){
            g1Y -= 1; //replace the old y value of the ghosts, decrease by 1
            if (map[g1Y][g1X] == DOT){ //if there is dot on new coordinate of ghost, the old coordinate of the ghost will be replaced with a dot
                map[g1Y+1][g1X] = DOT;
                map[g1Y][g1X] = GHOST;
            } else if (map[g1Y][g1X] == EMPTY){ //if there is empty space on the new coordinate of ghost, the old coordinate of the ghost will be replaced with empty character
                    map[g1Y+1][g1X] = EMPTY;
                    map[g1Y][g1X] = GHOST;
                }
        }
    }
    //the rest of the else if is the same as the one above, but the direction of movement is different
    else if (random == 1){ //move down
        if (isWall(DOWN, g1Y, g1X, map)==1){
            g1Y += 1;
            if (map[g1Y][g1X] == DOT){
                map[g1Y-1][g1X] = DOT;
                map[g1Y][g1X] = GHOST;
            } else if (map[g1Y][g1X] == EMPTY){
                map[g1Y-1][g1X] = EMPTY;
                map[g1Y][g1X] = GHOST;
            }
        }
    }
    else if (random == 2){ //move right
        if (isWall(RIGHT, g1Y, g1X, map)==1){
            g1X += 3;
            if (map[g1Y][g1X] == DOT){
                map[g1Y][g1X-3] = DOT;
                map[g1Y][g1X] = GHOST;
            } else if (map[g1Y][g1X] == EMPTY){
                map[g1Y][g1X-3] = EMPTY;
                map[g1Y][g1X] = GHOST;
            }
        }
    }
    else  if (random == 3){ //move left
        if (isWall(LEFT, g1Y, g1X, map)==1){
            g1X -= 3;
            if (map[g1Y][g1X] == DOT){
                map[g1Y][g1X+3] = DOT;
                map[g1Y][g1X] = GHOST;
            } else if (map[g1Y][g1X] == EMPTY){
                map[g1Y][g1X+3] = EMPTY;
                map[g1Y][g1X] = GHOST;
            }
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------*/
///ghost 2 movement
int g2Movement(char **map, int g2Y, int g2X){ //the same code for the movement of ghost 1, but for instead ghost 2.

    //generates random number
    srand(time(NULL));
    int random = rand() % 4;

    if (random == 0){ //move up
        //check isWall
        if (isWall(UP, g2Y, g2X, map)==1){
            g2Y -= 1;
            if (map[g2Y][g2X] == DOT){
                map[g2Y+1][g2X] = DOT;
                map[g2Y][g2X] = GHOST;
            } else if (map[g2Y][g2X] == EMPTY){
                map[g2Y+1][g2X] = EMPTY;
                map[g2Y][g2X] = GHOST;
            }
        }
    }
    else if (random == 1){ //move down
        //check isWall
        if (isWall(DOWN, g2Y, g2X, map)==1){
            g2Y += 1;
            if (map[g2Y][g2X] == DOT){
                map[g2Y-1][g2X] = DOT;
                map[g2Y][g2X] = GHOST;
            } else if (map[g2Y][g2X] == EMPTY){
                map[g2Y-1][g2X] = EMPTY;
                map[g2Y][g2X] = GHOST;
            }
        }
    }
    else if (random == 2){ //move right
        //check isWall
        if (isWall(RIGHT, g2Y, g2X, map)==1){
            g2X += 3;
            if (map[g2Y][g2X] == DOT){
                map[g2Y][g2X-3] = DOT;
                map[g2Y][g2X] = GHOST;
            } else if (map[g2Y][g2X] == EMPTY){
                map[g2Y][g2X-3] = EMPTY;
                map[g2Y][g2X] = GHOST;
            }
        }
    }
    else  if (random == 3){ //move left
        //check isWall
        if (isWall(LEFT, g2Y, g2X, map)==1){
            g2X -= 3;
            if (map[g2Y][g2X] == DOT){
                map[g2Y][g2X+3] = DOT;
                map[g2Y][g2X] = GHOST;
            } else if (map[g2Y][g2X] == EMPTY){
                map[g2Y][g2X+3] = EMPTY;
                map[g2Y][g2X] = GHOST;
            }
        }
    }

}
/*--------------------------------------------------------------------------------------------------------------*/
int main() {

        int pX, pY, g1X, g1Y, g2X, g2Y; //initializing variables

        FILE *fp = fopen("map.txt", "r"); //opens map text
        char **map = (char **) malloc(mapRow * sizeof(char *)); //using  pointers to allocate the rows

        //allocating the columns into the row i
        for (int i = 0; i < mapRow; i++) {
            map[i] = (char *) malloc(mapC * sizeof(char *)); //using pointers to allocate the columns
        }

        //populating the map with values
        //scanning each row and column
        map[mapRow - 1][mapC - 1] = '\n';
        for (int i = 0; i < mapRow; i++) {
            for (int n = 0; n < mapC; n++) {
                fscanf(fp, "%c", &map[i][n]);
            }
        }

        printMap(map); //print the initial map

        //while the pacman is alive, the loop will run forever
        while (1) {
            //finding the coordinates of the ghost's and pacman
            int temp = 1; //setting temp values
            for (int i = 0; i < mapRow; i++) {
                for (int n = 0; n < mapC; n++) {
                    if (map[i][n] == PACMAN) { //finding pacmans coordinates
                        pY = i;
                        pX = n;
                    } else if (temp == 1) { //if first ghost is still not found
                        if (map[i][n] == GHOST) { //finding ghosts coordinates
                            g1Y = i;
                            g1X = n;
                            temp = 0; //set temp to zero to indicate that the first ghost is found
                        }
                    } else if (map[i][n] == GHOST) { //if second is found
                        g2Y = i;
                        g2X = n;
                    }
                }
            }

            char input = getchar();//getting user input
            getchar();

            if (isWall(input, pY, pX, map) == 0) { //if isWall equal 0, it hits wall
                //moves the ghosts
                g1Movement(map, g1Y, g1X);
                g2Movement(map, g2Y, g2X);
                loseCheck(pX, pY, g1X, g1Y, g2X, g2Y); //checks if user loses
                printMap(map);
            } else if (isWall(input, pY, pX, map) == 1) { //if isWall equals 1: it does not hit wall
                if (input == UP) {
                    map[pY][pX] = EMPTY;//set old location of pacman to empty
                    map[pY - 1][pX] = PACMAN;
                    pY -= 1; //change pacman y coordinate
                } else if (input == DOWN) {
                    map[pY][pX] = EMPTY;//set old location of pacman to empty
                    map[pY + 1][pX] = PACMAN;
                    pY += 1;//change pacman y coordinate
                } else if (input == RIGHT) {
                    map[pY][pX] = EMPTY;//set old location of pacman to empty
                    map[pY][pX + 3] = PACMAN;
                    pX += 3; //change pacman x coordinate
                } else if (input == LEFT) {
                    map[pY][pX] = EMPTY; //set old location of pacman to empty
                    map[pY][pX - 3] = PACMAN;
                    pX -= 3;//change pacman x coordinate
                }
                printMap(map); //prints map after all new movements

                //using the functions of the moving ghosts
                g1Movement(map, g1Y, g1X);
                g2Movement(map, g2Y, g2X);

                loseCheck(pX, pY, g1X, g1Y, g2X, g2Y);
                //checking if the pacman ate all the dots
                if (winCheck(map) != 0) { //if no more dots
                    printMap(map);
                    printf("Congratulations! You win! Press any key to exit the game\n");
                    getchar();
                    exit(0);
                }
            }
        }
    }