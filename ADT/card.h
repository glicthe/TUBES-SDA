#ifndef CARD_H
#define CARD_H

#include "config.h"


// ==========================
// Struct & Macros
// ==========================
typedef struct Card* cardAddress;
typedef struct Card {
    char* name;
    char* type;         // "Attack", "Skill", etc.
    int cost;           // Energy cost
    int effectValue;    // e.g. damage or block
    cardAddress prev;
    cardAddress next;
} Card;

#define cardName(P) (P)->name
#define cardType(P) (P)->type
#define cardCost(P) (P)->cost
#define cardEffect(P) (P)->effectValue
#define cardPrev(P) (P)->prev
#define cardNext(P) (P)->next

// ==========================
// Deck as Doubly Linked List
// ==========================
typedef struct {
    cardAddress head;
    cardAddress tail;
    cardAddress current;  // pointer ke kartu yang ditunjuk sekarang
} cardDeck;

#define deckHead(P) (P).head
#define deckTail(P) (P).tail
#define currentCard(P) (P).current

// ==========================
// Discard pile as Stack
// ==========================
typedef struct discardNode* discardPtr;
typedef struct discardNode {
    cardAddress card;
    discardPtr next;
} discardNode;

typedef struct {
    discardPtr top;
} discardPile;

#define topDiscard(P) (P).top

// ==========================
// Function Prototypes
// ==========================

// Create
void initDeck(cardDeck *D);
cardAddress createCard(const char* name, const char* type, int cost, int value);
void staterDeckInventory(cardDeck *D);
void initDeckInventoryToHand(cardDeck inventory, cardDeck *hand);

// Insert & Navigation
void addCardToDeck(cardDeck *D, cardAddress C);
void moveLeft(cardDeck *D);
void moveRight(cardDeck *D);
void printCurrentCard(cardDeck D);
void printDeck(cardDeck D);
int countDeck(cardDeck D);


// Remove (play card)
cardAddress playCurrentCard(cardDeck *D);

// Discard
void initDiscard(discardPile *P);
void pushDiscard(discardPile *P, cardAddress C);
cardAddress popDiscard(discardPile *P);
void printDiscard(discardPile P);

// Cleanup
void freeCard(cardAddress C);

#endif
