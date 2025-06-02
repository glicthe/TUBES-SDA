#include "inGameLayout.h"

void inGame(int startCol, int startRow){
	// initiate
	setColorDefault;
    Player P = createPlayer();
    mobContainer C;
	createMobContainer(&C);
    randGenerateMob(&C);
    cardDeck deckInventory;
    initDeck(&deckInventory);
	starterDeckInventory(&deckInventory);
	initDeckInventoryToHand(&deckInventory, &P.hand, 0);
	
    int turnCounter = 0;
    int key;
	int running = 1;
	int damage;
	boolean state;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int mobStatsCol = startCol + 117;
	int mobStatsRow = (startRow / 2);
	int playerStatsCol = startCol - 76;
	int playerStatsRow = (startRow / 2);
	int battleScreenCol = startCol - 45; 
	int battleScreenRow = (startRow / 2) - 2;
	int inHandCol = startCol - 15; 
	int inHandRow = rows - startRow + 1; 
	
	
	while (running) {
		goto PlayerTurn;
		PlayerTurn:
			state = true;
			clearScreen();
			displayBorder();
			
			headBar(startCol, columns, P, turnCounter); 
			battleScreen(battleScreenCol, battleScreenRow, columns, rows); 
		    printMobContainer(C, mobStatsCol, mobStatsRow);
		    printPlayerStatus(P, playerStatsCol, playerStatsRow);
		    
		    printDeck(P.hand, inHandCol, inHandRow);
		    printCurrentCard(P.hand, playerStatsCol, playerStatsRow);
		    printCurrentMob(C, mobStatsCol, playerStatsRow);
		    showMobPlayer(C, columns, rows, state);
		    
			key = getch();
			switch(key){
				case 224:
		            key = getch();
	
		            switch (key) {
		                case KEY_LEFT:
		                    playArrowBeep();
		                    moveLeft(&P.hand);
		                    break;
		                    
		                case KEY_RIGHT:
		                    playArrowBeep();
		                    moveRight(&P.hand);
		                    break;
		                case KEY_UP:
		                	playArrowBeep();
		                	moveRightMob(&C);
		                	break;
		                case KEY_DOWN:
		                	playArrowBeep();
		                	moveLeftMob(&C);	
		                	break;
		            }
		            break;
	            case KEY_ENTER:
	            	playEnterBeep();
	            	int tempMob = mobHealth(currentMob(C));
					playCard(&P, &deckInventory, &C);
	            	if (currentMob(C) != Nil && tempMob > mobHealth(currentMob(C))) {
	            		state = false;
						clearScreen();
						displayBorder();
						showMobPlayer(C, columns, rows, state);
						Sleep(500);
						state = true;
					}
					checkMobHealth(&C);
	            	break;
	            case 'h':
	            	playEnterBeep();
	            	executeMenuAction(4);
	            	break;
	            case 'e':
					turnCounter++; 
	            	goto MobTurn;
	            	break;
		    	case 'q':
		    		playEnterBeep();
		    		SplashScreen();
		    		running = 0;
		    		goto end;
	                break;
			} 
			if (countMob(C) == 0) goto end;
	} 
	
	MobTurn:
		clearScreen();
		mobAddress current = firstMob(C);
		while (current != Nil) {	
			clearScreen();
			displayBorder();
				
			headBar(startCol, columns, P, turnCounter);
			battleScreen(battleScreenCol, battleScreenRow, columns, rows); 
			printMobContainer(C, mobStatsCol, mobStatsRow);
			printPlayerStatus(P, playerStatsCol, playerStatsRow);
			showMobPlayer(C, columns, rows, state);
			    
			
			if (!strcmp(mobActionType(current), "attack")){
				damage = attack(current);
				takeDamage(&P, damage);
			} else {
				mobheal(&current);
				P.shield = 0;
			}
			
			current = mobNext(current);
		    Sleep(1500);
		}
	    
		initDiscardToInventory(&P.discard, &deckInventory);
		initDeckInventoryToHand(&deckInventory, &P.hand, 0);
		randAction(C);
	    turnCounter++;
	    P.energy = 3;
		if (countMob(C) != 0) goto PlayerTurn;
	    else goto end;
		    
	end:
		SplashScreen();
}

