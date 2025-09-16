#include <windows.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    HANDLE hSource, hDest;
    DWORD bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    // Open the source file for reading
    hSource = CreateFile("source.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSource == INVALID_HANDLE_VALUE) {
        printf("Error opening source file (%d)\n", GetLastError());
        return 1;
    }

    // Create or open the destination file for writing
    hDest = CreateFile("destination.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDest == INVALID_HANDLE_VALUE) {
        printf("Error opening destination file (%d)\n", GetLastError());
        CloseHandle(hSource);
        return 1;
    }

    // Read from source and write to destination
    while (ReadFile(hSource, buffer, BUFFER_SIZE, &bytesRead, NULL) && bytesRead > 0) {
        if (!WriteFile(hDest, buffer, bytesRead, &bytesWritten, NULL)) {
            printf("Error writing to destination file (%d)\n", GetLastError());
            break;
        }
    }

    printf("File copied successfully.\n");

    // Close file handles
    CloseHandle(hSource);
    CloseHandle(hDest);

    return 0;
}
