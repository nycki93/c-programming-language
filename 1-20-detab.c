/* Exercise 1-20. Write a program 'detab' that replaces tabs in the 
 * input with the proper number of blanks to space to the next tab 
 * stop. Assume a fixed set of tab stops, say every n columns. Should n 
 * be a variable or a symbolic parameter? */

#include <stdio.h>

#define TAB_WIDTH 8

/* output modes */
#define MODE_DEFAULT 0
#define MODE_PADDING 1

int main()
{
	int col = 0;
	int c = getchar();
	int mode = MODE_DEFAULT; 
	while (1) {
		if (c == EOF) return 0;

		if (mode == MODE_DEFAULT && c == '\t') {
			printf(" ");
			col += 1;
			mode = MODE_PADDING;
			continue;
		}

		if (mode == MODE_DEFAULT && c == '\n') {
			printf("\n");
			col = 0;
			c = getchar();
			continue;
		}

		if (mode == MODE_DEFAULT) {
			printf("%c", c);
			col += 1;
			c = getchar();
			continue;
		}

		if (mode == MODE_PADDING && col % TAB_WIDTH == 0) {
			mode = MODE_DEFAULT;
			c = getchar();
			continue;
		}

		if (mode == MODE_PADDING) {
			printf(" ");
			col += 1;
			continue;
		}

		printf("[Unknown mode: %d]", mode);
		return 1;
	}
}
