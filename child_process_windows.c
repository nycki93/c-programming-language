#include <stdio.h>
#include <windows.h>

int main(int num_args, char** args)
{
    /* Set up pipes for child's input and output. */

    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE child_stdin_read;
    HANDLE child_stdin_write;
    CreatePipe(&child_stdin_read, &child_stdin_write, &sa, 0);
    SetHandleInformation(&child_stdin_write, HANDLE_FLAG_INHERIT, 0);

    HANDLE child_stdout_read;
    HANDLE child_stdout_write;
    CreatePipe(&child_stdout_read, &child_stdout_write, &sa, 0);
    SetHandleInformation(child_stdout_read, HANDLE_FLAG_INHERIT, 0);

    /* Start child process. */
    
    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    si.hStdOutput = child_stdout_write;
    si.hStdInput = child_stdin_read;
    si.dwFlags = STARTF_USESTDHANDLES;

    PROCESS_INFORMATION pi = {0};
    
    char* cmd = "hello";
    
    printf("Starting child process...\n");
    CreateProcess(0, cmd, 0, 0, 0, 0, 0, 0, &si, &pi);

    /* Read child's output. */
    CHAR buffer[1024];
    DWORD num_read;
    DWORD num_written;
    BOOL t = FALSE;
    HANDLE parent_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Child process's output:\n");
    while (1) {
        printf("About to read from child pipe.\n");
        t = ReadFile(child_stdout_read, buffer, 1024, &num_read, NULL);
        if (!t || num_read == 0) {
            printf("Failed to read from child pipe.\n");
            break;
        }

        t = WriteFile(parent_stdout, buffer, num_read, &num_written, NULL);
        if (!t) break;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
