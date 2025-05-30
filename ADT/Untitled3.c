#include <windows.h>
#include <stdio.h>

void setConsoleSize(int columns, int rows) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. Set screen buffer size
    COORD bufferSize;
    bufferSize.X = columns;
    bufferSize.Y = rows;
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // 2. Set window size (should not exceed buffer size)
    SMALL_RECT windowSize = {0, 0, columns - 1, rows - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

int main() {
    int columns = 30;
    int rows = 10;

    setConsoleSize(columns, rows);

    printf("Ukuran CMD telah diubah menjadi %dx%d.\n", columns, rows);
    printf("Tekan tombol apapun untuk keluar...");
    getchar();

    return 0;
}

