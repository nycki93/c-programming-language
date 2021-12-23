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

#include <windows.h>

#define LINE_MAX 256
#define NAME_MAX 256

/**
 * Gets from stdin until newline or EOF is encountered. Fills the buffer 
 * with as much of the line as possible. Returns the length of the line. 
 * If the return value is greater than buffer_len - 1, then the line was
 * truncated.
 */
int get_line(int buffer_len, char *buffer) {
	if (buffer_len <= 0) return 0;

	int i = 0;
	int c = getchar();
	if (c == EOF) return 0;
	buffer[i] = c;
	i++;
	
	while (c != '\n' && i + 1 < buffer_len) {
		c = getchar();
		if (c == EOF) c = '\n';
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';

	while (c != '\n') {
		c = getchar();
		if (c == EOF) c = '\n';
		i++;
	}
	return i;
}

/**
 * Copy the name of a test into the specified buffer. Do not include
 * the leading dash and space or the ending newline. For example:
 * - my test name\n
 * becomes:
 * my test name
 */
int get_name(int buffer_len, char *buffer, int line_len, char *line) {
	if (buffer_len <= 0) return 0;

	int offset = 1;
	while (line[offset] == ' ') offset++;

	int i = 0;
	int c = line[i + offset];
	while (
		c != '\0' && c != '\n' 
		&& i + offset < line_len 
		&& i + 1 < buffer_len
	) {
		buffer[i] = c;
		i++;
		c = line[i + offset];
	}
	buffer[i] = '\0';

	while (
		c != '\0' && c != '\n'
		&& i + offset < line_len
	) {
		i++;
		c = line[i + offset];
	}
	return i;
}

void warn_truncated(int line_num, int line_len) {
	printf(
		"WARNING: Truncated line %d from length %d to %d.\n",
		line_num, line_len, LINE_MAX - 1
	);
}

void err_bad_command(int line_num, char c) {
	printf("ERROR: Unknown command %c on line %d.\n", c, line_num);
}

int main() {
	int line_len = 0;
	char line[LINE_MAX];
	int name_len = 0;
	char name[NAME_MAX];
	int line_num = 0;
	while(line_len = get_line(LINE_MAX, line)) {
		line_num++;
		if (line_len > LINE_MAX - 1) {
			warn_truncated(line_num, line_len);
		}
		switch (line[0]) {
			case '#':
			case '\n':
			/* do nothing with comments and blank lines */
			break;
		
			case '-':
			name_len = get_name(NAME_MAX, name, LINE_MAX, line);
			printf("Test: %s\n", name);
			break;

			/* TODO $ invoke command */

			/* TODO > send stdin */

			/* TODO < assert stdout */

			default:
			err_bad_command(line_num, line[0]);
		}
	}
}