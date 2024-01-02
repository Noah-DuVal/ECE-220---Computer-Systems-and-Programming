/*

 Noah DuVal
 663669152
 
 In this MP we had to create three functions that would count the live neigherbors of a cell, updated the board,
 and check if the board will change in the next step. In implementing the first one I used a series of nested for loops to
 circle through the eight surounding cells. Then used a series of nested if statmentes to check in the cell was in range or
 not. More or less if the cell was an edge or corner there would be invalid cells that would not be added to the count.
 Thus, they are skipped, and then if the cell is valid the value at that cell is added to the count.
 Leaving the count with the number of live neighbors of the given cell.
 
 To implement the next function updateboard I once again used nested for loops to circulate through the board and called
 upon 'countLiveNeighbor' to check the number of live neighbors at each cell and used if statements to decide what to do
 with the cell based on the count of its live neighbors. If it was alive and had 2-3 live neighbors then it would stay
 alive and if it had more or less it would die from under or over population. Lastly, if it was a dead cell it would be
 revived if it had exactly 3 live neighbors. Then using a copy of the board to call the above funcitons and then update
 the real game board accordingly along the way that way when the for loop ends the board is all up to date.
 
 The final function just checks if the original board is the same as the board once it is updated. Thus, making a
 copy of the board and then calling the 'updateboard' function on it and comparing the copy to the original is how
 I went about it. Then using if statments to return 1 of there was no change and return 0 if the board would change
 if it updated.

*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    
    int i, j;
    int count;
    count = 0;
    
    for (i = row-1; i <= row + 1; i++) {
        for (j = col-1; j <= col + 1; j++) {
            if (i != row || j != col) {
                if (i < 0 || i > boardRowSize - 1 || j < 0 || j > boardColSize - 1 ) {   //cell is out of bound and do not add to count
                    count += 0;
                }else {            //cell is in bounds and adds value to count
                    count += board[ i * boardColSize + j ];
                }
            }
            
        }
    }
    return count;
    

}
/*
    if (col = 0) { //checks if edge on left side
        if (row = 0) { //checks if top left corner
            
        }
        else if (boardRowSize = row + 1) { //checks if bottom left corner
            
        }
        statements
    }
    
    else if (row = 0 ) { //checks if edge on top
        
    }
    
    else if (boardColSize = col + 1) { //checks if edge on right side
        
    }
    
    else if (boardRowSize = row + 1) { //checks if edge on bottom
        
    }
    
 */
    
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    
    int k, m;
    int q, w;
    int boardcopy[1 + ((boardRowSize-1)*boardColSize + (boardColSize-1));
    
    for (q = 0; q <= boardRowSize - 1; q++) {
        for (w = 0; w <= boardColSize - 1; w++) {
            boardcopy[ q * boardColSize + w ] = board[ q * boardColSize + w ];
        }
    }
    
    //boardcopy = ; //makes copy of the game board for manipulation use
    
    for (k = 0; k <= boardRowSize - 1; k++) {
        for (m = 0; m <= boardColSize - 1; m++) {
            if (boardcopy[ k * boardColSize + m ] = 1) { // Cell is alive
                if (countLiveNeighbor(board, boardRowSize, boardColSize, k, m) = (2 || 3)) {
                    board[ k * boardColSize + m ] = 1; // cell lives on
                } else {
                    board[ k * boardColSize + m ] = 0; //cell dies from under or over population
                }
                    }
            else if (boardcopy[ k * boardColSize + m ] = 0) { // cell is dead
                if (countLiveNeighbor(board, boardRowSize, boardColSize, k, m) = 3) {
                    board[ k * boardColSize + m ] = 1;   //cell is revived
                    }
                }
                    
            
        }
    }
}
    

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    
    int a,s;
    int alivecopy[1 + ((boardRowSize-1)*boardColSize + (boardColSize-1))];
    
    for (a = 0; a <= boardRowSize - 1; a++) {
        for (s = 0; a <= boardColSize - 1; s++) {
            alivecopy[ a * boardColSize + s ] = board[ a * boardColSize + s ];
        }
    }

    
    alivecopy == updateBoard(alivecopy, boardRowSize, boardColSize);
    
    if (alivecopy == board) { //check if no change
        return 1;
    } else {
        return 0; //returns 0 if there is change
    }
    
}

				
				
			

