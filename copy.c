#include <stdio.h>

/* copy input to output; 2nd version */
int main()
{
	int c;
	int b;
	while ((c = getchar()) != EOF) {
		putchar(c);
	}
		
	printf("EOF is %d", EOF);
}
