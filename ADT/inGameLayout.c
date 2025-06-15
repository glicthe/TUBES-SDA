#include "inGameLayout.h"

void inGame(int startCol, int startRow, int type, int depth){
	// initiate
	static mobContainer C;
	static Player P;
	static Boss* boss;
    static cardDeck deckInventory;
	if (depth == 1) {
    	P = createPlayer();
    	boss = Nil;
		createMobContainer(&C);
    	initDeck(&deckInventory);
		starterDeckInventory(&deckInventory);
	}
	
	if (type == 1) {
    	randGenerateMob(&C);
	} else if (type == 2) {
		boss = createRandSecondaryBoss(boss);
	} else if (type == 3) {
		patternQueue dragoon;
		boss = createBoss("dragoon", 80, &dragoon);
	} else if (type == 4) {
		merchantScreen(&P, &deckInventory);
		return;
	} else if (type == 5) {
		initDiscardToInventory(&P.discard, &deckInventory);
		restScreen(&P, &deckInventory);
		return;
	}
    
    initDiscardToInventory(&P.discard, &deckInventory);
	initDeckInventoryToHand(&deckInventory, &P.hand, 0);
	
	P.energy = 3;
    int turnCounter = 0;
	int running = 1;
	int tempMob, damage, key;
	boolean state;
	char* playerState;
	int prevBossHealth;
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	int mobStatsCol = startCol + 117;
	int mobStatsRow = (startRow / 2) - 2;
	int playerStatsCol = startCol - 77;
	int playerStatsRow = (startRow / 2) - 2;
	int battleScreenCol = startCol - 46; 
	int battleScreenRow = (startRow / 2) - 2;
	int inHandCol = startCol - 15; 
	int inHandRow = rows - startRow + 2; 
	
	
	while (running) {
		goto PlayerTurn;
		PlayerTurn:
			if (P.health == 0) goto Lose;
			state = true;
			clearScreen();
			playerState = "default";
			displayBorder();
			hideCursor();
			setColorDefault();
			
			headBar(startCol, columns, P, turnCounter); 
			battleScreen(battleScreenCol, battleScreenRow, columns, rows, "default"); 
			
			if (type == 1) {
				printCurrentMob(C, mobStatsCol, playerStatsRow);
				printMobContainer(C, mobStatsCol, mobStatsRow);
			} else if (type == 2 || type == 3) {
				printBossStats(boss, mobStatsCol, mobStatsRow);
			}
		    
			printPlayerStatus(P, playerStatsCol, playerStatsRow);
		    printDeck(P.hand, inHandCol, inHandRow);
		    printCurrentCard(P.hand, playerStatsCol, playerStatsRow);
		    printDiscardIcon(); 
			printDrawIcon();
		    showMobPlayer(boss, C, columns, rows, state);
		    
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
		                	if (type == 1) moveRightMob(&C);
		                	break;
		                case KEY_DOWN:
		                	playArrowBeep();
		                	if (type == 1) moveLeftMob(&C);	
		                	break;
		            }
		            break;
	            case KEY_ENTER:
	            	playEnterBeep();
                    playerState = strdup(cardType(currentCard(P.hand)));
				    if (P.energy != 0){
					    if (type == 1) {
					        tempMob = mobHealth(currentMob(C));
					    } else if (type == 2 || type == 3) {
					        prevBossHealth = (boss != NULL) ? bossHealth(boss) : 0;
					    }
					    
					    playCard(&P, &deckInventory, &C, boss);  
						if (currentMob(C) != NULL && tempMob > mobHealth(currentMob(C))) {
					        clearScreen();
					        displayBorder();
					        showMobPlayer(boss, C, columns, rows, false);
					        Sleep(500);
					    }
					        
						if (boss != NULL && prevBossHealth > bossHealth(boss)) {
					    	clearScreen();
					        displayBorder();
					        showMobPlayer(boss, C, columns, rows, false);
					        Sleep(500);
					    }
					    
					    if (strcmp(playerState, "Shield") == 0) {
					        battleScreen(battleScreenCol, battleScreenRow, columns, rows, playerState); 
					        setColorDefault();
					        Sleep(400);
					    }
					}
				    
				    if (type == 1) {
				        checkMobHealth(&C);
				    }
				    break;
	            case 'h':
	            	playEnterBeep();
	            	executeMenuAction(3);
	            	break;
	            case 'e':
					turnCounter++; 
	            	if (type == 1) {
                    	goto MobTurn;
                    } else {
                        goto BossTurn;
                    }
	            	break;
		    	case 'q':
		    		playEnterBeep();
		    		SplashScreen();
		    		running = 0;
		    		goto Lose;
	                break;
	            case 'a':
	            	showDiscardPile(P.discard);
	            	system("pause");
	            	break;
	            case 's':
	            	showDrawPile(deckInventory);
	            	system("pause");
	            	break;
		    	case 'd':
					showDeck(P.discard, P.hand, deckInventory);
					system("pause");
	                break;			
			} 
			if (type == 1 && countMob(C) == 0) goto Win;
            if ((type == 2 || type == 3) && (boss == NULL || bossHealth(boss) <= 0)) goto Win;
            
            continue;
	} 
	
	MobTurn:
		clearScreen();
		mobAddress current = firstMob(C);
		while (current != Nil) {	
			clearScreen();
			displayBorder();
				
			battleScreen(battleScreenCol, battleScreenRow, columns, rows, "default"); 
			headBar(startCol, columns, P, turnCounter);
			printMobContainer(C, mobStatsCol, mobStatsRow);
			printPlayerStatus(P, playerStatsCol, playerStatsRow);
			showMobPlayer(boss, C, columns, rows, state);
			    
		    Sleep(500);
			if (!strcmp(mobActionType(current), "attack")){
				damage = attack(current);
				battleScreen(battleScreenCol, battleScreenRow, columns, rows, "attacked"); 
				setColorDefault();
				takeDamage(&P, damage);
			} else {
				mobheal(&current);
			}
			current = mobNext(current);
		    Sleep(1000);
		}
	    
	    if (countDeck(deckInventory) <= 0){
			initDiscardToInventory(&P.discard, &deckInventory);
		}
		initDeckInventoryToHand(&deckInventory, &P.hand, 0);
		randAction(C);
	    turnCounter++;
		P.shield = 0;
		P.energy = 3;
		goto PlayerTurn;
	
	BossTurn:
		clearScreen();
		displayBorder();
		
		char bossAction[10];
		int quantity = 0 ;
		battleScreen(battleScreenCol, battleScreenRow, columns, rows, "default");
		headBar(startCol, columns, P, turnCounter);
		
		printBossStats(boss, mobStatsCol, mobStatsRow);
		printPlayerStatus(P, playerStatsCol, playerStatsRow);
		
		showMobPlayer(boss, C, columns, rows, state);
		executeBossAction(boss, bossAction, &quantity);
		
		Sleep(500);
		if (!strcmp(bossAction, "Attack")) {
			clearScreen();
			if (!strcmp(bossType(boss), "dragoon")) {
				battleScreen(battleScreenCol, battleScreenRow, columns, rows, "dragoon"); 
			} else if (!strcmp(bossType(boss), "unicorn")) {
				battleScreen(battleScreenCol, battleScreenRow, columns, rows, "unicorn"); 
			} else if (!strcmp(bossType(boss), "griffin")) {
				battleScreen(battleScreenCol, battleScreenRow, columns, rows, "griffin"); 
			}
			takeDamage(&P, quantity);
		} else  {
			bossHeal(boss, quantity);
		}
		
		Sleep(1000);
		if (countDeck(deckInventory) <= 0){
			initDiscardToInventory(&P.discard, &deckInventory);
		}
        initDeckInventoryToHand(&deckInventory, &P.hand, 0);
	    P.energy = 3;
	    turnCounter++;
        
        goto PlayerTurn;
	
	Win:
		restartCard(&deckInventory, &P.hand, &P.discard);if (type == 1 || type == 2 || type == 3) {
        showRewardScreen(&P, depth, type);
		return;
	Lose:
		showLoseScreen();
		SplashScreen();
	}
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
	
    gotoxy(startCol - 72, headBarRow + 2);
	setColorBrightWhite();
	printf("===========");
	gotoxy(startCol - 71, headBarRow + 3);
	setColorRed();
    printf("[Q] QUIT!");
    gotoxy(startCol - 72, headBarRow + 4);
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
    
    gotoxy(startCol + 26, headBarRow + 2);
	setColorBrightWhite();
	printf("===================");
	gotoxy(startCol + 27, headBarRow + 3);
	setColorBrightWhite();
    if (checkTurn == 0){
		printf("[%d] PLAYER'S TURN", turnCounter);
	} else printf(" [%d] MOB'S TURN", turnCounter);
    gotoxy(startCol + 26, headBarRow + 4);
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

