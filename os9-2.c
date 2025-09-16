/* reader_win.c
   Compile on Windows (Dev-C++ / MinGW):
   gcc reader_win.c -o reader.exe
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define MAPPING_NAME "MySharedMemory"

int main(void)
{
    HANDLE hMapFile;
    LPVOID pBuf;

    /* open the existing named mapping (writer must have created it and still running) */
    hMapFile = OpenFileMappingA(FILE_MAP_READ, FALSE, MAPPING_NAME);
    if (hMapFile == NULL) {
        fprintf(stderr, "OpenFileMapping failed (%lu). Make sure writer is running.\n", GetLastError());
        return 1;
    }

    /* map view for read */
    pBuf = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        fprintf(stderr, "MapViewOfFile (reader) failed (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    /* read and print */
    printf("Data read from memory: %s", (char*)pBuf);

    /* cleanup */
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

