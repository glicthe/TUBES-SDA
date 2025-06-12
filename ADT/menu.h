#ifndef MENU_H
#define MENU_H

#include "display.h"
#include "inGameLayout.h"
#include "map_display.h"
#include "map_navigation.h"


// Struktur untuk item menu
typedef struct {
    char text[50];
    int id;
} MenuItem;

// Fungsi-fungsi menu
void displayMenu(MenuItem menu[], int menuSize, int selectedIndex);
void executeMenuAction(int menuId);
void SplashScreen();
void howToPlay();
void startGame();

#endif