void battleScreen(int startCol, int startRow, int columns, int rows, char* state){
	int i, bottomRow, maxCol;
	
	bottomRow = rows - 40;
	maxCol = columns - 74;
	const int screenBorder = (COLOR_WHITE * 16) + COLOR_WHITE;
	const int screenBorderAttacked = (COLOR_RED * 16) + COLOR_RED;
	const int screenBorderBlock = (COLOR_BLUE * 16) + COLOR_BLUE;
	
	if (!strcmp(state, "attacked")){
		setTextColor(screenBorderAttacked);
	} else if (!strcmp(state, "Shield")) {
		setTextColor(screenBorderBlock);
	} else if (!strcmp(state, "dragoon")){
		printBossAttack(startCol, startRow, "dragoon");
		setTextColor(screenBorderAttacked);
	} else if (!strcmp(state, "unicorn")) {
		printBossAttack(startCol, startRow, "unicorn");
		setTextColor(screenBorderAttacked);
	} else if (!strcmp(state, "griffin")) {
		printBossAttack(startCol, startRow, "griffin");
		setTextColor(screenBorderAttacked);
	} else setTextColor(screenBorder);
	
	
	
	startRow -= 1;
	gotoxy(startCol, startRow);
	for(i = 0; i <= maxCol; i++) printf("=");
	for(i = 1; i <= bottomRow; i++) {
		gotoxy(startCol, startRow + i);
		printf("||");
		gotoxy(columns - startCol - 3, startRow + i);
		printf("||");
	}
	gotoxy(startCol, bottomRow + startRow);
	for(i = 0; i <= maxCol; i++) printf("=");
	
	setColorDefault();
}

void showMobPlayer(Boss* boss, mobContainer C, int columns, int rows, boolean state){
	int i, startCol, startRow;
	
	printMob(startCol, startRow, columns, rows, C, state);
	
	/**/
	if (boss != Nil) {
        startCol = columns - 100;
        startRow = rows / 3;
        printBoss(startCol, startRow, boss, state);
        
	}
	
	startCol = (columns / 4) - 50;
	startRow = rows / 3 - 5;
	setColorDefault();
	printPlayerSprite(startCol, startRow);
	
	setColorDefault();
	
}

void playCard(Player *P, cardDeck *Inventory, mobContainer *C, Boss* boss) {
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
	
        if (strcmp(cardType(played), "Attack") == 0) {
            if (currentMob(*C) != NULL) {
                // Fighting mobs
                attacked(cardEffect(played), C);
            } else if (boss != NULL) {
                // Fighting boss
                attackedBoss(cardEffect(played), boss);
            }
        } else if (strcmp(cardType(played), "Shield") == 0) {
            P->shield += cardEffect(played);
        } else if (strcmp(cardType(played), "Draw") == 0) {
            initDeckInventoryToHand(Inventory, &P->hand, cardEffect(played));
        }
        pushDiscard(&P->discard, played);
	}
}

