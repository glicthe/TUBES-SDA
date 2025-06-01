#ifndef INGAMELAYOUT_H
#define INGAMELAYOUT_H

#include "display.h"

void inGame(int startCol, int startRow);
void headBar(int startCol, int max, Player P, int turnCounter);
void battleScreen(int startCol, int startRow, int colunmns, int rows);
void showMobPlayer(mobContainer C, int columns, int rows, boolean state);

// Play
void playCard(Player *P, cardDeck *Inventory, mobContainer *C);

#endif 
