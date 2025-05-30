#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player createPlayer() {
	Player P;
	P.name = strdup("Player");
	P.health = MAX_PLAYER_HEALTH;
	P.energy = MAX_PLAYER_ENERGY;
	P.shield = 0;
	P.gold = 0;

	initDeck(&P.hand);
	initDiscard(&P.discard);

	return P;
}

void printPlayerStatus(Player P) {
	printf("===== Player Status =====\n");
	printf("Name   : %s\n", P.name);
	printf("HP     : %d\n", P.health);
	printf("Energy : %d\n", P.energy);
	printf("Shield : %d\n", P.shield);
	printf("Gold   : %d\n", P.gold);
	printf("=========================\n");
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

void playCard(Player *P) {
	cardAddress played = playCurrentCard(&P->hand);

	if (!played) {
		printf("No card to play.\n");
		return;
	}

	if (cardCost(played) > P->energy) {
		printf("Not enough energy to play %s.\n", cardName(played));
		addCardToDeck(&P->hand, played); // return card
		return;
	}

	useEnergy(P, cardCost(played));

	printf("Playing card: %s (%s) -> effect: %d\n",
	       cardName(played), cardType(played), cardEffect(played));

	// Simulasi efek
	if (strcmp(cardType(played), "Attack") == 0) {
		printf("Would attack enemy for %d damage\n", cardEffect(played));
	} else if (strcmp(cardType(played), "Skill") == 0) {
		P->shield += cardEffect(played);
		printf("Gained %d shield\n", cardEffect(played));
	} else if (strcmp(cardType(played), "Heal") == 0) {
		gainHP(P, cardEffect(played));
		printf("Healed for %d HP\n", cardEffect(played));
	}

	pushDiscard(&P->discard, played);
}