// Merchant
void merchantScreen(Player *player, cardDeck *inventory) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
	/*
	int nameCol = 50;
	int nameRow = 5;
	int i = 0;
	*/
	
    // Array 2x5 merchant card
    cardAddress merchantCards[2][5];
    int prices[2][5];
    int row, column;

    // Generate cards and their prices
    for (row = 0; row < 2; row++) {
        for (column = 0; column < 5; column++) {
            merchantCards[row][column] = generateRandomCard();
            prices[row][column] = 20 + randNumGenerator();
        }
    }

    int currentRow = 0, currentCol = 0;
    bool exitMerchant = false;
	bool isBuy = false;

    while (!exitMerchant) {
    	clearScreen();
    	displayBorder();
    	printMerchant();
    	if (isBuy){
			proceedLabel();
		} else {
			skipLabel("Merchant");
		}
        gotoxy(columns - 10, rows + 17);
		printf("Gold: %d", player->gold);

        // Display navigation
        for (row = 0; row < 2; row++) {
            for (column = 0; column < 5; column++) {
            	printCards(column, row);
				displayCardIcon(merchantCards[row][column], (row * 5 + column));
                if (row == currentRow && column == currentCol) {
                    // Position
                    printHand(column, row);
                    setColorBlue(); printCards(column, row); setColorWhite();
                    gotoxy(columns - 10, rows + 16);
		        	if (merchantCards[row][column] != Nil) {
						printf("%-12s (%s) - %d [%d gold]\n",
	                    		cardName(merchantCards[row][column]),
	                    		cardType(merchantCards[row][column]),
	                    		cardCost(merchantCards[row][column]),
	                    		prices[row][column]
						);
					} else {
						printf("Sold");
					}
				}
				displayCardIcon(merchantCards[row][column], (row * 5 + column));
            }
        }
        gotoxy(columns - 10, rows + 18);
		printf("Use arrow keys to move, ENTER to buy, ESC to exit.");
		
        int ch = getch();
        if (ch == 224) {
            ch = getch();
            switch (ch) {
                case KEY_UP:
                	playArrowBeep();
                    currentRow = (currentRow == 0) ? 1 : 0;
                    break;
                case KEY_DOWN:
                	playArrowBeep();
                    currentRow = (currentRow == 1) ? 0 : 1;
                    break;
                case KEY_LEFT:
                	playArrowBeep();
                    currentCol = (currentCol == 0) ? 4 : currentCol - 1;
                    break;
                case KEY_RIGHT:
                	playArrowBeep();
                    currentCol = (currentCol == 4) ? 0 : currentCol + 1;
                    break;
            }
        } else if (ch == KEY_ENTER) {
        	cardAddress selected = merchantCards[currentRow][currentCol];
        	if (selected != Nil) {
        		playEnterBeep();
	            int price = prices[currentRow][currentCol];
	            if (player->gold >= price) {
	                addCardToDeck(inventory, selected);
	                player->gold -= price;
	                printf("\nYou bought %s!\n", cardName(selected));
	                isBuy = true;
			        merchantCards[currentRow][currentCol] = Nil;
	            } else {
	                printf("\nNot enough gold!\n");
	                getch();
	            }
            } else {
        	    gotoxy(columns - 2, rows + 16);
				setColorRed(); printf("You have bought it ALREADY!");  setColorWhite();
			}
        } else if (ch == KEY_ESC) {
            exitMerchant = true;
            // Destroy merchant cards after leaving merchant
		    for (row = 0; row < 2; row++) {
		        for (column = 0; column < 5; column++) {
		            freeCard(merchantCards[row][column]);
        		}
    		}
    		
        }
    }
}

cardAddress generateRandomCard() {
    int roll = rand() % 3;
    switch (roll) {
        case 0:
            return createCard("PowerSlash", "Attack", 2, 8);
        case 1:
            return createCard("IronWall", "Shield", 2, 10);
        case 2:
            return createCard("Insight", "Draw", 1, 2);
        default:
            return createCard("Strike", "Attack", 1, 6);
    }
}

