/* 
    Here is a loop from the input function getline that we wrote in 
    chapter 1:
      
        for (i=0; i < lim-1 & (c=getchar()) != '\n' & c != EOF; ++i)
            s[i] = c;
    
    Write a loop equivalent to the `for` loop above without using &&
    or ||.
*/
#include <stdio.h>

#define MAXLINE 1024

int my_getline(char line[], int maxline);

int main() {
    int len = -1;
    char line[MAXLINE];
    while (len != 0) {
        len = my_getline(line, MAXLINE);
        printf("%s", line);
    }
    return 0;
}

int my_getline(char s[], int lim) 
{
    int c, i;
    for (i = 0; i < lim-1; ++i) {
        c = getchar();
        if (c == EOF) break;
        s[i] = c;
        if (c == '\n') break;
    }
    s[i] == '\0';
    return i;
}
