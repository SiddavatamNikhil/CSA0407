#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a new process (launch notepad as an example)
    if (!CreateProcess(
            NULL,
            "C:\\Windows\\System32\\notepad.exe",
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    printf("Parent Process:\n");
    printf("Process ID: %lu\n", GetCurrentProcessId());
    printf("Parent Process ID: Not directly available in Windows.\n");

    printf("Child Process:\n");
    printf("Process ID: %lu\n", pi.dwProcessId);
    printf("Thread ID: %lu\n", pi.dwThreadId);

    // Wait for child process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
