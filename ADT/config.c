#include "config.h"

HANDLE Out()
{
    return (GetStdHandle(STD_OUTPUT_HANDLE));
}

void gotoxy(int x, int y) 
{
    COORD Point;
    Point.X = x;
    Point.Y = y;
    SetConsoleCursorPosition(Out(), Point);
}

void clearScreen() {
    //system("cls");
    printf("\033[H\033[J");
    fflush(stdout);
}


void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void showCursor(void) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int randNumGenerator(){
	int min = 1, max = 10;
	
	int value = rand() % (max - min  + 1) + min;
	return value;
}

int generateRandomRange(int min, int max) {
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }
    int value = rand() % (max - min + 1) + min;
    return value;
}

boolean g_isGameActive;

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// Implementasi fungsi-fungsi warna
void setColorRed() {
    setTextColor(COLOR_RED);
}

void setColorGreen() {
    setTextColor(COLOR_GREEN);
}

void setColorBlue() {
    setTextColor(COLOR_BLUE);
}

void setColorYellow() {
    setTextColor(COLOR_YELLOW);
}

void setColorCyan() {
    setTextColor(COLOR_CYAN);
}

void setColorMagenta() {
    setTextColor(COLOR_MAGENTA);
}

void setColorWhite() {
    setTextColor(COLOR_WHITE);
}

void setColorGray() {
    setTextColor(COLOR_GRAY);
}

void setColorLightRed() {
    setTextColor(COLOR_LIGHT_RED);
}

void setColorLightGreen() {
    setTextColor(COLOR_LIGHT_GREEN);
}

void setColorLightBlue() {
    setTextColor(COLOR_LIGHT_BLUE);
}

void setColorLightCyan() {
    setTextColor(COLOR_LIGHT_CYAN);
}

void setColorLightMagenta() {
    setTextColor(COLOR_LIGHT_MAGENTA);
}

void setColorLightYellow() {
    setTextColor(COLOR_LIGHT_YELLOW);
}

void setColorBrightWhite() {
    setTextColor(COLOR_BRIGHT_WHITE);
}

void setColorDefault() {
    setTextColor(COLOR_WHITE);
}

void setColorHighlight() {
    setTextColor(112); // Background putih, teks hitam
}

void setColorHighlight_Map() {
    setTextColor(78); // Background putih, teks hitam
}

void playArrowBeep() {
    Beep(BEEP_ARROW_FREQ, BEEP_ARROW_DURATION);
}

void playEnterBeep() {
    Beep(BEEP_ENTER_FREQ, BEEP_ENTER_DURATION);
}
