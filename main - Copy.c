//Dylan Bearman
//R00190268

#include <stdio.h>
#include "maze_gen.c"
#define WALL 'w'
#define POTION '#'
#define ME '@'
#define LASTME ' '

void printMaze(struct  maze generateMaze,int myRow, int myCol, int row, int col, int potionsCollected) {
    //printf("My Position:");
    printf("\nPotions: %d\n", potionsCollected);
    for (row = 0; row < generateMaze.h; row++) {
        for (col = 0; col < generateMaze.w; col++) {
            if (col == myCol && row == myRow) {
                putchar(generateMaze.a[row][col] = ME);
            } else {
                putchar(generateMaze.a[row][col]);

            }
        }
        putchar('\n');
    }
}
// 206 220 234 271 272
// these are lines from the given file that generates the maze that i had to change
// the first i had to change to srand and the rest to rand as they were giving me errors

//i understand i got an extension but i also took the extra week as i couldn't implement it all
//i understand there is a 10 percent reduction
int main() {
    int height;
    int width;
    int cellSize;
    int randomSeed;
    int fogRadius;
    char input = 0;
    int row = 1;
    int col = 1;
    int myRow = 1;
    int myCol = 1;
    int startRow = 1;
    int startCol = -1;
    int potionsCollected = 0;
    int potionsNeeded = 3;

    //values needed to generate the maze
    printf("Width=");
    scanf("%d", &width);
    printf("Height=");
    scanf("%d", &height);
    printf("Random seed=");
    scanf("%d", &randomSeed);
    printf("Cell size (odd number=");
    scanf("%d", &cellSize);
    printf("Fog radius=");
    scanf("%d", &fogRadius);
    printf("Enter your next move (w,a,s,d) or e to exit");

    //generates and prints the maze
    struct  maze generateMaze = generate_maze(width, height, cellSize, randomSeed);
    printMaze(generateMaze,myRow,myCol,row,col,potionsCollected);

    //switch statement withing a while loop
    //loop will end if the user presses e to exit
    while (input!='e') {
        //gets the current position and replaces it with blank
        //this way there isnt a continous trail behind you
        generateMaze.a[myRow][myCol] = LASTME;
        scanf("%c", &input);
        //every switch statement checks for walls and potions
        //wasd are used to move around
        switch (input) {
            // case a
            // in this case we use it for moving left
            // there is extra conditions in here to prevent the user from leaving the
            // maze through the entry point

            case 'a' :
                if (myRow == startRow && myCol-1 == startCol){
                    break;
                }
                if (generateMaze.a[myRow][myCol-1] == WALL){
                    break;
                }
                else {
                    myCol--;
                    if (generateMaze.a[myRow][myCol] == POTION){
                        potionsCollected ++;}
                }
                printMaze(generateMaze,myRow,myCol,row,col,potionsCollected);
                break;
            case 'w' :
                //case w
                // this is for going up
                // standard as we cant leave the maze with the up button
                if (generateMaze.a[myRow-1][myCol] == WALL) {
                    break;
                }
                else {
                    myRow--;
                    if (generateMaze.a[myRow][myCol] == POTION){
                        potionsCollected ++;}
                }
                printMaze(generateMaze,myRow,myCol,row,col,potionsCollected);
                break;

            case 's' :
                //case s
                // this is for going down
                //  also standard as we cant leave the maze with the up button
                if (generateMaze.a[myRow+1][myCol] == WALL) {
                    break;
                }
                else {
                    myRow++;
                    if (generateMaze.a[myRow][myCol] == POTION){
                        potionsCollected ++;}
                }
                printMaze(generateMaze,myRow,myCol,row,col,potionsCollected);
                break;
            case 'd' :
                //case d
                //this has extra conditions
                //the standard wall and potion check
                //nut we also need to check if the user is at the end of the maze
                //and weather they have the potions needed to leave
                if (generateMaze.a[myRow][myCol+1] == WALL){
                    break;
                }
                if ((myRow >= generateMaze.h-2 && myCol >= generateMaze.w-1) &&
                (potionsCollected == potionsNeeded)){
                    printf("You escaped, well done");
                    exit(0);
                }
                if ((myRow >= generateMaze.h-2 && myCol >= generateMaze.w-1) &&
                    (potionsCollected != potionsNeeded)){
                    printf("You need 3 potions to escape\n");
                    myCol --;
                    break;
                }
                else {
                    myCol++;
                    if (generateMaze.a[myRow][myCol] == POTION){
                        potionsCollected++;
                    }
                }
                printMaze(generateMaze,myRow,myCol,row,col,potionsCollected);
                break;
                //this is for other cases outside wasde
                //it will break and the user can enter the correct letter (wasde)
            default:
                break;
        }
    }
}