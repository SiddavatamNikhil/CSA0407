/* writer_win.c
   Compile on Windows (Dev-C++ / MinGW):
   gcc writer_win.c -o writer.exe
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024
#define MAPPING_NAME "MySharedMemory"

int main(void)
{
    HANDLE hMapFile;
    LPVOID pBuf;
    char input[BUF_SIZE];

    /* create a named file-mapping object backed by the system paging file */
    hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
                                 0, BUF_SIZE, MAPPING_NAME);
    if (hMapFile == NULL) {
        fprintf(stderr, "CreateFileMapping failed (%lu)\n", GetLastError());
        return 1;
    }

    /* map view of the file into this process address space */
    pBuf = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        fprintf(stderr, "MapViewOfFile failed (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    /* get message from user and copy into shared memory */
    printf("Enter a message to write in shared memory: ");
    if (fgets(input, BUF_SIZE, stdin) == NULL) input[0] = '\0';

    /* copy (including newline if present) */
    strncpy((char*)pBuf, input, BUF_SIZE - 1);
    ((char*)pBuf)[BUF_SIZE - 1] = '\0';

    printf("Data written in memory: %s", (char*)pBuf);
    printf("\nKeep this program running so the reader can open the shared memory.\n");
    printf("Press ENTER to unmap and exit (cleanup shared object)...\n");

    /* wait so reader can open while writer is still alive */
    getchar();

    /* cleanup */
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

