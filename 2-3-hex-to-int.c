/*
    Exercise 2-3. Write a function htoi(s), which converts a string of 
    hexidecimal digits (including an optional 0x or 0X) into its equivalent 
    integer value. The allowable digits are 0 through 9, a through f, and A
    through F.
*/

#include <stdio.h>

// 16 bits = 4 chars, plus 2 for 0x, plus 1 for \n, plus 1 for \0.
#define MAXLENGTH 8

// TODO: automatically truncate to last 16 bits instead of crashing.

int htoi(char s[]);

int main() {
    char s[MAXLENGTH];
    int i, c;
    for (i = 0; i < MAXLENGTH-1; i++) {
        c = getchar();
        if (c == EOF) break;
        s[i] = c;
        if (c == '\n') break;
    }
    s[i] = '\0';

    int result = htoi(s);
    printf("%d\n", result);
    return 0;
}

int hex_value(char c) {
    if ('0' <= c && c <= '9') {
        return c - '0';
    }
    if ('a' <= c && c <= 'f') {
        return c - 'a' + 10;
    }
    if ('A' <= c && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

int htoi(char s[]) {
    return hex_value(s[0]);
    // TODO: finish this
}