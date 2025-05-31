#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define true 1
#define false 0
#define Nil NULL

// Konstanta untuk tombol
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

// Konstanta untuk beep
#define BEEP_ARROW_FREQ 800
#define BEEP_ARROW_DURATION 50
#define BEEP_ENTER_FREQ 1200
#define BEEP_ENTER_DURATION 100

// Konstanta untuk warna
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_YELLOW 6
#define COLOR_WHITE 7
#define COLOR_GRAY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

// Fungsi utility
HANDLE Out();
void gotoxy(int x, int y);
void clearScreen();
void hideCursor();
void setTextColor(int color);
int randNumGenerator();

// Fungsi-fungsi warna
void setColorRed();
void setColorGreen();
void setColorBlue();
void setColorYellow();
void setColorCyan();
void setColorMagenta();
void setColorWhite();
void setColorGray();
void setColorLightRed();
void setColorLightGreen();
void setColorLightBlue();
void setColorLightCyan();
void setColorLightMagenta();
void setColorLightYellow();
void setColorBrightWhite();
void setColorDefault();
void setColorHighlight();

void playArrowBeep();
void playEnterBeep();

#endif
