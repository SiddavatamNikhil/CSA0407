/* reader.c - Named Pipe "message queue" receiver (Windows) */
#include <windows.h>
#include <stdio.h>

#define PIPE_NAME "\\\\.\\pipe\\MsgQueuePipe"
#define BUF_SIZE 512

int main(void) {
    HANDLE hPipe;
    char buffer[BUF_SIZE];
    DWORD bytesRead;

    hPipe = CreateNamedPipeA(
        PIPE_NAME,
        PIPE_ACCESS_INBOUND, /* server reads, client writes */
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,            /* max instances */
        BUF_SIZE,     /* out buffer (client->server) */
        BUF_SIZE,     /* in buffer */
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("CreateNamedPipe failed, error = %lu\n", GetLastError());
        return 1;
    }

    printf("Reader: Waiting for writer to connect...\n");

    if (!ConnectNamedPipe(hPipe, NULL) && GetLastError() != ERROR_PIPE_CONNECTED) {
        printf("ConnectNamedPipe failed, error = %lu\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Reader: Connected. Waiting for message...\n");

    if (ReadFile(hPipe, buffer, BUF_SIZE - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("Reader: Message received is: %s\n", buffer);
    } else {
        printf("Reader: ReadFile failed, error = %lu\n", GetLastError());
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    return 0;
}

