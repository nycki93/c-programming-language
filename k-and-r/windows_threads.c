#include <stdio.h>
#include <windows.h>

void thread_say(char *name) {
    printf("Hello, %s!\n", name);
}

HANDLE go(void *fn, void *arg) {
    return CreateThread(NULL, 0, fn, arg, 0, NULL);
}

int main() {
    HANDLE threads[] = {
        go(thread_say, "World!"),
        go(thread_say, "aaa"),
        go(thread_say, "bbb"),
        go(thread_say, "ccc"),
        go(thread_say, "ddd"),
        go(thread_say, "eee"),
    };
    WaitForMultipleObjects(6, threads, TRUE, INFINITE);
    return 0;
}
