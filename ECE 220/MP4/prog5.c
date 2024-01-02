/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 
 Noah DuVal
 663669152
 
 In this program we are comleteing a few parts to a game that requires you to guess the combination
 of a randomly generated 4 number sequence with values between 1-8. The player has up to 12 guesses to figure out the combination.
 When the player makes a guess they are told how many perfect matches and how many misplaced matches their guess
 contains.
 
 When it came to writing the program I started with the first function where I used sscanf to find the input of the seed number
 and then used srand to generate a random seed. After that the second function is where that was used to create the random number sequence
 used for the solution of the combination. the final function is where a majority of the work was done as there is first steps to
 see if the guess was valid and then to check for perfect matches, then lastly checks for misplaced matches.

*/

#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */

int
set_seed (const char seed_str[])
{

int seed;
int count;
char post[2];
count = sscanf (seed_str, "%d %1s", &seed, post);   //places the integer in "seed" and extra in "post" and stores the return value in count

if( count == 1 )    //Checks that it was only an integer that entered
{
	srand(seed);    //Initilizes # generator
	return 1;
}
else
{
    printf("set_seed: invalid seed\n"); //Seed entry was invalid thus prints invalid statement
	return 0;
}

}

/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */

void
start_game (int* one, int* two, int* three, int* four)
{

solution1 = rand()%8 + 1;   //The following create the random numbers for the solution (1-8)
solution2 = rand()%8 + 1;
solution3 = rand()%8 + 1;
solution4 = rand()%8 + 1;

*one = solution1;       //The following stores the solutions at the pointers
*two = solution2;
*three = solution3;
*four = solution4;

guess_number = 1;       //Initializes the guess count

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format

 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"

 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */

int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{

int w, x, y, z;
int cnt;
char garb[2];

cnt = 0;


cnt = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, garb);  //scans guess for integers and extra stores in w,x,y,z and extra in garb with return value in cnt

if ( cnt != 4 )     //checks that the input was only 4 integers
{
	printf("make_guess: invalid guess\n");
	return 0 ;                                  //returns 0 to say expresion was invalid
}
    
//The following sequence checks that the 4 values entered are within the range of 1-8 (valid)

if ( 1 > w || w > 8 )
{
	printf("make_guess: invalid guess\n");
	return 0 ;
}		

if ( 1 > x || x > 8 )
{
	printf("make_guess: invalid guess\n");
	return 0;
}		

if ( 1 > y || y > 8 )
{
	printf("make_guess: invalid guess\n");
	return 0;
}		

if ( 1 > z || z > 8 )
{
	printf("make_guess: invalid guess\n");
	return 0;
}		

// Expression is now valid

*one = w;       //following four lines store guess values in the pointers
*two = x;
*three = y;
*four = z;

int perfect;
int misplaced;
int s1, s2, s3, s4;
int ww, xx, yy, zz;

s1 = solution1;     //stores solution values so they can be changed and then restored later
s2 = solution2;
s3 = solution3;
s4 = solution4;

ww = w;     //stores guess values so they can be changed and then restored later
xx = x;
yy = y;
zz = z;

perfect = 0;        //initializes the following variables
misplaced = 0;

//starts to check for perfect matches first

if ( w == solution1 )
{
	perfect += 1;       //increments perfect count
	solution1 = 9;      //changes value so it is not recounted
	w = 0;              //changes valuse so it is not recounted
}
                        //the following three if statments follow the same idea
if ( x == solution2 )
{
	perfect += 1;
	solution2 = 9;
	x = 0;	
}

if ( y == solution3 )
{
	perfect += 1;
	solution3 = 9;	
	y = 0;
}

if ( z == solution4 )
{
	perfect += 1;	
	solution4 = 9;
	z = 0;
}


//starts to check misplaced matches by trying to match the guess values to the other solutions values

if ( w == solution2 )
{
	misplaced += 1;         //increments misplaced count
	solution2 = 9;          //changes value so that it not recounted
}

else if ( w == solution3 )
{
	misplaced += 1;
	solution3 = 9;
}

else if ( w == solution4 )
{
	misplaced += 1;
	solution4 = 9;
}

// moves on to second guess
//checks second guess against all other solutions


if ( x == solution1 )
{
	misplaced += 1;         //increments misplaced count
	solution1 = 9;          //changes value so that it not recounted
}

else if ( x == solution3 )
{
	misplaced += 1;
	solution3 = 9;
}

else if ( x == solution4 )
{
	misplaced += 1;
	solution4 = 9;
}

// moves on to third guess



if ( y == solution2 )
{
	misplaced += 1;
	solution2 = 9;
}

else if ( y == solution1 )
{
	misplaced += 1;
	solution1 = 9;
}

else if ( y == solution4 )
{
	misplaced += 1;
	solution4 = 9;
}

// moves onto fourth guess



if ( z == solution2 )
{
	misplaced += 1;
	solution2 = 9;
}

else if ( z == solution3 )
{
	misplaced += 1;
	solution3 = 9;
}

else if ( z == solution1 )
{
	misplaced += 1;
	solution1 = 9;
}

//done matching

solution1 = s1;     //restores the following values for the next guess
solution2 = s2;
solution3 = s3;
solution4 = s4;

w = ww;     //restores the following values for the next guess
x = xx;
y = yy;
z = zz;


printf( "With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced); //prints how well your guess was

guess_number += 1;      //increments guess number

return 1;   //returns the value of one showing expressison was valid
    
}


