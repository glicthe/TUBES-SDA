#ifndef MENU_H
#define MENU_H

#include "display.h"
#include "inGameLayout.h"


// Struktur untuk item menu
typedef struct {
    char text[50];
    int id;
} MenuItem;

// Fungsi-fungsi menu
void displayMenu(MenuItem menu[], int menuSize, int selectedIndex);
void executeMenuAction(int menuId);
void SplashScreen();

#endif
