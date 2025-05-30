#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initDeck(cardDeck *D) {
    deckHead(*D) = NULL;
    deckTail(*D) = NULL;
    currentCard(*D) = NULL;
}

cardAddress createCard(const char* name, const char* type, int cost, int value) {
    cardAddress C = (cardAddress)malloc(sizeof(Card));
    if (!C) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    cardName(C) = strdup(name);
    cardType(C) = strdup(type);
    cardCost(C) = cost;
    cardEffect(C) = value;
    cardPrev(C) = NULL;
    cardNext(C) = NULL;

    return C;
}

void addCardToDeck(cardDeck *D, cardAddress C) {
    if (deckHead(*D) == NULL) {
        deckHead(*D) = deckTail(*D) = currentCard(*D) = C;
    } else {
        cardNext(deckTail(*D)) = C;
        cardPrev(C) = deckTail(*D);
        deckTail(*D) = C;
    }
}

void moveLeft(cardDeck *D) {
    if (currentCard(*D) && cardPrev(currentCard(*D))) {
        currentCard(*D) = cardPrev(currentCard(*D));
    }
}

void moveRight(cardDeck *D) {
    if (currentCard(*D) && cardNext(currentCard(*D))) {
        currentCard(*D) = cardNext(currentCard(*D));
    }
}

void printCurrentCard(cardDeck D) {
    if (currentCard(D)) {
        printf(">> Current Card <<\n");
        printf("  Name : %s\n", cardName(currentCard(D)));
        printf("  Type : %s\n", cardType(currentCard(D)));
        printf("  Cost : %d\n", cardCost(currentCard(D)));
        printf("  Effect: %d\n", cardEffect(currentCard(D)));
    } else {
        printf("No card selected.\n");
    }
}

cardAddress playCurrentCard(cardDeck *D) {
    cardAddress played = currentCard(*D);
    if (played == NULL) return NULL;

    if (cardPrev(played)) {
        cardNext(cardPrev(played)) = cardNext(played);
    } else {
        deckHead(*D) = cardNext(played);
    }

    if (cardNext(played)) {
        cardPrev(cardNext(played)) = cardPrev(played);
    } else {
        deckTail(*D) = cardPrev(played);
    }

    // Update currentCard
    currentCard(*D) = cardNext(played) ? cardNext(played) : cardPrev(played);

    cardNext(played) = NULL;
    cardPrev(played) = NULL;
    return played;
}

void printDeck(cardDeck D) {
    cardAddress temp = deckHead(D);
    int i = 1;
    while (temp) {
        printf("Card %d: %s (%s), Cost: %d, Effect: %d\n", i++, cardName(temp), cardType(temp), cardCost(temp), cardEffect(temp));
        temp = cardNext(temp);
    }
}

void freeCard(cardAddress C) {
    if (C) {
        if (cardName(C)) free(cardName(C));
        if (cardType(C)) free(cardType(C));
        free(C);
    }
}

void initDiscard(discardPile *P) {
    topDiscard(*P) = NULL;
}

void pushDiscard(discardPile *P, cardAddress C) {
    discardPtr node = (discardPtr)malloc(sizeof(discardNode));
    node->card = C;
    node->next = topDiscard(*P);
    topDiscard(*P) = node;
}

cardAddress popDiscard(discardPile *P) {
    if (topDiscard(*P) == NULL) return NULL;

    discardPtr temp = topDiscard(*P);
    cardAddress C = temp->card;
    topDiscard(*P) = temp->next;
    free(temp);
    return C;
}

void printDiscard(discardPile P) {
    printf("Discard Pile:\n");
    discardPtr temp = topDiscard(P);
    int i = 1;
    while (temp) {
        printf("  %d: %s (%s)\n", i++, cardName(temp->card), cardType(temp->card));
        temp = temp->next;
    }
}