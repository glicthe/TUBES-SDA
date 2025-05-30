#include "card.h"

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

void starterDeckInventory(cardDeck *D){
	int Num;
	while (Num < 10){
		if (Num <= 3) {
			cardAddress addCard = createCard("Slash", "Attack", 1, 4);
			addCardToDeck(D, addCard);
		} else if (Num >= 4 && Num <= 6) {
			cardAddress addCard = createCard("Block", "Shield", 1, 5);
			addCardToDeck(D, addCard);
		} else if (Num == 7) {
			cardAddress addCard = createCard("Draw", "Draw", 2, 3);
			addCardToDeck(D, addCard);
		} else {
			cardAddress addCard = createCard("SuperSlash", "SpecialAttack", 3, 9);
			addCardToDeck(D, addCard);
		}
		Num++;
	}
}

void initDeckInventoryToHand(cardDeck inventory, cardDeck *hand) {
    int i, num, min, max, count = 0;
    
    int countInv = countDeck(inventory);
    if (countInv < 5) {
        printf("Error: Inventory must have at least 5 cards.\n");
        return;
    }

    min = 0;
    max = countInv - 1;
    int *used = (int*)calloc(countInv, sizeof(int));
    while (count < 5) {
        num = rand() % (max - min + 1) + min;
        
        if (used[num] == 0) {
            used[num] = 1; 
            printf("%d ", num);
            cardAddress selectedCard = deckHead(inventory);

            for (i = 0; i < num; i++) {
                selectedCard = cardNext(selectedCard); 
            }
            
            // Create a copy of the selected card to avoid modifying the original inventory
            cardAddress moveCopyCard = createCard(cardName(selectedCard), cardType(selectedCard), cardCost(selectedCard), cardEffect(selectedCard));
            addCardToDeck(hand, moveCopyCard);
            count++;            
        }
    }
    free(used);
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

int countDeck(cardDeck D){
	int count = 0;
    cardAddress P;
	if (deckHead(D) != Nil){
	    P = deckHead(D);
	    for (;;) {
	        if (P == Nil){
	            break;
	        } else {
	            count++;
	            P = cardNext(P);
	        }
	    } 
	}
	return (count);
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
