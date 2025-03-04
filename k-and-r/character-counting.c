#include <stdio.h>

/* count characters in input */
int main()
{
	double char_count = 0;
	while (getchar() != EOF)
		++char_count;
	printf("%ld\n", char_count);
}
