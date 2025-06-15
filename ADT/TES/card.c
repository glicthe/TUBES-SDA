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
    	inventory = Nil;
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
    if (D->current != Nil && cardPrev(D->current) != Nil) {
        D->current = cardPrev(D->current);
    } else {
        moveToTail(D);
    }
}

void moveRight(cardDeck *D) {
    if (D->current != Nil && cardNext(D->current) != Nil) {
        D->current = cardNext(D->current);
    } else {
        moveToHead(D);
    }
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

void upgradeCard(cardDeck *D) {
	if (D->head == NULL) {
        printf("No cards to upgrade.\n");
        getch();
        return;
    }
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
		
    bool exitUpgrade = false, isUpgrade = false;
	int row = 0, column = 0;
	int count = 0, cardInDeck = countDeck(*D);
	int maxRow = (cardInDeck - 1) / 5;
	int maxCol = ((cardInDeck - 1) % 5);
    D->current = D->head;
		
    while (!exitUpgrade) {
    	clearScreen();
    	displayBorder();
    	printUpgradeText();
    	showDrawPile(*D);
    	gotoxy(columns - 10, rows + 17);
    	if (isUpgrade){
			printf("You may leave");			
		} else {
			printf("Upgrade a card");
		}
		gotoxy(columns - 10, rows + 19);
		printf("%-12s (%s) - %d\n",
        		cardName(D->current),
        		cardType(D->current),
        		cardCost(D->current)		
		);

        // Position
        setColorBlue(); printCards(column, row); setColorWhite();
        
		gotoxy(columns - 10, rows + 16);
    	if (D->current->upgrade == true) {
			printf("Upgraded");
		}
        gotoxy(columns - 10, rows + 18);
		printf("Use arrow keys to move, ENTER to Upgrade a card, ESC to exit.");
		
        int ch = getch();
        if (ch == 224) {
            ch = getch();
            switch (ch) {
				case KEY_LEFT:
				    playArrowBeep();
				    if (row == 0 && column == 0) {
				        row = maxRow;
				        column = maxCol;
				    } else if (column == 0) {
				        row--;
				        column = 4;
				        if (row == maxRow && column > maxCol) {
				            column = maxCol;
				        }
				    } else {
				        column--;
				    }
				    moveLeft(D);
				    break;
				
				case KEY_RIGHT:
				    playArrowBeep();
				    if (row == maxRow && column == maxCol) {
				        row = 0;
				        column = 0;
				    } else if (column == 4 || (row == maxRow && column == maxCol)) {
				        row++;
				        column = 0;
				    } else {
				        column++;
				        if (row == maxRow && column > maxCol) {
				            column = 0;
				            row = 0;
				        }
				    }
				    moveRight(D);
				    break;
            }
        } else if (ch == KEY_ENTER) {
        	if (!isUpgrade) {
	        	if (!D->current->upgrade) {
		        	if (strcmp(D->current->type, "Draw") == 0) {
		        		D->current->effectValue = D->current->effectValue + 1;
						D->current->cost = D->current->cost - 1;
					} else if (strcmp(D->current->type, "Attack") == 0) {
						D->current->effectValue = D->current->effectValue + 16;
						D->current->cost = D->current->cost - 1;
					} else if (strcmp(D->current->type, "Shield") == 0) {
						D->current->effectValue = D->current->effectValue + 16;
					}
				    char* newName = malloc(strlen(D->current->name) + 2);
				    if (newName == NULL) {
				        printf("Memory allocation failed.\n");
				        return;
				    }
				    strcpy(newName, D->current->name);
				    strcat(newName, "+");
				    free(D->current->name);
				    D->current->name = newName;
		        	
					D->current->upgrade = true;
		        	isUpgrade = true;
		    	} else {
				    gotoxy(columns - 10, rows + 20);
				    setColorRed();
				    printf("Already upgraded!");
				    setColorWhite();
				    getch();
				}
			}
        } else if (ch == KEY_ESC) {
            exitUpgrade = true;
        }
    }
}

void restartCard(cardDeck *D, cardDeck *H, discardPile *P) {
    cardAddress current = D->head;
    while (current != NULL) {
        cardAddress next = cardNext(current);
        pushDiscard(P, current);
        current = next;
    }
    D->head = NULL;
    D->tail = NULL;
    D->current = NULL;

    current = H->head;
    while (current != NULL) {
        cardAddress next = cardNext(current);
        pushDiscard(P, current);
        current = next;
    }
    H->head = NULL;
    H->tail = NULL;
    H->current = NULL;
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

void showDiscardPile(discardPile discard) {
	clearScreen();
	displayBorder();
	printDiscardText();	
	gotoxy(0, 0);
		
	int count = 0;
	discardPtr current = topDiscard(discard);
	if (topDiscard(discard) != Nil) { //Check if discard is not empty
		count++;
	    while (cardNext(current) != Nil) { // Check if there is next card and repeat this loop
			current = cardNext(current);
	        count++;				
	    } 
		printAllCards(count);  
	}    
		
	count = 0;
	current = topDiscard(discard);
	if (topDiscard(discard) != Nil) { //Check if discard is not empty
		displayCardIcon(current->card, count); 
		count++;
	    while (cardNext(current) != Nil) { // Check if there is next card and repeat this loop
			current = cardNext(current);
			displayCardIcon(current->card, count); 
	        count++;				// Count the total card in discard pile
	    }    
	}    
	
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 10;
    int startRow = csbi.srWindow.Bottom - csbi.srWindow.Top;
	gotoxy(startCol, startRow);
}

void showDrawPile(cardDeck deckInventory) {
	gotoxy(0, 0);
	int count = 0, cardInDeck = countDeck(deckInventory);
	cardAddress currentDeck = deckHead(deckInventory);
	
	printAllCards(cardInDeck);
	if (cardInDeck != 0) {	
		moveToHead(&deckInventory);
	    for (cardInDeck; cardInDeck > 0; cardInDeck--) {
			displayCardIcon(deckInventory.current, count);
	    	moveRight(&deckInventory);
			count++;
		}
	}
	
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 10;
    int startRow = csbi.srWindow.Bottom - csbi.srWindow.Top - 1;
	gotoxy(startCol, startRow);
}

void showDeck(discardPile discard, cardDeck hand, cardDeck inventory) {
	clearScreen();
	displayBorder();
	gotoxy(0, 0);
	
	int counter = 0, cardInDeck = countDeck(inventory), cardInHand = countDeck(hand);
	discardPtr currentDiscard = topDiscard(discard);
	if (topDiscard(discard) != Nil) { //Check if discard is not empty
		counter++;
	    while (cardNext(currentDiscard) != Nil) { // Check if there is next card and repeat this loop
			currentDiscard = cardNext(currentDiscard);
	        counter++;				
	    }    
	}    
	printAllCards(counter + cardInHand + cardInDeck);
	
	counter = 0;
	if (cardInDeck != 0) {
		moveToHead(&inventory);
	    for (cardInDeck; cardInDeck > 0; cardInDeck--) {
	    	displayCardIcon(inventory.current, counter);
	    	moveRight(&inventory);
			counter++;
		}
	}
    

	if (cardInHand != 0) {
		moveToHead(&hand);
	    for (cardInHand; cardInHand > 0; cardInHand--) {
	    	displayCardIcon(hand.current, counter);
	    	moveRight(&hand);
			counter++;
		}
	}
	    
	currentDiscard = topDiscard(discard);
	if (topDiscard(discard) != Nil) { //Check if discard is not empty
		displayCardIcon(currentDiscard->card, counter); 
		counter++;
	    while (cardNext(currentDiscard) != Nil) { // Check if there is next card and repeat this loop
			currentDiscard = cardNext(currentDiscard);
			displayCardIcon(currentDiscard->card, counter); 
	        counter++;				// Count the total card in discard pile
	    }    
	}    
	

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 10;
    int startRow = csbi.srWindow.Bottom - csbi.srWindow.Top;
	gotoxy(startCol, startRow);
}

void printDrawIcon() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = 7;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 17;
	gotoxy(startCol, startRows++); printf("%s                %s.:==.          ", RESET, GRAYII);
	gotoxy(startCol, startRows++); printf("        :++++-.  .. =-         ");
	gotoxy(startCol, startRows++); printf("   :==:..-=:...  ---.=-        ");
	gotoxy(startCol, startRows++); printf("-=-.:-=.   %s-####:%s    :.=:      ", RED, GRAYII);
	gotoxy(startCol, startRows++); printf("+==-.-..   %s.*####-.%s   : +      ", RED, GRAYII);
	gotoxy(startCol, startRows++); printf("==--..-     %s.#####:%s    :.+     ", RED, GRAYII);    
	gotoxy(startCol, startRows++); printf("  +==-.-.     %s+#####:%s   ..:+   ", RED, GRAYII);
	gotoxy(startCol, startRows++); printf("  :+-=: :.    %s.######.%s   .:=-  ", RED, GRAYII);
	gotoxy(startCol, startRows++); printf("    +===..+.    %s:###*:%s. .=:..+ ", RED, GRAYII);
	gotoxy(startCol, startRows++); printf("     =-==..:+-...:-::...=*##*- ");
	gotoxy(startCol, startRows++); printf("      -+-=%sPress [S] to%s-*+=-    ", RESET, GRAYII);
	gotoxy(startCol, startRows++); printf("       -%sview Draw Pile         ", RESET, GRAYII);
	gotoxy(startCol, startRows++); printf("%s        ++*+++-                %s", GRAYII, RESET);
} 

void printDiscardIcon() { // Size (32 , 14)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 38;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 17;
	gotoxy(startCol, startRows++); printf("%s           %s-++=:               ", RESET, GRAYII);
	gotoxy(startCol, startRows++); printf("         *+=====+*****-        ");
	gotoxy(startCol, startRows++); printf("        +++=   %s=#####%s*==+*+=   ", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf("      ++=*   %s==**=%s      ==+=##-", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf("    -*=*  %s=@@@@@@@@@#+=%s #=####=", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf("   .*++   %s=@@#+=*#@@@##%s+=*###+ ", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf("  ++*=       %s==#=#@@@++%s###*:   ", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf(" =*+##      %s ====*#@@#%s=####=   ", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf(".*==#@@#####%s@@@#@#+=#%s=####+    ", PURPLE, GRAYII);   
	gotoxy(startCol, startRows++); printf(" :##########*+==%s+**=*%s###*:     ", PURPLE, GRAYII);
	gotoxy(startCol, startRows++); printf("   .+*%sPress [A] to view%s*-      ", RESET, GRAYII); 
	gotoxy(startCol, startRows++); printf("         %sDiscard Pile%s#*=       ", RESET, GRAYII); 
	gotoxy(startCol, startRows++); printf("              .-+***##=        %s", RESET);
}

void printCards(int column, int row) {
    int startCol, startRow;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
    startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

    startCol = (startCol - 55) + 22 * column;
    startRow = (startRow - 13) + 15 * row;
    displayCardAt(startCol, startRow);
}

void printAllCards(int cardCount) {
    int i = 0;
	for (i; i < cardCount; i++) {
        int col = i % 5;
        int row = i / 5;
        printCards(col, row);
    }
}

void displayCardAt(int startCol, int startRow) {
	int length;
    gotoxy(startCol + 1, startRow++); printf("[X]===============. ");
    for (length = 0; length < 10; length++) {
        gotoxy(startCol + 2, startRow); printf("||");
        gotoxy(startCol + 18, startRow); printf("||");
        startRow++;
    }
    gotoxy(startCol, startRow++); printf(" .===============[X]");
}

void displayCardIcon(cardAddress card, int cardNumber) {
    int col = cardNumber % 5;
    int row = cardNumber / 5;
    
    int startCol, startRow;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
    startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

    startCol = (startCol - 55) + 22 * col;
    startRow = (startRow - 13) + 15 * row;
    
	int i = 3;
	if (card == Nil){
        gotoxy(startCol + 8, startRow + i); i++;
        printf("SOLD ");
        gotoxy(startCol + 8, startRow + i); i++;
        printf("  OUT");
        gotoxy(startCol + 8, startRow + i + 2); i++;
        printf("T   T");
        gotoxy(startCol + 8, startRow + i + 3); i++; i++;
        printf(" --- ");
        return;
    }
			
	
	char name[10];
	gotoxy(startCol + 1, startRow);
	setColorYellow();
	printf("[%d]", cardCost(card));
	gotoxy(startCol + 20 - 3, startRow + 11);
	setColorRed();
	printf("[%d]", cardEffect(card));
	
	if (strcmp(cardName(card), "PowerSlash") == 0){
		setColorLightRed();
		gotoxy(startCol + 7, startRow + i); i++;
		printf("   ^\n");
		gotoxy(startCol + 7, startRow + i); i++;
		printf("   |\n");
		gotoxy(startCol + 7, startRow + i); i++;
		printf("._<O>_.\n");
		gotoxy(startCol + 7, startRow + i); i++; i++;
		printf("   I\n");
	} else if (strcmp(cardName(card), "SuperSlash") == 0){
		setColorLightRed();
		gotoxy(startCol + 7, startRow + i); i++;
		printf("   ^\n");
		gotoxy(startCol + 7, startRow + i); i++;
		printf("   |\n");
		gotoxy(startCol + 7, startRow + i); i++;
		printf("._)*(_.\n");
		gotoxy(startCol + 7, startRow + i); i++; i++;
		printf("  `I`\n");
	} else if (strcmp(cardName(card), "Insight") == 0){
		setColorLightYellow();
		gotoxy(startCol + 7, startRow + i); i++;
		printf("\\  |  /\n");
		gotoxy(startCol + 7, startRow + i); i++;
		printf(" '.'.'\n");
		gotoxy(startCol + 7, startRow + i); i++;
		printf("~`(O)`~\n");
		gotoxy(startCol + 7, startRow + i); i++; i++;
		printf(" `-~-`\n");
	} else if (strcmp(cardName(card), "IronWall") == 0) {
		setColorLightBlue();
		gotoxy(startCol + 4, startRow + i); i++;
		printf("     /+\\\n");
		gotoxy(startCol + 4, startRow + i); i++;
		printf("   _/_|_\\_\n");
		gotoxy(startCol + 4, startRow + i); i++;
		printf(" _/_\\_|_/_\\_\n");
		gotoxy(startCol + 4, startRow + i); i++; i++;
		printf("/_\\_\\_|_/_/_\\\n");
	} else if (strcmp(cardType(card), "Attack") == 0){
    	setColorLightRed();
		gotoxy(startCol + 8, startRow + i); i++;
		printf("  ^  ");
		gotoxy(startCol + 8, startRow + i); i++;
		printf("  |  ");
		gotoxy(startCol + 8, startRow + i); i++;
    	printf("._|_.");
    	gotoxy(startCol + 8, startRow + i); i++; i++;
    	printf("  I  ");
	} else if (strcmp(cardType(card), "Shield") == 0){
		setColorLightBlue();
		gotoxy(startCol + 8, startRow + i); i++;
		printf("<--->");
		gotoxy(startCol + 8, startRow + i); i++;
	    printf("|_|_|");
		gotoxy(startCol + 8, startRow + i); i++;
	    printf("|_|_|");
    	gotoxy(startCol + 8, startRow + i); i++; i++;
	    printf("\\|_|/");
	} else if (strcmp(cardType(card), "Draw") == 0){
		setColorLightYellow();
		gotoxy(startCol + 5, startRow + i); i++;
		printf("  .-<<<-.\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf(" /       \\\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf(" \\       /\n");
		gotoxy(startCol + 5, startRow + i); i++; i++;
		printf("  `->>>-`\n");
	} 
    
	gotoxy(startCol + 8, startRow + i); i++; 
    if (strlen(cardName(card)) > 5){
	    strcpy(name, cardName(card));
	    int j = 0;
	    
	    while(j < strlen(name) && j < 10) {
	        if (j > 0 && isupper(name[j])) {
	            // Found uppercase after first character, move to next line
	            gotoxy(startCol + 8, startRow + i); 
	            i++;
	        }
	        printf("%c", name[j]);
	        j++;
	    }
	} else {
    	printf("%s", cardName(card));
	}
	setColorBrightWhite();
}

void printDiscardText() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 80;
	int startRows = 3;

	gotoxy(startCol, startRows++); printf("%s       ....             .       .x+=:.                                         ..      			    ....      ..        .          ..            ", RED);
	gotoxy(startCol, startRows++); printf("   .xH888888Hx.        @88>    z`    ^%%                                      dF        			  +^\"\"888h. ~\"888h     @88>  x .d88\"             ");
	gotoxy(startCol, startRows++); printf(" .H8888888888888:      %%8P        .   <k                          .u    .   '88bu.     			 8X.  ?8888X  8888f    %%8P    5888R                 ");
	gotoxy(startCol, startRows++); printf(" 888*\"\"\"?\"\"*88888X      .       .@8Ned8\"       .         u      .d88B :@8c  '*88888bu  			'888x  8888X  8888~     .     '888R        .u   ");      
	gotoxy(startCol, startRows++); printf("'f     d8x.   ^%%88k   .@88u   .@^%%8888\"   .udR88N     us888u.  =\"8888f8888r   ^\"*8888N 			'88888 8888X   \"88x:  .@88u    888R     ud8888.   "); 
	gotoxy(startCol, startRows++); printf("'>    <88888X   '?8  ''888E` x88:  `)8b. <888'888k .@88 \"8888\"   4888>'88\"   beWE \"888L			 `8888 8888X  X88x.  ''888E`   888R   :888'8888.  ");
	gotoxy(startCol, startRows++); printf(" `:..:`888888>    8>   888E  8888N=*8888 9888 'Y\"  9888  9888    4888> '     888E  888E			   `*` 8888X '88888X   888E    888R   d888 '88%%\"   ");
	gotoxy(startCol, startRows++); printf("        `\"*88     X    888E   %%8\"    R88 9888      9888  9888    4888>       888E  888E			  ~`...8888X  \"88888   888E    888R   8888.+\"    ");
	gotoxy(startCol, startRows++); printf("   .xHHhx..\"      !    888E    @8Wou 9%%  9888      9888  9888   .d888L .+    888E  888F			   x8888888X.   `%%8\"   888E    888R   8888L            "); 
	gotoxy(startCol, startRows++); printf("  X88888888hx. ..!     888&  .888888P`   ?8888u../ 9888  9888   ^\"8888*\"    .888N..888 			  '%%\"*8888888h.   \"    888&   .888B . '8888c. .+     ");
	gotoxy(startCol, startRows++); printf(" !   \"*888888888\"      R888\" `   ^\"F      \"8888P'  \"888*\"\"888\"     \"Y\"       `\"888*\"\"  			  ~    888888888!`     R888\"  ^*888%%   \"88888%%");        
	gotoxy(startCol, startRows++); printf("        ^\"***\"`         \"\"                  \"P'     ^Y\"   ^Y'                   \"\"     			 X888^\"\"\"         \"\"      \"%%       \"YP'           ");
	gotoxy(startCol, startRows++); printf("                                                                                                            `88f  ");
	gotoxy(startCol, startRows++); printf("                                                                                                             88   ");
	gotoxy(startCol, startRows++); printf("                                                                                                             \"\" %s", RESET);
}

void printDrawText() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 62;
	int startRows = 3;
	
	gotoxy(startCol, startRows++); printf("%s       ....                                                                   ....      ..        .          ..  ", RED);
	gotoxy(startCol, startRows++); printf("   .xH888888Hx.                                 x=~                         +^\"\"888h. ~\"888h     @88>  x .d88\"  ");     
	gotoxy(startCol, startRows++); printf(" .H8888888888888:       .u    .                88x.   .e.   .e.            8X.  ?8888X  8888f    %%8P    5888R      ");
	gotoxy(startCol, startRows++); printf(" 888*\"\"\"?\"\"*88888X    .d88B :@8c        u     '8888X.x888:.x888           '888x  8888X  8888~     .     '888R        .u      ");
	gotoxy(startCol, startRows++); printf("'f     d8x.   ^%%88k  =\"8888f8888r    us888u.   `8888  888X '888k          '88888 8888X   \"88x:  .@88u    888R     ud8888.    ");
	gotoxy(startCol, startRows++); printf("'>    <88888X   '?8    4888>'88\"  .@88 \"8888\"   X888  888X  888X           `8888 8888X  X88x.  ''888E`   888R   :888'8888. ");
	gotoxy(startCol, startRows++); printf(" `:..:`888888>    8>   4888> '    9888  9888    X888  888X  888X             `*` 8888X '88888X   888E    888R   d888 '88%%\"   ");         
	gotoxy(startCol, startRows++); printf("        `\"*88     X    4888>      9888  9888    X888  888X  888X            ~`...8888X  \"88888   888E    888R   8888.+\"  ");
	gotoxy(startCol, startRows++); printf("   .xHHhx..\"      !   .d888L .+   9888  9888   .X888  888X. 888~             x8888888X.   `%%8\"   888E    888R   8888L     ");
	gotoxy(startCol, startRows++); printf("  X88888888hx. ..!    ^\"8888*\"    9888  9888   `%%88%%``\"*888Y\"               '%%\"*8888888h.   \"    888&   .888B . '8888c. .+  ");
	gotoxy(startCol, startRows++); printf(" !   \"*888888888\"        \"Y\"      \"888*\"\"888\"    `~     `\"                  ~    888888888!`     R888\"  ^*888%%   \"88888%% "); 
	gotoxy(startCol, startRows++); printf("        ^\"***\"`                    ^Y\"   ^Y'                                     X888^\"\"\"         \"\"      \"%%       \"YP'    ");   
	gotoxy(startCol, startRows++); printf("                                                                                 `88f ");                                                     
	gotoxy(startCol, startRows++); printf("                                                                                  88   ");                                                    
	gotoxy(startCol, startRows++); printf("                                                                                  \"\"  %s", RESET);                                        
}

void printUpgradeText() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 80;
	int startRows = 3;
	
	gotoxy(startCol, startRows++); printf("%s                                                                        ..                                        ...                                      ..  ", RED);     
	gotoxy(startCol, startRows++); printf("  x8h.     x8.                                                        dF                                       xH88\"`~ .x8X                              dF  ");
	gotoxy(startCol, startRows++); printf(":88888> .x8888x.   .d``                        .u    .               '88bu.                                  :8888   .f\"8888Hf                .u    .   '88bu.         ");
	gotoxy(startCol, startRows++); printf(" `8888   `8888f    @8Ne.   .u        uL      .d88B :@8c        u     '*88888bu        .u                    :8888>  X8L  ^\"\"`        u      .d88B :@8c  '*88888bu    ");
	gotoxy(startCol, startRows++); printf("  8888    8888'    %%8888:u@88N   .ue888Nc.. =\"8888f8888r    us888u.    ^\"*8888N    ud8888.                  X8888  X888h          us888u.  =\"8888f8888r   ^\"*8888N     ");
	gotoxy(startCol, startRows++); printf("  8888    8888      `888I  888. d88E`\"888E`   4888>'88\"  .@88 \"8888\"  beWE \"888L :888'8888.                 88888  !88888.     .@88 \"8888\"   4888>'88\"   beWE \"888L   ");
	gotoxy(startCol, startRows++); printf("  8888    8888       888I  888I 888E  888E    4888> '    9888  9888   888E  888E d888 '88%%\"                 88888   %%88888     9888  9888    4888> '     888E  888E  ");
	gotoxy(startCol, startRows++); printf("  8888    8888       888I  888I 888E  888E    4888>      9888  9888   888E  888E 8888.+\"                    88888 '> `8888>    9888  9888    4888>       888E  888E  ");
	gotoxy(startCol, startRows++); printf("  8888    8888     uW888L  888' 888E  888E   .d888L .+   9888  9888   888E  888F 8888L                      `8888L %%  ?888   ! 9888  9888   .d888L .+    888E  888F ");
	gotoxy(startCol, startRows++); printf("-n88888x>\"88888x- '*88888Nu88P  888& .888E   ^\"8888*\"    9888  9888  .888N..888  '8888c. .+                  `8888  `-*\"\"   /  9888  9888   ^\"8888*\"    .888N..888     ");
	gotoxy(startCol, startRows++); printf("  `%%888\"  4888!`  ~ '88888F`    *888\" 888&      \"Y\"      \"888*\"\"888\"  `\"888*\"\"    \"88888%%                      \"888.      :\"   \"888*\"\"888\"     \"Y\"       `\"888*\"\"  ");
	gotoxy(startCol, startRows++); printf("    `\"      \"\"       888 ^       `\"   \"888E               ^Y\"   ^Y'      \"\"         \"YP'                         `\"\"***~\"`      ^Y\"   ^Y'                   \"\"    ");
	gotoxy(startCol, startRows++); printf("                     *8E        .dWi   `88E    ");                                                             
	gotoxy(startCol, startRows++); printf("                     '8>        4888~  J8%%   ");                                                               
	gotoxy(startCol, startRows++); printf("                      \"          ^\"===*\"` %s", RESET);                                                                   
}

