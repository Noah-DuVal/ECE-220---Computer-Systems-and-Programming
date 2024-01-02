/*

Noah DuVal
663669152

For this MP the goal was to create a maze solver that used recursion and backtracking to search through a given maze to find
the end point. We were responsible for creating four functions that allowed the program to run. The first one was to 
create the maze based on a file given. We had open the file to read and then parse it into the given data structure
in the header file. Then we had to allocate the memory for all of the contentes that we wanted to save. The next function we
had to create was 'destroymaze' where we had to free the memory we previously allocated in the same order we called it. 
The third function was to print the maze in which I used neseted for loops to go cell by cell and print out the characters
The final function was to actually solve the maze. This consisted of about ten steps which completes it. The first three 
check that it is in bounds and that it is not the end nor a wall. Following that starts to fill in the solution path and 
starts recursing into new cells and paths. Then when those fail it backtracks replacing previous solutions into explored paths
instead.

*/





#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    
    int a;
    
    
    FILE *reader = fopen(fileName,"r");	//Opens file to be read
    
    maze_t * maze = malloc(sizeof(maze_t));	//allocated mem for maze structure
    
    fscanf(reader, "%d %d", &(maze->width), &(maze->height));		//finds height and width
    fgetc(reader);							//new line buffer
    
    maze->cells = malloc(maze->height*sizeof(char *));			//The following allocates mem for cells array
    for (a = 0; a < maze->height; a++) {
        maze->cells[a] = malloc(maze->width*sizeof(char));
    }
    
    
    int z, x;						//The following fills in cells and finds start and end
    for(z=0; z < maze->height; z++) {
      for(x=0; x < maze->width; x++) {
        fscanf(reader, "%c", &(maze->cells[z][x]));
	  if (maze->cells[z][x] == 'S') {		//finds start of maze
              maze->startRow = z;
              maze->startColumn = x;
          }
          if (maze->cells[z][x] == 'E') {		//finds end of maze
              maze->endRow = z;
              maze->endColumn = x;
          }

      }
        fgetc(reader);		//new line buffer
    }



    fclose(reader);		//closes file
    
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int q;
    
    for (q = 0; q < maze->height; q++) {	//frees the mem of the cells rows first
        free(maze->cells[q]);
    }
    free(maze->cells);		//frees mem of cells cols
    free(maze);		//frees mem of maze_t
    
  
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    
    int i,j;
    
//The following prints the maze cell by cell using nested for loops

    for (i = 0; i<maze->height; i++) {
        for (j = 0; j<maze->width; j++) {
            printf("%c", maze->cells[i][j]);
        }
        printf("\n");	//print newline before going to next line
    }
    

}

/*
 * solveMazeDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{

    
    
    if (col < 0 || col >= maze->width || row < 0 || row >= maze->height) {    //Step 1 - Checks if in bounds
        return 0;
    }

    if (row == maze->endRow && col == maze->endColumn) {  	//Step 3 - Checks if at end
	maze->cells[maze->startRow][maze->startColumn] = 'S';	//Replaces the start as needed
        return 1;
    }
    if ((maze->cells[row][col] != ' ') && (maze->cells[row][col] != 'S')) { 	//Step 2 - Checks if valid cell
        return 0;
    }

    maze->cells[row][col] = '*'; 		   //Step 4 - Marks as solution
    
    if (solveMazeDFS(maze, col+1, row) == 1) {     //Step 5 - Moves Right
        return 1;
    }
    if (solveMazeDFS(maze, col-1, row) == 1) {     //Step 6 - Moves Left
        return 1;
    }
    if (solveMazeDFS(maze, col, row-1) == 1) {     //Step 7 - Moves Up
        return 1;
    }
    if (solveMazeDFS(maze, col, row+1) == 1) {     //Step 8 - Moves Down
        return 1;
    }
    
    maze->cells[row][col] = '~'; 		   //Step 9 - Marks as visited
    
    return 0;        //Step 10 - Maze unsolvable
    
}
