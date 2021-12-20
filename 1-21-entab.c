/* Exercise 1-21. Write a program 'entab' that replaces strings of
 * blanks by the minimum number of tabs and blanks to achieve the same
 * spacing. Use the same tab stops as for 'detab'. When either a tab
 * or a single blank would suffice to reach a tab stop, which should be
 * given preference? */

/* <nupa> In response to the open-ended part of the question, I think
 * a 1-width tab should be given priority over a lone space, but only
 * at the start of a line (implying TAB_WIDTH = 1). In all other 
 * situations, a 1-width tab should not appear.
 * 
 * Exercise for future me: Heuristically handle mixed indentation and 
 * alignment by comparing the space width to the previous line ;) */

#include <stdio.h>

#define TAB_WIDTH 8

int main() {
	int c, i;
	int col = 0;
	int pending_spaces = 0;

	while ((c = getchar()) != EOF) {
		
		if (c == '\n') {
			col = 0;
			pending_spaces = 0;
			printf("\n");
			continue;
		}

		if (c == ' ') {
			pending_spaces++;
			continue;
		}

		/* Encountered non-space character. */

		if (pending_spaces == 1 && col > 0) {
			printf(" %c", c);
			col += 2;
			pending_spaces = 0;
			continue;
		}

		while (pending_spaces >= (TAB_WIDTH - col % TAB_WIDTH)) {
			printf("\t");
			col += TAB_WIDTH;
			pending_spaces -= TAB_WIDTH;
		}

		while (pending_spaces) {
			printf(" ");
			col++;
			pending_spaces--;
		}

		printf("%c", c);
		col++;
	}
	return 0;
}