void headBar(int startCol, int max, Player P, int turnCounter){
	int i, headBarRow = 3;
	int headBarCol = 2;;
	int checkTurn = turnCounter % 2;
	
	
	gotoxy(headBarCol, headBarRow);
	setColorBrightWhite();
	for(i = 0; i < max - 4; i++) printf("=");
	for(i = 1; i <= 5; i++) {
		gotoxy(headBarCol, headBarRow + i);
		printf("[]");
	}
	
    gotoxy(startCol - 71, headBarRow + 2);
	setColorBrightWhite();
	printf("===========");
	gotoxy(startCol - 70, headBarRow + 3);
	setColorRed();
    printf("[Q] QUIT!");
    gotoxy(startCol - 71, headBarRow + 4);
    setColorBrightWhite();
	printf("===========");
    
    gotoxy(startCol - 26, headBarRow + 2);
	setColorBrightWhite();
	printf("===========");
	gotoxy(startCol - 25, headBarRow + 3);
	setColorLightYellow();
	printf("[%d] GOLD", P.gold);
    gotoxy(startCol - 26, headBarRow + 4);
    setColorBrightWhite();
	printf("===========");
    
    gotoxy(startCol + 30, headBarRow + 2);
	setColorBrightWhite();
	printf("===================");
	gotoxy(startCol + 31, headBarRow + 3);
	setColorBrightWhite();
    if (checkTurn == 0){
		printf("[%d] PLAYER'S TURN", turnCounter);
	} else printf(" [%d] MOB'S TURN", turnCounter);
    gotoxy(startCol + 30, headBarRow + 4);
    setColorBrightWhite();
	printf("===================");
    
    gotoxy(startCol + 79, headBarRow + 2);
	setColorBrightWhite();
	printf("===========");
    gotoxy(startCol + 80, headBarRow + 3);
	setColorGreen();
    printf("LEVEL [_]");
    gotoxy(startCol + 79, headBarRow + 4);
	setColorBrightWhite();
	printf("===========");
    
    gotoxy(startCol + 124, headBarRow + 2);
	setColorBrightWhite();
	printf("==================");
    gotoxy(startCol + 125, headBarRow + 3);
	setColorCyan();
    printf("[H] HOW TO PLAY?");
    gotoxy(startCol + 124, headBarRow + 4);
	setColorBrightWhite();
	printf("==================");
    
    
    gotoxy(headBarCol, headBarRow + 6);
    setColorBrightWhite();
	for(i = 0; i < max - 4; i++) printf("=");
	setColorDefault;
	for(i = 1; i <= 5; i++) {
		gotoxy(max - 4, headBarRow + i);
		printf("[]");
	}
}

void battleScreen(int startCol, int startRow, int columns, int rows){
	int i, bottomRow, maxCol;
	
	bottomRow = rows - 40;
	maxCol = columns - 69;
	gotoxy(startCol, startRow);
	setColorHighlight();
	for(i = 0; i < maxCol; i++) printf("=");
	for(i = 1; i <= bottomRow; i++) {
		gotoxy(startCol, startRow + i);
		printf("||");
		gotoxy(columns - startCol - 3, startRow + i);
		printf("||");
	}
	gotoxy(startCol, bottomRow + startRow);
	for(i = 0; i < maxCol; i++) printf("=");
	setColorDefault;
}

void showMobPlayer(mobContainer C, int columns, int rows, boolean state){
	int i, startCol, startRow;
	startCol = columns - 100;
	startRow = rows / 3;
	mobAddress current = firstMob(C);
	
	while (current != Nil){
		i = 1;
		if (!strcmp(mobType(current), "Goblin")) {
			setColorLightCyan();
			gotoxy(startCol, startRow + i); i++;
			printf("  [%d] ", mobCounter(current));
			if (!state) setColorRed();
			else setColorGreen();
		} else if (!strcmp(mobType(current), "Ghost")) {
			i = 5;
			setColorLightCyan();
			gotoxy(startCol, startRow + i); i++;
			printf(" [%d] ", mobCounter(current));
			if (!state) setColorRed();
			else setColorBrightWhite(); 
		}
		if (current == currentMob(C) && state){
			gotoxy(startCol, startRow);
			setColorGray();
		}
		
		if (!strcmp(mobType(current), "Goblin")){
			gotoxy(startCol, startRow + i); i++;
			printf(" .-^-. ");
			gotoxy(startCol, startRow + i); i++;
			printf("( @ @ )");
			gotoxy(startCol, startRow + i); i++;
			printf(" \\ V /");
			gotoxy(startCol, startRow + i); i++;
			printf(" .='=.");
			gotoxy(startCol, startRow + i); i++;
			printf("//\\_/\\\\");
			gotoxy(startCol, startRow + i); i++;
			printf("\\)|_|(/");
			gotoxy(startCol, startRow + i); i++;
			printf("  /|\\");
			gotoxy(startCol, startRow + i); i++;
			printf(" (/ \\)");
		} else if (!strcmp(mobType(current), "Ghost")) {
			i = 6;
			gotoxy(startCol, startRow + i); i++;
			printf(" .-. ");
			gotoxy(startCol, startRow + i); i++;
    		printf("| OO|");
    		gotoxy(startCol, startRow + i); i++;
    		printf("|   |");
    		gotoxy(startCol, startRow + i); i++;
    		printf("'^^^'");
		}
		startCol += 21;
		current = mobNext(current);
	}
	
}

void playCard(Player *P, cardDeck *Inventory, mobContainer *C) {
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
			attacked(cardEffect(played), C);
		} else if (strcmp(cardType(played), "Shield") == 0) {
			P->shield += cardEffect(played);
		} else if (strcmp(cardType(played), "Draw") == 0) {
			initDeckInventoryToHand(Inventory, &P->hand, cardEffect(played));
		}
		pushDiscard(&P->discard, played);
	}
}




