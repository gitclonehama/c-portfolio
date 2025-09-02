#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Assembly language functions
long gcd(long, long);

int main() 
{
	// Seed the random number generator
	srand(time(NULL));
	
	long a, b, c;

	a = 21;
	b = 55;
	c = gcd(a, b);
	printf("The gcd of %ld and %ld is %ld\n", a, b, c);

	a = 21;
	b = 77;
	c = gcd(a, b);
	printf("The gcd of %ld and %ld is %ld\n", a, b, c);

    return 0;
}