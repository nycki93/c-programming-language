#include <stdio.h>
#include <windows.h>

int go(char* cmd, PROCESS_INFORMATION* out_pi) {
    STARTUPINFO si = {
        cb: sizeof(si)
    };
    return CreateProcess(0, cmd, 0, 0, 0, 0, 0, 0, &si, out_pi);
}

int main(int num_args, char** args)
{
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi = {0};

    char* command = "hello";

    int t = CreateProcess(0, command, 0, 0, 0, 0, 0, 0, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
