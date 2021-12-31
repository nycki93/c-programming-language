#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 1024

int main(int num_args, char** args)
{
    /* Temporary flag for storing pass/fail status. */
    BOOL t = TRUE;

    /* Set up input and output pipes. */

    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;

    HANDLE child_stdout_read;
    HANDLE child_stdout_write;
    t = t && CreatePipe(&child_stdout_read, &child_stdout_write, &sa, 0);
    t = t && SetHandleInformation(child_stdout_read, HANDLE_FLAG_INHERIT, 0);

    HANDLE child_stdin_read;
    HANDLE child_stdin_write;
    t = t && CreatePipe(&child_stdin_read, &child_stdin_write, &sa, 0);
    t = t && SetHandleInformation(child_stdin_write, HANDLE_FLAG_INHERIT, 0);

    if (!t) {
        printf("Failed to create pipes.\n");
        return 1;
    }

    /* Start child process. */
    
    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    si.hStdOutput = child_stdout_write;
    si.hStdInput = child_stdin_read;
    si.dwFlags = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi = {0};
    
    char* cmd = "cmd /c echo hello world";
    
    t = CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (!t) {
        printf("Failed to start process.\n");
        return 1;
    }

    /* Close unnecessary handles or else the child might not exit. */

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(child_stdout_write);
    CloseHandle(child_stdin_read);

    BYTE buffer[BUFFER_SIZE];
    DWORD num_read;
    DWORD num_written;
    HANDLE parent_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("<child process> ");
    while (1) {
        t = ReadFile(child_stdout_read, buffer, BUFFER_SIZE, &num_read, NULL);
        if (!t || num_read == 0) break;    
        t = WriteFile(parent_stdout, buffer, num_read, &num_written, NULL);
        if (!t) break;
    }

    /*  Close remaining handles to be neat and tidy. */

    CloseHandle(child_stdout_read);
    CloseHandle(child_stdin_write);

    return 0;    
}
