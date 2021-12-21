/* Test a command line program with input file and arguments.
 * Copyright Nick "nupa" Lamicela, 2021.
 * 
 * 'test' takes a test file over stdin, Each line in the input should
 * be blank, or start with one of the symbols -, $, <, >, or #, each
 * corresponding to part of a test.
 * - indicates the title of a new test.
 * $ indicates something that should be typed on the command line.
 * > indicates something that should be passed over stdin.
 * < indicates something that should be expected in stdout.
 * # indicates a comment.
 * 
 * So, for instance:
 * 
 * - it should reverse a single line
 * $ reverse
 * > abcdefg
 * < gfedcba
 * 
 * - it should reverse multiple lines
 * $ reverse
 * > the quick brown fox jumps
 * > over the lazy dog
 * < god yzal eht revo
 * < spmuj xof nworb kciuq eht
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Gets a line from stdin if possible. Returns the length of the line,
 * including the newline char, or 0 if no line was found. 
 */
int get_line(char **out_line) {
	size_t i = 0;
	size_t buf_size = 4;
	char *buffer = malloc(buf_size);
	int c = getchar();
	if (c == EOF) return 0;

	while (1) {
		if (c == EOF) c = '\n';
		buffer[i++] = c;
		if (i >= buf_size) {
			buf_size *= 2;
			buffer = realloc(buffer, buf_size);
		}
		if (c == '\n') break;
		c = getchar();
	}
	buffer = realloc(buffer, i+1);
	buffer[i] = '\0';

	*out_line = buffer;
	return i;
}

/**
 * Extract the name of a test and save as a new string. Do not include
 * the leading dash and space or the ending newline. For example:
 * - my test name\n
 * becomes:
 * my test name
 */
int get_name(char **out_name, int line_len, char *line) {
	int offset = 1;
	while (line[offset] == ' ') offset++;

	int name_len = line_len - offset;
	char *name = malloc(name_len + 1);
	int i = 0;
	int c = line[i + offset];
	while (i < name_len && c != '\0' && c != '\n') {
		name[i++] = c;
		c = line[i + offset];
	}
	name = realloc(name, i+1);
	name[i] = '\0';

	*out_name = name;
	return i;
}

int main() {
	int line_num = 0;
	int line_len = 0;
	char *line = NULL;
	int name_len = 0;
	char *name = NULL;
	while(line_len = get_line(&line)) {
		line_num++;
		if (line[0] == '#' || line[0] == '\n') {
			/* do nothing with comments and blank lines */
		} else if (line[0] == '-') {
			if (name) free(name);
			name_len = get_name(&name, line_len, line);
			printf("Test: %s\n", name);
		} else {
			/* TODO warn about invalid line */
			printf(
				"Unexpected command '%c' on line %d.\n", 
				line[0], line_num
			);
		}

		/* TODO $ invoke command */

		/* TODO > send stdin */

		/* TODO < assert stdout */

		free(line);
	}
	if (name) free(name);
}