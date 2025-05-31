#include "player.h"

Player createPlayer() {
	Player P;
	P.name = strdup("Player");
	P.health = MAX_PLAYER_HEALTH;
	P.energy = MAX_PLAYER_ENERGY;
	P.shield = 0;
	P.gold = 10;

	initDeck(&P.hand);
	initDiscard(&P.discard);

	return P;
}

void printPlayerStatus(Player P, int startCol, int startRow) {
	int i;
	gotoxy(startCol, startRow - 1);
    setColorLightCyan();
	printf("=======[Player Status]=======\n");
	
	gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+---------------------------+");

	gotoxy(startCol, startRow + i); i++;
    setColorBrightWhite();
    printf("	Name	[%s]", P.name);
    	
	gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+---------------------------+");
	
	gotoxy(startCol, startRow + i); i++;
    setColorGreen();
	printf("	Health	[%d]", P.health);
	        
	gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+---------------------------+");
        
	gotoxy(startCol, startRow + i); i++;
    setColorYellow();
	printf("	Energy	[%d]", P.energy);
        
	gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+---------------------------+");
        
	gotoxy(startCol, startRow + i); i++;
    setColorGray();
	printf("	Shield	[%d]", P.shield);
        
	gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+---------------------------+");

}

void startTurn(Player *P) {
	P->energy = MAX_PLAYER_ENERGY;
}

void gainHP(Player *P, int amount) {
	P->health += amount;
	if (P->health > MAX_PLAYER_HEALTH) {
		P->health = MAX_PLAYER_HEALTH;
	}
}

void takeDamage(Player *P, int damage) {
	int realDamage = damage - P->shield;
	if (realDamage < 0) realDamage = 0;

	P->health -= realDamage;
	P->shield = 0;

	if (P->health < 0) P->health = 0;
}

void useEnergy(Player *P, int amount) {
	if (P->energy >= amount) {
		P->energy -= amount;
	} else {
		printf("Not enough energy!\n");
	}
}

void playCard(Player *P, cardDeck *Inventory) {
	cardAddress played = currentCard(P->hand);
	if (cardCost(played) > P->energy) {
		return;
	} else {
		played = playCurrentCard(&P->hand);
	
		if (!played) {
			printf("No card to play.\n");
			return;
		}
	
	
		useEnergy(P, cardCost(played));
	
		// Simulasi efek
		if (strcmp(cardType(played), "Attack") == 0) {
			printf("Would attack enemy for %d damage\n", cardEffect(played));
		} else if (strcmp(cardType(played), "Shield") == 0) {
			P->shield += cardEffect(played);
			printf("Gained %d shield\n", cardEffect(played));
		} else if (strcmp(cardType(played), "Draw") == 0) {
			initDeckInventoryToHand(Inventory, &P->hand);
			
		}
	
		pushDiscard(&P->discard, played);
	}
}
