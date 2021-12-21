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

int get_line(char **line) {
    size_t i = 0;
    size_t buf_size = 4;
    char *buffer = malloc(buf_size);
    int c = getchar();
    while (1) {
        if (i >= buf_size) {
            buf_size *= 2;
            buffer = realloc(buffer, buf_size);
        }
        if (c == EOF) break;
        buffer[i++] = c;
        if (c == '\n') break;
    }
    buffer[i] = '\0';
    *line = buffer;
    return i;
}

int main() {
    int line_len;
    char *line;
    while(1) {
        line_len = get_line(&line);
        printf("Received a line of length %d:\n%s", line_len, line);
    }
}