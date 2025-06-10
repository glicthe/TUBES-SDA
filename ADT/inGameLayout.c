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
			printDiscardIcon(); printDrawIcon();
		    printMobContainer(C, mobStatsCol, mobStatsRow);
		    printPlayerSprite(playerStatsCol, playerStatsRow);
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
	            case 'm':				//Untuk akses merchant sementara
					merchantScreen(&P, &deckInventory);
	            	break;
	            case 'c':				//Untuk akses rest sementara
					restScreen(&P, &deckInventory);
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

// Merchant
void merchantScreen(Player *player, cardDeck *inventory) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
	
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

		// Display card
	    int gap = 19;
	    for (row = 0; row < 2; row++) {
	        for (column = 0; column < 5; column++) {
	        	printCard(column, row, merchantCards[row][column]);
	        }
	    }

        // Display navigation
        for (row = 0; row < 2; row++) {
            for (column = 0; column < 5; column++) {
                if (row == currentRow && column == currentCol) {
                    // Position
                    printHand(column, row);
                    setColorBlue(); printCard(column, row, merchantCards[row][column]); setColorWhite();
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

void printMerchant(){//Size (34, 18)
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

void printHand(int column, int row){ //Size (24, 16)
	int startCol, startRow;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
	
	startCol = (startCol - 55) + 22 * column;
	startRow = (startRow - 29) + 15 * row;
	
	gotoxy(startCol, startRow++); printf(" %s.@<=)[{{}{}{]}}]@@=]-. ", BLUE);
	gotoxy(startCol, startRow++); printf(" .@-)~............)(@-. ");
	gotoxy(startCol, startRow++); printf(" .@@....:-:.-~~..*>-@.. ");
	gotoxy(startCol, startRow++); printf(" .:@-.......::~~~-=..@. ");
	gotoxy(startCol, startRow++); printf(" ...(@@<...>@@@@@@@..@. ");
	gotoxy(startCol, startRow++); printf(" %s.+@@@@@@@@@@@@@@@@@.@. ", CYAN);
	gotoxy(startCol, startRow++); printf(" .@@@###@@@@{#####(@.@. ");
	gotoxy(startCol, startRow++); printf(" .@@...::=.*.@@@@##@@.. ");
	gotoxy(startCol, startRow++); printf(" .{@@#######@@@@@@#@@.. ");
	gotoxy(startCol, startRow++); printf(" ..@@@@@-###@@##@@#@@{. ");
	gotoxy(startCol, startRow++); printf(" ...@@@@@@##@@@@#.@@@@. ");
	gotoxy(startCol, startRow++); printf(" ......@@@@@@@}..@@~... ");
	gotoxy(startCol, startRow++); printf(" ........{@@@..-@@..... ");
	gotoxy(startCol, startRow++); printf(" .........[@@.......... ");
	gotoxy(startCol, startRow++); printf(" .........(@@.......... ");
	gotoxy(startCol, startRow++); printf(" .........[@*..........%s ", RESET);
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

void printCard(int column, int row, Card *shopCard){//Size (22, 12)
	int length, startCol, startRow;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	startRow = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
	
	startCol = (startCol - 55) + 22 * column;
	startRow = (startRow - 13) + 15 * row;
	gotoxy(startCol, startRow++); printf(" .==================. ");
	for (length = 0; length < 10; length++) {
		gotoxy(startCol, startRow++); printf(" .||              ||. ");
	}
	gotoxy(startCol, startRow++); printf(" .==================. ");
}

//Rest Site
void restScreen(Player *player, cardDeck *deck) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int columns = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	bool exitRestSite = false;
	bool chooseHeal = true;
	bool isResting = false;
	
//    gotoxy(startCol, 21); printf("HP: %d/%d\n", player->health, MAX_PLAYER_HEALTH);	
    
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
			highlightLeft();
		} else {
			highlightRight();
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
					//upgradeCard(deck, index);
	                isResting = true;
	            } else {
			        int heal = (MAX_PLAYER_HEALTH - player->health) * 0.3;  //heal berdasarkan 30% hp yang hilang
			        gainHP(player, heal);
	                isResting = true;
	            }
	        } else {
	    	    gotoxy(columns - 2, rows + 16);
				setColorRed(); printf("You have bought it ALREADY!");  setColorWhite();
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
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 - 46;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 13;
	gotoxy(startCol, startRows++); printf("                            .:--::.              ");
	gotoxy(startCol, startRows++); printf("                      .*:.*#########*=.          ");
	gotoxy(startCol, startRows++); printf("                       +*###############-.       ");
	gotoxy(startCol, startRows++); printf("                       +#=::--==+*########+.  :. ");
	gotoxy(startCol, startRows++); printf("                  ..  .=:........::..::+####+:*- ");
	gotoxy(startCol, startRows++); printf("                    .--:........::.........+##*: ");
	gotoxy(startCol, startRows++); printf("                 .......::..:...-..........-###: ");
	gotoxy(startCol, startRows++); printf("               .-==-:.........:::--........=++*: ");
	gotoxy(startCol, startRows++); printf("             .===========-:..........::...--==*: ");
	gotoxy(startCol, startRows++); printf("          .:===================::.......:--===*- ");
	gotoxy(startCol, startRows++); printf("        .-=========================-:....::--=#- ");
	gotoxy(startCol, startRows++); printf("      .-===============================-..:---*- ");
	gotoxy(startCol, startRows++); printf("=#+..:===============================++-..:. .*= ");
	gotoxy(startCol, startRows++); printf(".#=-*########**+===================++===...      ");
	gotoxy(startCol, startRows++); printf(".################*===============++=====..       ");
	gotoxy(startCol, startRows++); printf(".##################*+==========++=====-.         ");
	gotoxy(startCol, startRows++); printf(":####################*==*#*==++=====-.           ");
	gotoxy(startCol, startRows++); printf(":######################++#*=+=====-.             ");
	gotoxy(startCol, startRows++); printf(":#########################*======:.              ");
	gotoxy(startCol, startRows++); printf(":#=  :+*##################*====:                 ");
	gotoxy(startCol, startRows++); printf("         .-+*#############*==-.                  ");
	gotoxy(startCol, startRows++); printf("             ..-+#########*=:.                   ");
	gotoxy(startCol, startRows++); printf("                    :=*####.                     ");
	gotoxy(startCol, startRows++); printf("                        :*#                      ");
}

void printSmith() { //Size (44, 24)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int startCol = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2 + 6;
	int startRows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2 - 13;
	gotoxy(startCol, startRows++); printf("                                   .-:.               ");
	gotoxy(startCol, startRows++); printf("                                  :*###*:             ");
	gotoxy(startCol, startRows++); printf("                                 =#######.            ");
	gotoxy(startCol, startRows++); printf("                               .=######*:             ");
	gotoxy(startCol, startRows++); printf("                               +######*:              ");
	gotoxy(startCol, startRows++); printf("                              *#######=-::.           ");
	gotoxy(startCol, startRows++); printf("                             -#####*: :=--::..        ");
	gotoxy(startCol, startRows++); printf("                               :+##.    :=--:::.      ");
	gotoxy(startCol, startRows++); printf("                                          .-=--:::.   ");
	gotoxy(startCol, startRows++); printf("                                             :---:::. ");
	gotoxy(startCol, startRows++); printf("                                               .-=--- ");
	gotoxy(startCol, startRows++); printf("                                                 .::  ");
	gotoxy(startCol, startRows++); printf("            .:::::::::::::::::::.                     ");
	gotoxy(startCol, startRows++); printf("  +*=::-===+*==================#.  ");
	gotoxy(startCol, startRows++); printf("   .+#######*################*+-   ");
	gotoxy(startCol, startRows++); printf("      .:-=*#############*-.        ");
	gotoxy(startCol, startRows++); printf("             :#########.           ");
	gotoxy(startCol, startRows++); printf("              -#######=            ");
	gotoxy(startCol, startRows++); printf("              *########.           ");
	gotoxy(startCol, startRows++); printf("          .-*###########*=.        ");
	gotoxy(startCol, startRows++); printf("         *##**==#####*=**###       ");
	gotoxy(startCol, startRows++); printf("         *#####=.   .-#####%       ");
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