void printMerchant(){
	int i = 1;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 38;
	int startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 9;
	gotoxy(startCol, startRow++); printf("            %s+++++##               ", BLUE);
	gotoxy(startCol, startRow++); printf("          +%s-+%s----%s+###             ", RED, RESET, BLUE);
	gotoxy(startCol, startRow++); printf("          +%s++%s-----%s+###            ", RED, RESET, BLUE);
	gotoxy(startCol, startRow++); printf("           +%s-----%s++%s#####          ", RESET, CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("           #+++++###              ");
	gotoxy(startCol, startRow++); printf("          #+###++##               ");
	gotoxy(startCol, startRow++); printf("         ++############           ");
	gotoxy(startCol, startRow++); printf("         ++++###++##++#           ");
	gotoxy(startCol, startRow++); printf("         +++++####++++##          ");
	gotoxy(startCol, startRow++); printf("         ####+++#+++#####         ");
	gotoxy(startCol, startRow++); printf("     %s++++%s######%s+++%s#########       ", CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("     %s+++++%s###########%s++++%s###      ", CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("    %s+++++-++%s########%s++++++%s###     ", CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("   #%s+++%s#%s++---++%s#####%s++-++%s#######  ", CYAN, BLUE, CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("##############%s++++%s################", CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("  #############%s++%s##########       ", CYAN, BLUE);
	gotoxy(startCol, startRow++); printf("          ##%sMERCHANT%s## %s           ", RESET, BLUE, RESET);
}

void printHand(int column, int row){
	int startCol, startRow;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
	
	startCol = (startCol - 55) + 22 * column;
	startRow = (startRow - 29) + 15 * row;
	gotoxy(startCol, startRow++); printf("%s@<=)[{{}{}{]}}]@@=]-  ", BLUE);
	gotoxy(startCol, startRow++); printf(" @-)~............)(@-  ");
	gotoxy(startCol, startRow++); printf(" @@....:-:.-~~..*>-@   ");
	gotoxy(startCol, startRow++); printf(" :@-.......::~~~-=..@  ");
	gotoxy(startCol, startRow++); printf("   (@@<...>@@@@@@@..@  ");
	gotoxy(startCol, startRow++); printf("+@@@@@@@@@@@@@@@@@@  ");
	gotoxy(startCol, startRow++); printf("%s @@@###@@@@{#####(@.@  ", CYAN);
	gotoxy(startCol, startRow++); printf(" @@...::=.*.@@@@##@@   ");
	gotoxy(startCol, startRow++); printf(" {@@#######@@@@@@#@@   ");
	gotoxy(startCol, startRow++); printf("  @@@@@-###@@##@@#@@{  ");
	gotoxy(startCol, startRow++); printf("   @@@@@@##@@@@#.@@@@  ");
	gotoxy(startCol, startRow++); printf("      @@@@@@@}..@@~    ");
	gotoxy(startCol, startRow++); printf("        {@@@..-@@      ");
	gotoxy(startCol, startRow++); printf("         [@@           ");
	gotoxy(startCol, startRow++); printf("         (@@           ");
	gotoxy(startCol, startRow++); printf("         [@*          %s ", RESET);
}

//Rest Area
void restScreen(Player *player, cardDeck *deck) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	bool exitRestSite = false;
	bool chooseHeal = true;
	bool isResting = false;
	
	//Selection
    while (!exitRestSite) {
    	clearScreen();
    	displayBorder();
		campFire();
    	if (isResting){
			proceedLabel();
		} else {
			skipLabel("Rest Site");
		}

	    // Display 2 Option (Rest and Smith)
		printRest();
		printSmith();
		// Display highlighter
		if (chooseHeal) {
			setColorBlue();
			highlightLeft();
			setColorWhite();
		} else {
			setColorBlue();
			highlightRight();
			setColorWhite();
		}
	    
		//Selection
	    int ch = getch();
	    if (ch == 224) {
	        ch = getch();
	        if (ch == KEY_LEFT || ch == KEY_RIGHT) {
            	playArrowBeep();
                chooseHeal = !chooseHeal;
			}
	    } else if (ch == KEY_ENTER) {
	    	if (isResting != true) {
	    		playEnterBeep();
	            if (!chooseHeal) {
					upgradeCard(deck);
	                isResting = true;
	            } else {
			        int heal = (MAX_PLAYER_HEALTH - player->health) * 0.3;  //heal berdasarkan 30% hp yang hilang
			        gainHP(player, heal);
	                isResting = true;
	            }
	        } else {
	    	    gotoxy(columns - 2, rows + 16);
				setColorRed(); printf("You have done rest action!");  setColorWhite();
				gotoxy(columns - 2, rows + 17);
				system("pause");
			}
	    } else if (ch == KEY_ESC) {
	        exitRestSite = true;
    	}
	}
}

void campFire() { //Size (61, 34)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 66;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 38;
    gotoxy(startCol, startRows); printf("                          %s=@@                                ", RED);
    gotoxy(startCol, startRows++); printf("                         @@@##                               ");
    gotoxy(startCol, startRows++); printf("                         @@*#@  @@                           ");
    gotoxy(startCol, startRows++); printf("                          -@*@.+@@@                          ");
    gotoxy(startCol, startRows++); printf("                           =@+#@*+@@                         ");
    gotoxy(startCol, startRows++); printf("                        *  %@%s-=+=-%s*@     ..                  ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                      @@@@ %@%s=##:.*%s@@    @@                  ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                     =@@#  =@%s :# =*%s@@   ##@@@                ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                    @@**# #@%s*+ : +*%s@@  *@*@@                 ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                    +@.*@..@%s= :=.##%s@* +@*+@@                 ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                    @@%s+-%s*@@%s*.-+=:.-%s*@-:@-@=                  ", YELLOW, RED, YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                     :@%s*#*= =:.*= =%%###%s**@                  ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                      @*%s.-%%.+  **:%%:@=:%s@@                  ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                @@@@  :@:%s .=.  :*=:. #= %s@@                   ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                +@*@@ +@#%s:**%%+  :%%%#  =@- %s@@@              ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("                -@:%s#=:@*.#. ## -    ==   ##%s@@*@=             ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("               :@#%s:.###..  .##+.. :   -*.=#*-%s*@@             ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("              %%@#%s+  *##::  *@* :: .=.+%%+- #- %s+%%:          ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("             .@#%s-.-=-=#*  .  ::     =%%++=#=+%s###@@           ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("            -@*@%s%*:..*+:  .---.::. .: -%%. : +%s#=@@           ", YELLOW, RED, RED);
    gotoxy(startCol, startRows++); printf("            %%@%s== +. %s+%%%s+  .-::.  :==.  +*  :%s-+#+@@          ", YELLOW, RED, YELLOW, RED);
    gotoxy(startCol, startRows++); printf("            #@%s-= +: .%s%%%%%s .  -:   --. .:.   -:=%s*@%%          ", YELLOW, RED, YELLOW, RED);
    gotoxy(startCol, startRows++); printf("            #@*#%s= :   .-=:         -+=.   :.-*%s@@             ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("              @**%s*:-   .=-+-    :*+-:.    ..%s*@               ", YELLOW, RED);
    gotoxy(startCol, startRows++); printf("%s   @@@@@@@@@@@@@@%s*-   .                 .=*%s@@@@@@@@@@@@@@    ", BROWN, YELLOW, BROWN);
    gotoxy(startCol, startRows++); printf(" @@    +        -@@@##    .          .  ##@@@-        =  @@  ");
    gotoxy(startCol, startRows++); printf(" #@ =*  ##+*@@@@@*.  +@#  :@@@@@@@@*  #@*   *@@@@@*+#  *= @@ ");
    gotoxy(startCol, startRows++); printf(" @@ .   *@@    #+=++##*@@@##+=:::-#@@@###+===#:   @@*   . @@ ");
    gotoxy(startCol, startRows++); printf("   @@@@@@@      #@###@@@@=@@@@@@@##*@@@@*##@##      ##@@@@@@ ");
    gotoxy(startCol, startRows++); printf("        =@   .###  ##@* .@+        +@* :@@##  ###:   @@      ");
    gotoxy(startCol, startRows++); printf("         *@*     .@@   @@  -##*=.- ##@   #@-     +@@         ");
    gotoxy(startCol, startRows++); printf("           ##@@@@@@     @@   :  =  .@@     @@@@@@@           ");
    gotoxy(startCol, startRows++); printf("                         @@+###*@@@                          %s", RESET);
}

void printRest() { //Size (44, 24)
	highlightLeft();
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 46;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 13;
	gotoxy(startCol, startRows++); printf("%s                            .:--::.              ", GRAY);
	gotoxy(startCol, startRows++); printf("                      .*:.*#########*=.          ");
	gotoxy(startCol, startRows++); printf("                       +*###############-.       ");
	gotoxy(startCol, startRows++); printf("                       +#%s=::--==+%s*########+.  :. ", RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s                      .=:........::..::%s+####+:*- ", RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s                    .--:........::.........%s+##*: ", RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s                 .......::..:...-..........-%s###: ", RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s               .-==-:%s.........:::--........%s=++*: ", BLUEI, RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s             .===========-:%s..........::...--%s==*: ", BLUEI, RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s          .:===================::%s.......:--%s===*- ", BLUEI, RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s        .-=========================-:%s....::--%s=#- ", BLUEI, RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s      .-===============================-%s..:---%s*- ", BLUEI, RESET, GRAY);
	gotoxy(startCol, startRows++); printf("%s=#+..%s:===============================++-..:%s. .*= ", GRAY, BLUEI, RESET);
	gotoxy(startCol, startRows++); printf("%s.#=-*########**+%s===================++===...      ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s.################*%s===============++=====..       ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s.##################*+%s==========++=====-.         ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s:####################*==*#*%s==++=====-.           ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s:######################++#*%s=+=====-.             ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s:#########################*%s======:.              ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s:#=  :+*##################*%s====:                 ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s         .-+*#############*%s==-.                  ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s             ..-+#########*=:%s.                   ", GRAY, BLUEI);
	gotoxy(startCol, startRows++); printf("%s                    :=*####.                     ", GRAY);
	gotoxy(startCol, startRows++); printf("                        :*#                      %s", RESET);
}

void printSmith() { //Size (44, 24)
	highlightRight();
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 + 6;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 13;
	gotoxy(startCol, startRows++); printf("%s                                   .-:.               ", GRAY);
	gotoxy(startCol, startRows++); printf("                                  :*###*:             ");
	gotoxy(startCol, startRows++); printf("                                 =#######.            ");
	gotoxy(startCol, startRows++); printf("                               .=######*:             ");
	gotoxy(startCol, startRows++); printf("                               +######*:              ");
	gotoxy(startCol, startRows++); printf("                              *#######%s=-::.           ", BROWN);
	gotoxy(startCol, startRows++); printf("%s                             -#####*%s::=--::..        ", GRAY, BROWN);
	gotoxy(startCol, startRows++); printf("%s                               :+##.    %s:=--:::.      ", GRAY, BROWN);
	gotoxy(startCol, startRows++); printf("                                          .-=--:::.   ");
	gotoxy(startCol, startRows++); printf("                                             :---:::. ");
	gotoxy(startCol, startRows++); printf("                                               .-=--- ");
	gotoxy(startCol, startRows++); printf("                                                 .::  ");
	gotoxy(startCol, startRows++); printf("%s            .:::::::::::::::::::.  ", GRAY);
	gotoxy(startCol, startRows++); printf("  +*=::-===+*==================#.  ");
	gotoxy(startCol, startRows++); printf("   .+#######*################*+-   ");
	gotoxy(startCol, startRows++); printf("      .:-=*#############*-.        ");
	gotoxy(startCol, startRows++); printf("             :#########.           ");
	gotoxy(startCol, startRows++); printf("              -#######=            ");
	gotoxy(startCol, startRows++); printf("              *########.           ");
	gotoxy(startCol, startRows++); printf("          .-*###########*=.        ");
	gotoxy(startCol, startRows++); printf("         *##**==#####*=**###       ");
	gotoxy(startCol, startRows++); printf("         *#####=.   .-######       ", RESET);
}


void printVictoryBanner() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int startX = (columns - 104) / 2;
    int startY = 2;
    
	gotoxy(startX, startY++); printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.%s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\%s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /%s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / %s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s      _            .                   s                                            ..%s      %s/ /\\%s \n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s    u            @88>                :8                               ..          888B.%s   %s/ /\\ \\%s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s   88Nu.   u.    %%8P                .88           u.      .u    .    @L          48888E%s   %s\\ \\/ /%s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /%s   '88888.o888c    .          .     :888ooo  ...ue888b   .d88B :@8c  9888i   .dL  '8888'%s    %s\\/ / %s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s    ^8888  8888  .@88u   .udR88N  -*8888888  888R Y888r =\"8888f8888r `Y888k:*888.  Y88F%s     %s/ /\\ %s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s    8888  8888 ''888E` <888'888k   8888     888R I888>   4888>'88\"    888E  888I  '88%s     %s/ /\\ \\%s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s    8888  8888   888E  9888 'Y\"    8888     888R I888>   4888> '      888E  888I   8F%s     %s\\ \\/ /%s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /%s     8888  8888   888E  9888        8888     888R I888>   4888>        888E  888I   4%s       %s\\/ / %s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s    .8888b.888P   888E  9888       .8888Lu= u8888cJ888   .d888L .+     888E  888I   .%s       %s/ /\\ %s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s    ^Y8888*\"\"    888&  ?8888u../  ^%%888*    \"*888*P\"    ^\"8888*\"     x888N><888'  u8N.%s    %s/ /\\ \\%s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s      `Y\"        R888\"  \"8888P'     'Y\"       'Y\"          \"Y\"        \"88\"  888  \"*88%%%s    %s\\ \\/ /%s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /%s                   \"\"      \"P'                                               88F    \"\"%s      %s\\/ / %s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s                                                                            98\"%s             %s/ /\\ %s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s                                                                         ./\"%s              %s/ /\\ \\%s\n", LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s                                                                        ~`%s                %s\\ \\/ /%s\n", YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\\/ /\\ %s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\ /\\ \\%s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'  /%s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'` %s\n", YELLOW, RESET);

    printf("%s", RESET);
}

void printRewardsClaimedBanner() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int startX = (columns - 140) / 2;
    int startY = 2;

	gotoxy(startX+10, startY++); printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. %s\n", YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\%s\n", LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /%s\n", YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / %s\n", LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s / /\\%s                                                                          ..          .x+=:.     ..%s     %s/ /\\ %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s/ /\\ \\%s                            x=~                                        dF           z`    ^%%   888B.%s  %s/ /\\ \\%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s\\ \\/ /%s     .u    .               88x.   .e.   .e.                 .u    .   '88bu.           .   <k 48888E%s  %s\\ \\/ /%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s \\/ /%s    .d88B :@8c       .u    '8888X.x888:.x888        u      .d88B :@8c  '*88888bu      .@8Ned8\" '8888'%s   %s\\/ / %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s / /\\%s   =\"8888f8888r   ud8888.   `8888  888X '888k    us888u.  =\"8888f8888r   ^\"*8888N   .@^%%8888\"   Y88F%s    %s/ /\\ %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s/ /\\ \\%s    4888>'88\"  :888'8888.   X888  888X  888X .@88 \"8888\"   4888>'88\"   beWE \"888L x88:  `)8b.  '88%s    %s/ /\\ \\%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s\\ \\/ /%s    4888> '    d888 '88%%\"   X888  888X  888X 9888  9888    4888> '     888E  888E 8888N=*8888   8F%s    %s\\ \\/ /%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s \\/ /%s     4888>      8888.+\"      X888  888X  888X 9888  9888    4888>       888E  888E  %%8\"    R88   4%s      %s\\/ / %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s / /\\%s    .d888L .+   8888L       .X888  888X. 888~ 9888  9888   .d888L .+    888E  888F   @8Wou 9%%    .%s      %s/ /\\ %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s/ /\\ \\%s   ^\"8888*\"    '8888c. .+  `%%88%%``\"*888Y\"    9888  9888   ^\"8888*\"    .888N..888  .888888P`    u8N.%s   %s/ /\\ \\%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s\\ \\/ /%s      \"Y\"       \"88888%%      `~     `\"       \"888*\"\"888\"     \"Y\"       `\"888*\"\"   `   ^\"F     \"*88%%%s   %s\\ \\/ /%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s \\/ /%s                   \"YP'                        ^Y\"   ^Y'                   \"\"                    \"\"%s     %s\\/ / %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ %s\n", YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\%s\n", LYELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /`' / %s\n", YELLOW, RESET);
	gotoxy(startX+10, startY++); printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' %s\n", LYELLOW, RESET);
}

void printLoserBanner() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;


    int startX = (columns - 80) / 2; 
    int startY = 5;
    int i = 0;
    setColorLightRed();
    
	gotoxy(startX, startY + i++); printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. \n", LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\%s\n", YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /%s\n", LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / \n", YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\%s        ..                .x+=:.                             ..%s     %s/ /\\ %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\%s x .d88\"                z`    ^%%                           888B.%s  %s/ /\\ \\%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/ /%s  5888R          u.        .   <k               .u    .   48888E%s  %s\\ \\/ /%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /%s   '888R    ...ue888b     .@8Ned8\"      .u     .d88B :@8c  '8888'%s   %s\\/ / %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\%s    888R    888R Y888r  .@^%%8888\"    ud8888.  =\"8888f8888r  Y88F%s    %s/ /\\ %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\%s   888R    888R I888> x88:  `)8b. :888'8888.   4888>'88\"   '88%s    %s/ /\\ \\%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/ /%s   888R    888R I888> 8888N=*8888 d888 '88%%\"   4888> '      8F%s    %s\\ \\/ /%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /%s    888R    888R I888>  %%8\"    R88 8888.+\"      4888>        4%s      %s\\/ / %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\%s    888R   u8888cJ888    @8Wou 9%%  8888L       .d888L .+     .%s      %s/ /\\ %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\%s  .888B .  \"*888*P\"   .888888P`   '8888c. .+  ^\"8888*\"     u8N.%s   %s/ /\\ \\%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/ /%s  ^*888%%     'Y\"      `   ^\"F      \"88888%%       \"Y\"      \"*88%%%s   %s\\ \\/ /%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /%s     \"%%                               \"YP'                   \"\"%s     %s\\/ / %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ %s",  LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\\n", YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /\n", LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' \n", LYELLOW, RESET);	
	
    setColorDefault();	
}


void showLoseScreen() {
    clearScreen();
    displayBorder();
    
    printLoserBanner();

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int textY = 30;
    
    const char* promptPart1 = "Press ";
    const char* promptPart2 = "[ENTER]";
    const char* promptPart3 = " to return to the Main Menu...";

    int totalPromptWidth = strlen(promptPart1) + strlen(promptPart2) + strlen(promptPart3);
    int promptStartX = (columns - totalPromptWidth) / 2;

    gotoxy(promptStartX, textY);
    setColorWhite();
    printf("%s", promptPart1);
    
    setColorGreen();
    printf("%s", promptPart2);
    
    setColorWhite();
    printf("%s", promptPart3);
    
    setColorDefault();

    while (getch() != KEY_ENTER) {
    }
}

void printRewardSeparator_Top(int x, int y) {
    setColorBrightWhite();
    gotoxy(x, y);     printf("                                                  %s/\\", CYAN);
    gotoxy(x, y + 1); printf("%s __                                               %s\\/                                               %s__", LYELLOW, CYAN, LYELLOW);
    gotoxy(x, y + 2); printf("%s(_______________________________________________/\\/\\/\\_______________________________________________)", LYELLOW);
    setColorDefault();
}

void printRewardSeparator_Bottom(int x, int y) {
    setColorBrightWhite();
    gotoxy(x, y);     printf(" %s_______________________________________________      _______________________________________________", LYELLOW);
    gotoxy(x, y + 1); printf("%s(__                                             \\/\\/\\/                                             __)", LYELLOW);
    gotoxy(x, y + 2); printf("                                                  %s/\\", CYAN);
    gotoxy(x, y + 3); printf("                                                  %s\\/", CYAN);
    setColorDefault();
}

void printTreasureChest(int x, int y) {
    gotoxy(x, y++); printf("%s  __________", BROWN);
    gotoxy(x, y++); printf("%s /\\____%s;;%s___\\", BROWN, RESET, BROWN);
    gotoxy(x, y++); printf("%s |/         /", BROWN);
    gotoxy(x, y++); printf("%s `.%s ())%so%so%s() %s.", BROWN, YELLOW, BLUE, RED, YELLOW, BROWN);
    gotoxy(x, y++); printf("  %s|\\%s(%%%s()%s*^^%s()%s^\\", BROWN, YELLOW, GREEN, CYAN, YELLOW, BROWN);
    gotoxy(x, y++); printf(" %s%%%s| |-%s%%%s-------|", YELLOW, BROWN, YELLOW, BROWN);
    gotoxy(x, y++); printf("%s%% %s\\ |%s %%  %s))   %s|", YELLOW, BROWN, YELLOW, RESET, BROWN);
    gotoxy(x, y++); printf("%s%%  %s\\|%s%%%s________%s|", YELLOW, BROWN, YELLOW, BROWN, BROWN);
    gotoxy(x, y++); printf(" %s%%%%%%%s", YELLOW, RESET);
}

void showRewardScreen(Player *player, int depth, int type) {
    int goldEarned = 0;
    if (type == 2 || type == 3) { goldEarned = generateRandomRange(80, 100); } 
    else { goldEarned = (10 + (5 * depth)) + generateRandomRange(-3, 3); }
    player->gold += goldEarned;

    cardAddress cardChoices[3];
    int i;
    for (i = 0; i < 3; i++) {
        cardChoices[i] = generateRandomCard();
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int selectedIndex = 0;
    bool cardChosen = false;
    int key;

    while (!cardChosen) {
        clearScreen();
        displayBorder();
        
        int layoutWidth = 103;
        int layoutX = (columns - layoutWidth) / 2;
        int currentY = 2; 

        printVictoryBanner();
        currentY = 27;

        printRewardSeparator_Top(layoutX, currentY);
        currentY += 4;

        printTreasureChest(layoutX + (layoutWidth - 12) / 2, currentY);
        currentY += 10;

		char goldAmountStr[20];
		sprintf(goldAmountStr, "%d Gold!", goldEarned);
		const char* earnText = "You earned ";
		int goldTextTotalWidth = strlen(earnText) + strlen(goldAmountStr);
		
		gotoxy(layoutX + (layoutWidth - goldTextTotalWidth) / 2, currentY++);
		setColorWhite();
		printf("%s", earnText);
		setColorYellow();
		printf("%s", goldAmountStr);
		setColorDefault();
		currentY++;
		
		int panjangGaris = 95;
		int posisiXGaris = layoutX + (layoutWidth - panjangGaris) / 2;
		
		setColorLightYellow();
		gotoxy(posisiXGaris, currentY++);
		for(i = 0; i < panjangGaris; i++) printf("=");
		currentY++;

		const char* t1 = "Choose a ";
		const char* t2 = "card";
		const char* t3 = " to add to your ";
		const char* t4 = "deck:";
		int totalLen = strlen(t1) + strlen(t2) + strlen(t3) + strlen(t4);
		
		gotoxy(layoutX + (layoutWidth - totalLen) / 2, currentY++);
		setColorWhite(); printf("%s", t1);
		setColorCyan();  printf("%s", t2);
		setColorWhite(); printf("%s", t3);
		setColorGreen(); printf("%s", t4);
		setColorDefault();
		currentY += 2;

        int cardsTotalWidth = (18 * 3) + (7 * 2);
        int cardDisplayStartCol = layoutX + (layoutWidth - cardsTotalWidth) / 2;
        for (i = 0; i < 3; i++) {
            cardDeck singleCardDeck;
            initDeck(&singleCardDeck);
            deckHead(singleCardDeck) = cardChoices[i];
            deckTail(singleCardDeck) = cardChoices[i];
            currentCard(singleCardDeck) = (i == selectedIndex) ? cardChoices[i] : NULL;
            printDeck(singleCardDeck, cardDisplayStartCol + (i * 25), currentY);
        }
        currentY += 14;

        currentY += 2;

        const char* promptPart1 = "Use Left/Right Arrow to navigate. Press ";
        const char* promptPart2 = "[ENTER]";
        const char* promptPart3 = " to choose.";
        int totalPromptWidth = strlen(promptPart1) + strlen(promptPart2) + strlen(promptPart3);
        int promptStartX = layoutX + (layoutWidth - totalPromptWidth) / 2;

        gotoxy(promptStartX, currentY);
        setColorWhite(); printf("%s", promptPart1);
        setColorGreen(); printf("%s", promptPart2);
        setColorWhite(); printf("%s", promptPart3);
        setColorDefault();
        currentY++;
        
        currentY += 2;
        printRewardSeparator_Bottom(layoutX, currentY);
        
        key = getch();
        if (key == 224) {
            key = getch();
            playArrowBeep();
            if(key == KEY_LEFT) selectedIndex = (selectedIndex - 1 + 3) % 3;
            if(key == KEY_RIGHT) selectedIndex = (selectedIndex + 1) % 3;
        } else if (key == KEY_ENTER) {
            playEnterBeep();
            cardChosen = true;
        }
    }

    for (i = 0; i < 3; i++) {
        if (i == selectedIndex) pushDiscard(&(player->discard), cardChoices[i]);
        else freeCard(cardChoices[i]);
    }

    clearScreen();
    displayBorder();

    int layoutWidth = 140;
    int layoutX = (columns - layoutWidth) / 2;
    int currentY = 2;

    printRewardsClaimedBanner();
    currentY = 25; 

    int separatorWidth = 103;
    int separatorX = layoutX + (layoutWidth - separatorWidth) / 2;
    printRewardSeparator_Top(separatorX, currentY);

    int contentY = currentY + 3 + 3;
    int chestWidth = 12;
    int cardWidth = 18;
    int gap = 6;
    int totalContentWidth = chestWidth + gap + cardWidth;
    int contentStartX = layoutX + (layoutWidth - totalContentWidth) / 2;
    int chestX = contentStartX;
    int cardX = chestX + chestWidth + gap;
    
    printTreasureChest(chestX, contentY);
    cardAddress chosenCard = cardChoices[selectedIndex];
    cardDeck displayDeck;
    initDeck(&displayDeck);
    deckHead(displayDeck) = chosenCard;
    deckTail(displayDeck) = chosenCard;
    currentCard(displayDeck) = chosenCard;
    printDeck(displayDeck, cardX, contentY);

    int cardHeight = 13;
    int textY = contentY + cardHeight + 2;

    char goldInfoStr[50];
    sprintf(goldInfoStr, "You earned %d Gold.", goldEarned);
    int goldInfoWidth = strlen(goldInfoStr);
    gotoxy(layoutX + (layoutWidth - goldInfoWidth) / 2, textY++);
    setColorWhite();
    printf("You earned ");
    setColorYellow();
    printf("%d Gold.", goldEarned);
    setColorDefault();
    textY++;

    const char* textPart1 = "Card ";
    const char* textPart3 = " has been added to your deck!";
    char cardNameStr[50];
    sprintf(cardNameStr, "'%s'", cardName(chosenCard));
    int totalCardTextWidth = strlen(textPart1) + strlen(cardNameStr) + strlen(textPart3);
    int cardTextStartX = layoutX + (layoutWidth - totalCardTextWidth) / 2;
    gotoxy(cardTextStartX, textY++);
    setColorWhite(); printf("%s", textPart1);
    setColorCyan(); printf("%s", cardNameStr);
    setColorWhite(); printf("%s", textPart3);
    setColorDefault();
    textY += 2;

    const char* promptPart1_ = "Press ";
    const char* promptPart2_ = "[ENTER]";
    const char* promptPart3_ = " to return to the map...";
    int totalPromptWidth = strlen(promptPart1_) + strlen(promptPart2_) + strlen(promptPart3_);
    int promptStartX = layoutX + (layoutWidth - totalPromptWidth) / 2;
    gotoxy(promptStartX, textY++);
    setColorWhite(); printf("%s", promptPart1_);
    setColorGreen(); printf("%s", promptPart2_);
    setColorWhite(); printf("%s", promptPart3_);
    setColorDefault();
    
    int bottomSeparatorY = textY + 2;
    printRewardSeparator_Bottom(separatorX, bottomSeparatorY);

    while (getch() != KEY_ENTER) {
    }
}

void highlightLeft() {
	int length, startCol, startRow;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 47;
	startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 14;
	
	for (length = 0; length < 49; length++) {
		gotoxy(startCol + length, startRow); printf("=");
	}
	
	for (length = 0; length < 26; length++) {
		gotoxy(startCol, startRow); printf("||");
		gotoxy(startCol + 49, startRow ); printf("||");
		startRow++;
	}
	
	startRow--;
	for (length = 0; length < 49; length++) {
		gotoxy(startCol + length, startRow); printf("=");
	}
}

void highlightRight() {
	int length, startCol, startRow;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 + 5;
	startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 14;
	
	for (length = 1; length < 54; length++) {
		gotoxy(startCol + length, startRow); printf("=");
	}
	
	for (length = 0; length < 26; length++) {
		gotoxy(startCol, startRow); printf("||");
		gotoxy(startCol + 54, startRow ); printf("||");
		startRow++;
	}
	
	startRow--;
	for (length = 1; length < 54; length++) {
		gotoxy(startCol + length, startRow); printf("=");
	}
}

void skipLabel(const char* name){ //Size (33, 7)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 33;
	int startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 9;
	
	gotoxy(startCol, startRow++); printf("   //===========================");
	gotoxy(startCol, startRow++); printf("  //       Press [ESC] to		");
	gotoxy(startCol, startRow++); printf(" //  //====  ||// ||  ||>>\\\\	");
	gotoxy(startCol, startRow++); printf("<<   \\\\===\\\\ ||<< ||  ||>>//	");
	gotoxy(startCol, startRow++); printf(" \\   ====//  ||\\\\ ||  ||		");
	gotoxy(startCol, startRow++); printf("  \\ 	 %9s   	", name);
	gotoxy(startCol, startRow++); printf("   \\===========================");
}

void proceedLabel(){ //Size (33, 7)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 33;
	int startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 9;
	
	gotoxy(startCol, startRow++); printf("   //===========================");
	gotoxy(startCol, startRow++); printf("  //       Press [ESC] to		");
	gotoxy(startCol, startRow++); printf(" // |\\     __  __  __  __   __|");
	gotoxy(startCol, startRow++); printf("<<  |/ |~ | | |   |__ |__  |  |");
	gotoxy(startCol, startRow++); printf(" \\  |  |  |_| |__ |__ |__  |__|");
	gotoxy(startCol, startRow++); printf("  \\ 		            		");
	gotoxy(startCol, startRow++); printf("   \\===========================");
}
