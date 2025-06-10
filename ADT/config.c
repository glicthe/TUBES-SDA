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
    system("cls");
}

HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

void SetConsoleSettings() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    // Step 3: Resize font
    CONSOLE_FONT_INFOEX fontInfo = {0};
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    fontInfo.dwFontSize.X = 4;  // Smaller font
    fontInfo.dwFontSize.Y = 7;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hOut, FALSE, &fontInfo);


    Sleep(1000);  // Let font update propagate

    // Step 2: Resize buffer
    COORD bufferSize = {229, 75};
    SetConsoleScreenBufferSize(hOut, bufferSize);

    Sleep(1000);  // Let font update propagate
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int randNumGenerator(){
	int min = 1, max = 10;
	
	int value = rand() % (max - min  + 1) + min;
	return value;
}

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

void playArrowBeep() {
    Beep(BEEP_ARROW_FREQ, BEEP_ARROW_DURATION);
}

void playEnterBeep() {
    Beep(BEEP_ENTER_FREQ, BEEP_ENTER_DURATION);
}


