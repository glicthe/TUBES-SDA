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
    cardUpgrade(C) = false;
    cardPrev(C) = NULL;
    cardNext(C) = NULL;

    return C;
}

void starterDeckInventory(cardDeck *D){
	int Num = 0;
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
			cardAddress addCard = createCard("SuperSlash", "Attack", 3, 14);
			addCardToDeck(D, addCard);
		}
		Num++;
	}
}

void initDeckInventoryToHand(cardDeck *inventory, cardDeck *hand, int drawAmount) {
    int i, num, min, max, drawDeck, count;
    
    cardAddress temp = (*hand).current;
    
    int countInv = countDeck(*inventory);
    if (countInv == 0) {
    	return;
	}
    int countHand = countDeck(*hand);
    if (drawAmount > 0) {
        drawDeck = drawAmount;  
    } else {
        drawDeck = 5 - countHand;  
    }
	
    min = 0;
    max = countInv - 1;
    int *used = (int*)calloc(countInv, sizeof(int));
    count = 0;
	while (count < drawDeck) {
        num = rand() % (max - min + 1) + min;
        
        if (currentCard(*inventory) == Nil) break;
        
        if (used[num] == 0) {
            used[num] = 1; 
            
           	currentCard(*inventory) = deckHead(*inventory);

            for (i = 0; i < num; i++) {
                if (cardNext(currentCard(*inventory)) != NULL) {
                    currentCard(*inventory) = cardNext(currentCard(*inventory));
                }
            }
            
            cardAddress movedCard = playCurrentCard(inventory);
            if (movedCard) {
                addCardToDeck(hand, movedCard);
                count++;
			}
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
    } else if (cardPrev(currentCard(*D)) == Nil) moveToTail(D);	
}

void moveRight(cardDeck *D) {
    if (currentCard(*D) && cardNext(currentCard(*D))) {
        currentCard(*D) = cardNext(currentCard(*D));
    } else if (cardNext(currentCard(*D)) == Nil) moveToHead(D);
}

void moveToHead(cardDeck *D) {
    if (currentCard(*D) && deckHead(*D)) {
        currentCard(*D) = deckHead(*D);
    }
}

void moveToTail(cardDeck *D) {
    if (currentCard(*D) && deckTail(*D)){
        currentCard(*D) = deckTail(*D);
    }
}


void printCurrentCard(cardDeck D, int startCol, int startRow) {
    int i = 23; 
	if (currentCard(D)) {
    	
		gotoxy(startCol, startRow + i); i++;
    	setColorLightCyan();
        printf("=======[Current Card]=======\n");
    	
		gotoxy(startCol, startRow + i); i++;
	    setColorDefault();
		printf("+---------------------------+");
		
		gotoxy(startCol, startRow + i); i++;
        void setColorMagenta();
		printf("	Card	[%s]", cardName(currentCard(D)));
        
        gotoxy(startCol, startRow + i); i++;
	    setColorDefault();
		printf("+---------------------------+");
        
    	gotoxy(startCol, startRow + i); i++;
    	setColorLightGreen();
		printf("	Type	[%s]", cardType(currentCard(D)));
    	
    	gotoxy(startCol, startRow + i); i++;
	    setColorDefault();
		printf("+---------------------------+");
		
    	gotoxy(startCol, startRow + i); i++;
    	setColorYellow();
        printf("	Cost	[%d]", cardCost(currentCard(D)));
    	
		gotoxy(startCol, startRow + i); i++;
	    setColorDefault();
		printf("+---------------------------+");
		
		gotoxy(startCol, startRow + i); i++;
        setColorLightMagenta();
		printf("	Effect	[%d]", cardEffect(currentCard(D)));
        
        gotoxy(startCol, startRow + i); i++;
	    setColorDefault();
		printf("+---------------------------+");
    } else {    	
    	gotoxy(startCol, startRow + 28);
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

void printDeck(cardDeck D, int startCol, int startRow) {
    cardAddress temp = deckHead(D);
    int boxTopBot = 16;
    int boxLeftRight = 11;
    char name[10];
    int i, j, countCard, startColReset;
    if (countDeck(D) > 5){
    	startCol -= 21;
	} 
    startColReset = startCol;
    while (temp != Nil) {
        i = 1;
        if (countCard == 7) {
			startCol = startColReset;
			startRow += 13;
			 
		}
    	gotoxy(startCol, startRow);
    	if (temp == currentCard(D)) setColorBlue();
		else setColorBrightWhite(); 
		for(i = 0; i <= boxTopBot; i++) printf("=");
		for(i = 1; i <= boxLeftRight; i++) {
			gotoxy(startCol, startRow + i);
			printf("||");
			gotoxy(startCol + boxTopBot -1, startRow + i);
			printf("||");
		}
		gotoxy(startCol, startRow + boxLeftRight);
		for(i = 0; i <= boxTopBot; i++) printf("=");
		
		gotoxy(startCol, startRow);
		setColorYellow();
		printf("[%d]", cardCost(temp));
		i = 3;
		if (strcmp(cardName(temp), "PowerSlash") == 0){
			setColorLightRed();
			gotoxy(startCol + 5, startRow + i); i++;
			printf("   ^\n");
			gotoxy(startCol + 5, startRow + i); i++;
			printf("   |\n");
			gotoxy(startCol + 5, startRow + i); i++;
			printf("._<O>_.\n");
			gotoxy(startCol + 5, startRow + i); i++; i++;
			printf("   I\n");
		} else if (strcmp(cardName(temp), "SuperSlash") == 0){
			setColorLightRed();
			gotoxy(startCol + 5, startRow + i); i++;
			printf("   ^\n");
			gotoxy(startCol + 5, startRow + i); i++;
			printf("   |\n");
			gotoxy(startCol + 5, startRow + i); i++;
			printf("._)*(_.\n");
			gotoxy(startCol + 5, startRow + i); i++; i++;
			printf("  `I`\n");
		} else if (strcmp(cardName(temp), "Insight") == 0){
			setColorLightYellow();
			gotoxy(startCol + 5, startRow + i); i++;
			printf("\\  |  /\n");
			gotoxy(startCol + 5, startRow + i); i++;
			printf(" '.'.'\n");
			gotoxy(startCol + 5, startRow + i); i++;
			printf("~`(O)`~\n");
			gotoxy(startCol + 5, startRow + i); i++; i++;
			printf(" `-~-`\n");
		} else if (strcmp(cardName(temp), "IronWall") == 0) {
			setColorLightBlue();
			gotoxy(startCol + 2, startRow + i); i++;
			printf("     /+\\\n");
			gotoxy(startCol + 2, startRow + i); i++;
			printf("   _/_|_\\_\n");
			gotoxy(startCol + 2, startRow + i); i++;
			printf(" _/_\\_|_/_\\_\n");
			gotoxy(startCol + 2, startRow + i); i++; i++;
			printf("/_\\_\\_|_/_/_\\\n");
		} else if (strcmp(cardType(temp), "Attack") == 0){
	    	setColorLightRed();
			gotoxy(startCol + 6, startRow + i); i++;
			printf("  ^  ");
			gotoxy(startCol + 6, startRow + i); i++;
			printf("  |  ");
			gotoxy(startCol + 6, startRow + i); i++;
	    	printf("._|_.");
	    	gotoxy(startCol + 6, startRow + i); i++; i++;
	    	printf("  I  ");
		} else if (strcmp(cardType(temp), "Shield") == 0){
			setColorLightBlue();
			gotoxy(startCol + 6, startRow + i); i++;
			printf("<--->");
			gotoxy(startCol + 6, startRow + i); i++;
		    printf("|_|_|");
			gotoxy(startCol + 6, startRow + i); i++;
		    printf("|_|_|");
	    	gotoxy(startCol + 6, startRow + i); i++; i++;
		    printf("\\|_|/");
		} else if (strcmp(cardType(temp), "Draw") == 0){
			setColorLightYellow();
			gotoxy(startCol + 3, startRow + i); i++;
			printf("  .-<<<-.\n");
			gotoxy(startCol + 3, startRow + i); i++;
			printf(" /       \\\n");
			gotoxy(startCol + 3, startRow + i); i++;
			printf(" \\       /\n");
			gotoxy(startCol + 3, startRow + i); i++; i++;
			printf("  `->>>-`\n");
		} 
		        int nameX_offset;
		if (strcmp(cardName(temp), "Insight") == 0) {
			nameX_offset = 5;
		} else {
			nameX_offset = 6;
		}
		
		gotoxy(startCol + nameX_offset, startRow + i); i++;
        if (strlen(cardName(temp)) > 5){
            strcpy(name, cardName(temp));
            j = 0;
            
            while(j < strlen(name) && j < 10) {
                if (j > 0 && isupper(name[j])) {
                    gotoxy(startCol + nameX_offset, startRow + i); 
                    i++;
                }
                printf("%c", name[j]);
                j++;
            }
        } else {
            printf("%s", cardName(temp));
        }
        gotoxy(startCol + boxTopBot - 2, startRow + boxLeftRight);
        setColorRed();
        printf("[%d]", cardEffect(temp));
        setColorBrightWhite();
        startCol += (boxTopBot + 5);
        countCard++;
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

void initDiscardToInventory(discardPile *P, cardDeck *D){
	discardPtr temp = topDiscard(*P);
	while (temp != Nil){
		cardAddress current = popDiscard(P);
		addCardToDeck(D, current);
		temp = topDiscard(*P);
	}
}

void printDiscard(discardPile P) {
    discardPtr temp = topDiscard(P);
    int i = 1;
    while (temp) {
        printf("  %d: %s (%s)\n", i++, cardName(temp->card), cardType(temp->card));
        temp = temp->next;
    }
}

void printDrawIcon() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = 7;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 17;
	gotoxy(startCol, startRows++); printf("%s                .:==.          ", RESET);
	gotoxy(startCol, startRows++); printf("        :++++-.  .. =-         ");
	gotoxy(startCol, startRows++); printf("   :==:..-=:...  ---.=-        ");
	gotoxy(startCol, startRows++); printf("-=-.:-=.   -####:    :.=:      ");
	gotoxy(startCol, startRows++); printf("+==-.-..   .*####-.   : +      ");
	gotoxy(startCol, startRows++); printf("==--..-     .#####:    :.+     ");    
	gotoxy(startCol, startRows++); printf("  +==-.-.     +#####:   ..:+   ");
	gotoxy(startCol, startRows++); printf("  :+-=: :.    .######.   .:=-  ");
	gotoxy(startCol, startRows++); printf("    +===..+.    :###*:. .=:..+ ");
	gotoxy(startCol, startRows++); printf("     =-==..:+-...:-::...=*##*- ");
	gotoxy(startCol, startRows++); printf("      -+-=-=*##########*+=-    ");
	gotoxy(startCol, startRows++); printf("       -=-+######*+++.         ");
	gotoxy(startCol, startRows++); printf("        ++*+++-                ");
} 

void printDiscardIcon() { // Size (32 , 14)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 38;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 17;
	gotoxy(startCol, startRows++); printf("%s           -++=:               ", RESET);
	gotoxy(startCol, startRows++); printf("         *+=====+*****-        ");
	gotoxy(startCol, startRows++); printf("        +++=---=#####*==+*+=   ");
	gotoxy(startCol, startRows++); printf("      ++=*---==**=------==+=##-");
	gotoxy(startCol, startRows++); printf("    -*=*--=@@@@@@@@@#+=-#=####=");
	gotoxy(startCol, startRows++); printf("   .*++=--=@@#+=*#@@@##+=*###+ ");
	gotoxy(startCol, startRows++); printf("  ++*=-=------==#=#@@@++###*:  ");
	gotoxy(startCol, startRows++); printf(" =*+##==-----====*#@@#=####=   ");
	gotoxy(startCol, startRows++); printf(".*==#@@#####@@@#@#+=#=####+    ");   
	gotoxy(startCol, startRows++); printf(" :##########*+==+**=*###*:     ");
	gotoxy(startCol, startRows++); printf("   .+**################*-      ");
	gotoxy(startCol, startRows++); printf("         =***#########*=       ");
	gotoxy(startCol, startRows++); printf("              .-+***##=        ");
}
