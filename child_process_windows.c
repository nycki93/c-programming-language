#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 1024

typedef struct MY_COROUTINE {
    HANDLE in;
    HANDLE out;
} MY_COROUTINE;

BOOL spawn(char* cmd, MY_COROUTINE* out_cr) {
    // Temp flag
    BOOL t = TRUE;

    // Inherit all handles except for write-to-in and read-from-out.
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE in_read;
    HANDLE in_write;
    t = t && CreatePipe(&in_read, &in_write, &sa, 0);
    t = t && SetHandleInformation(in_write, HANDLE_FLAG_INHERIT, 0);

    HANDLE out_read;
    HANDLE out_write;
    t = t && CreatePipe(&out_read, &out_write, &sa, 0);
    t = t && SetHandleInformation(out_read, HANDLE_FLAG_INHERIT, 0);

    // Failed to open pipes?
    if (!t) return FALSE; 

    PROCESS_INFORMATION pi = {0};
    STARTUPINFO si = {0};
    si.cb = sizeof(si);
    si.hStdOutput = out_write;
    si.hStdInput = in_read;
    si.dwFlags = STARTF_USESTDHANDLES;
    t = CreateProcess(0, cmd, 0, 0, 1, 0, 0, 0, &si, &pi);
    // Failed to start process?
    if (!t) return FALSE; 

    // It is possible that the process fails after starting.
    // Future improvement: can we capture that info?

    // Close all handles that we don't return.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(out_write);
    CloseHandle(in_read);

    out_cr->in = in_write;
    out_cr->out = out_read;

    return TRUE;
}

BOOL close(MY_COROUTINE* cr) {
    CloseHandle(cr->in);
    CloseHandle(cr->out);
    return TRUE;
}

int main(int num_args, char **args) 
{
    BOOL t;

    char *cmd = "cmd /c echo hello world";
    MY_COROUTINE cr = {0};
    t = spawn(cmd, &cr);
    if (!t) {
        printf("Failed to spawn coroutine.");
        return 1;
    }

    BYTE buffer[BUFFER_SIZE];
    DWORD num_read, num_written;
    HANDLE my_out = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("<child process> ");
    while (1) {
        t = ReadFile(cr.out, buffer, BUFFER_SIZE, &num_read, NULL);
        if (!t || num_read == 0) break;    
        t = WriteFile(my_out, buffer, num_read, &num_written, NULL);
        if (!t) break;
    }

    close(&cr);
    return 0;
}
