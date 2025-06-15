#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "config.h"

#define MAX_PLAYER_HEALTH 90
#define MAX_PLAYER_ENERGY 3

typedef struct Player* pPlayer;

typedef struct Player {
	char* name;
	int health;
	int energy;
	int shield;
	int gold;

	cardDeck hand;         // kartu di tangan
	discardPile discard;   // kartu yang sudah dimainkan
} Player;

// Init
Player createPlayer();
void printPlayerSprite(int startCol, int startRows);

// Status
void printPlayerStatus(Player P, int startCol, int startRow);

// Turn
void startTurn(Player *P);

// Health & Energy
void gainHP(Player *P, int amount);
void takeDamage(Player *P, int damage);
void useEnergy(Player *P, int amount);



#endif
