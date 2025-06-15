#ifndef INGAMELAYOUT_H
#define INGAMELAYOUT_H

#include "display.h"

void inGame(int startCol, int startRow, int battle, int depth);
void headBar(int startCol, int max, Player P, int turnCounter);
void battleScreen(int startCol, int startRow, int colunmns, int rows, char* state);
void showMobPlayer(Boss* boss, mobContainer C, int columns, int rows, boolean state);

// Play
void playCard(Player *P, cardDeck *Inventory, mobContainer *C, Boss* boss);
void showRewardScreen(Player *player, int depth, int type);
void printVictoryBanner();
void printRewardsClaimedBanner();
void printTreasureChest(int x, int y);
void printRewardSeparator_Top(int x, int y);
void printRewardSeparator_Bottom(int x, int y);
void printLoserBanner();
void showLoseScreen();

// Merchant
void merchantScreen(Player *player, cardDeck *inventory);
cardAddress generateRandomCard();
void printMerchant();
void skipLabel(const char* name);
void printHand(int Column, int row);
void printMerchantCard(int column, int row, Card *shopCard);

// Rest
void restScreen(Player *player, cardDeck *deck);
void campFire();
void proceedLabel();
void printRest();
void printSmith();
void highlightLeft();
void highlightRight();
void printSmithText();
void printRestText();


#endif 
