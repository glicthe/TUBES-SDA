#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdint.h>

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

// Fungsi Generate Map
#define D4_PATTERN_SIZE 17
#define PROB_ENEMY_COMMON 65
#define PROB_REST_NODE 85
#define MAP_MAX_DEPTH 6
#define START_NODE_CHILDREN 3

// Fungsi untuk posisi Node
#define NODE_DISPLAY_WIDTH_L 15  // Lebar tampilan node level 1
#define NODE_DISPLAY_WIDTH_M 12  // Lebar tampilan node level 2
#define MAP_START_X 0            // Posisi X awal untuk menggambar peta
#define MAP_START_Y 2            // Posisi Y awal untuk menggambar peta
#define MAX_CHILDREN_DISPLAY 4   // Batasan anak yang bisa ditampilkan dalam satu baris untuk kasus tertentu
#define MAX_GRANDCHILDREN_DISPLAY 8 // Batasan cucu yang bisa ditampilkan

#define MAP_START_X_ALGO 5      // Posisi X paling kiri untuk peta baru
#define MAP_START_Y_ALGO 5      // Posisi Y awal untuk peta baru
#define HORIZONTAL_SPACING 25   // Jarak horizontal antar level/depth
#define VERTICAL_SPACING 6      // Jarak vertikal antar node bersaudara

#define RESET "\033[0m"
#define RED "\033[0;31;40m"
#define BLUE "\033[0;34;40m"
#define CYAN "\033[0;36;40m"

// Fungsi utility
HANDLE Out();
void gotoxy(int x, int y);
void clearScreen();
void hideCursor();
void showCursor();
void setTextColor(int color);
int randNumGenerator();
int generateRandomRange(int min, int max);

// Fungsi untuk mengatur warna
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
void setColorHighlight_Map();

// Fungsi untuk efek suara
void playArrowBeep();
void playEnterBeep();

#endif
