#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  unsigned long int row;

  printf("Enter a row index: ");
  scanf("%lu",&row);

  // Write your code here

	unsigned long int accum = 1;
	printf("1");
	printf(" ");
	for(unsigned long int i=1; i<=row; i++){
	
	accum *= row+1-i;
	accum /= i;
	printf(("%lu"),accum);
	printf(" ");
	

}

  return 0;
}

