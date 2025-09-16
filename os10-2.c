/* writer.c - Named Pipe "message queue" sender (Windows) */
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PIPE_NAME "\\\\.\\pipe\\MsgQueuePipe"
#define BUF_SIZE 512

int main(void) {
    HANDLE hPipe;
    char buffer[BUF_SIZE];
    DWORD bytesWritten;

    printf("Writer: Enter message: ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    /* remove newline */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';

    /* Try to open the pipe; wait if busy */
    while (1) {
        hPipe = CreateFileA(
            PIPE_NAME,
            GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );
        if (hPipe != INVALID_HANDLE_VALUE) break;

        if (GetLastError() != ERROR_PIPE_BUSY) {
            printf("Could not open pipe, error = %lu\n", GetLastError());
            return 1;
        }

        /* Wait up to 5 seconds for the server */
        if (!WaitNamedPipeA(PIPE_NAME, 5000)) {
            printf("WaitNamedPipe timed out.\n");
            return 1;
        }
    }

    if (!WriteFile(hPipe, buffer, (DWORD)strlen(buffer), &bytesWritten, NULL)) {
        printf("WriteFile failed, error = %lu\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Writer: Message sent successfully: %s\n", buffer);
    CloseHandle(hPipe);
    return 0;
}

