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
// 			restScreen(startCol, &P, &deckInventory);
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
	            case 'm':				//Untuk akses merchant sementara
	            	merchantScreen(startCol, startRow, &P, &deckInventory);
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
void merchantScreen(int startCol, int startRow, Player *player, cardDeck *inventory) {
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
    int exitMerchant = 0;

    while (!exitMerchant) {
    	clearScreen();
    	displayBorder();
    	printMerchant(startCol * 2 * 1.2, startRow);
        printf("Gold: %d\n\n", player->gold);

		// Display card
	    int gap = 19;
	    for (row = 0; row < 2; row++) {
	        for (column = 0; column < 5; column++) {
	        	printCard((columns - 55) + 22 * column, (rows - 13) + 15 * row, merchantCards[row][column]);
	        }
	    }

        // Display navigation
        for (row = 0; row < 2; row++) {
            for (column = 0; column < 5; column++) {
                if (row == currentRow && column == currentCol) {
                    // Position
                    printHand((columns - 55) + 22 * column, (rows - 29) + 15 * row);
                    setColorBlue(); printCard((columns - 55) + 22 * column, (rows - 13) + 15 * row, merchantCards[row][column]); setColorWhite();
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
        printf("\nUse arrow keys to move, ENTER to buy, ESC to exit.\n");

        int ch = getch();
        if (ch == 224) {
            ch = getch();
            switch (ch) {
                case KEY_UP:
                    currentRow = (currentRow == 0) ? 1 : 0;
                    break;
                case KEY_DOWN:
                    currentRow = (currentRow == 1) ? 0 : 1;
                    break;
                case KEY_LEFT:
                    currentCol = (currentCol == 0) ? 4 : currentCol - 1;
                    break;
                case KEY_RIGHT:
                    currentCol = (currentCol == 4) ? 0 : currentCol + 1;
                    break;
            }
        } else if (ch == KEY_ENTER) {
        	cardAddress selected = merchantCards[currentRow][currentCol];
        	if (selected != Nil) {
	            int price = prices[currentRow][currentCol];
	            if (player->gold >= price) {
	                addCardToDeck(inventory, selected);
	                player->gold -= price;
	                printf("\nYou bought %s!\n", cardName(selected));
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
            exitMerchant = 1;
            // Generate cards and their prices
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

void printMerchant(int startCol, int startRow){
	int i = 1;
	gotoxy(startCol, startRow + i); i++; printf("            %s+++++##               ", BLUE);
	gotoxy(startCol, startRow + i); i++; printf("          +%s-+%s----%s+###             ", RED, RESET, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("          +%s++%s-----%s+###            ", RED, RESET, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("           +%s-----%s++%s#####          ", RESET, CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("           #+++++###              ");
	gotoxy(startCol, startRow + i); i++; printf("          #+###++##               ");
	gotoxy(startCol, startRow + i); i++; printf("         ++############           ");
	gotoxy(startCol, startRow + i); i++; printf("         ++++###++##++#           ");
	gotoxy(startCol, startRow + i); i++; printf("         +++++####++++##          ");
	gotoxy(startCol, startRow + i); i++; printf("         ####+++#+++#####         ");
	gotoxy(startCol, startRow + i); i++; printf("     %s++++%s######%s+++%s#########       ", CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("     %s+++++%s###########%s++++%s###      ", CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("    %s+++++-++%s########%s++++++%s###     ", CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("   #%s+++%s#%s++---++%s#####%s++-++%s#######  ", CYAN, BLUE, CYAN, BLUE, CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("##############%s++++%s################", CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("  #############%s++%s##########       ", CYAN, BLUE);
	gotoxy(startCol, startRow + i); i++; printf("          ##%sMERCHANT%s## %s           ", RESET, BLUE, RESET);
}

void printHand(int startCol, int startRow){
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

void printCard(int startCol, int startRow, Card *shopCard){
	int length;
	gotoxy(startCol, startRow++); printf(" .==================. ");
	for (length = 0; length < 10; length++) {
		gotoxy(startCol, startRow++); printf(" .||              ||. ");
	}
	gotoxy(startCol, startRow++); printf(" .==================. ");
}

//Rest Area
void restScreen(int startCol, Player *player, cardDeck *deck) {
    gotoxy(startCol, 2); printf("=== Rest Site ===\n");
    gotoxy(startCol, 21); printf("HP: %d/%d\n", player->health, MAX_PLAYER_HEALTH);
    gotoxy(startCol, 22); printf("1. Rest (Recover 30% lost HP)\n");
    gotoxy(startCol, 23); printf("2. Smith (Upgrade a card)\n");
    gotoxy(startCol, 26); printf("Choose: ");	
	
	//Selection
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        int heal = (MAX_PLAYER_HEALTH - player->health) * 0.3;  //heal berdasarkan 30% hp yang hilang
        player->health += heal;
        if (player->health > MAX_PLAYER_HEALTH) {
            player->health = MAX_PLAYER_HEALTH;
        }
        gotoxy(startCol, 31); printf("You rest and recover %d lost HP.\n", heal);
    } else if (choice == 2) {
        gotoxy(startCol, 32); printf("Available cards to upgrade:\n");
        printDeck(player->hand, 10, 20); 
        gotoxy(startCol, 33); printf("Choose card index to upgrade: ");
        int index;
        scanf("%d", &index);
//      upgradeCard(deck, index);
    } else {
        printf("Invalid choice.\n");
    }
}

void campFire() {
	int startCol = 0;
    gotoxy(startCol, 33); printf("                                                             ");
    gotoxy(startCol, 33); printf("                          =@@                                ");
    gotoxy(startCol, 33); printf("                         @@@%%                               ");
    gotoxy(startCol, 33); printf("                         @@*%@  @@                           ");
    gotoxy(startCol, 33); printf("                          -@*@.+@@@                          ");
    gotoxy(startCol, 33); printf("                           =@+#@*+@@                         ");
    gotoxy(startCol, 33); printf("                        *  %@-=+=-*@     ..                  ");
    gotoxy(startCol, 33); printf("                      @@@@ %@=%%:.*@@    @@                  ");
    gotoxy(startCol, 33); printf("                     =@@#  =@ :# =*@@   %%@@@                ");
    gotoxy(startCol, 33); printf("                    @@**# #@*+ : +*@@  *@*@@                 ");
    gotoxy(startCol, 33); printf("                    +@.*@..@= :=.##@* +@*+@@                 ");
    gotoxy(startCol, 33); printf("                    @@+-*@@*.-+=:.-*@-:@-@=                  ");
    gotoxy(startCol, 33); printf("                     :@*#*= =:.*= =%%###**@                  ");
    gotoxy(startCol, 33); printf("                      @*.-%%.+  **:%%:@=:@@                  ");
    gotoxy(startCol, 33); printf("                @@@@  :@: .=.  :*=:. #= @@                   ");
    gotoxy(startCol, 33); printf("                +@*@@ +@#:**%%+  :%%%#  =@- @@@              ");
    gotoxy(startCol, 33); printf("                -@:#=:@*.#. %% -    ==   ##@@*@=             ");
    gotoxy(startCol, 33); printf("               :@#:.###..  .%%+.. :   -*.=#*-*@@             ");
    gotoxy(startCol, 33); printf("              %%@#+  *%%::  *@* :: .=.+%%+- #- +%%:          ");
    gotoxy(startCol, 33); printf("             .@#-.-=-=#*  .  ::     =%%++=#=+%%#@@           ");
    gotoxy(startCol, 33); printf("            -@*%%*:..*+:  .---.::. .: -%%. : -#=@@           ");
    gotoxy(startCol, 33); printf("            %%@== +. +%%+  .-::.  :==.  +*  :-+#+@@          ");
    gotoxy(startCol, 33); printf("            #@-= +: .%%%% .  -:   --. .:.   -:=*@%%          ");
    gotoxy(startCol, 33); printf("            #@*#= :   .-=:         -+=.   :.-*@@             ");
    gotoxy(startCol, 33); printf("              @***:-   .=-+-    :*+-:.    ..*@               ");
    gotoxy(startCol, 33); printf("   @@@@@@@@@@@@@@*-   .                 .=*@@@@@@@@@@@@@@    ");
    gotoxy(startCol, 33); printf(" @@    +        -@@@%%    .          .  %%@@@-        =  @@  ");
    gotoxy(startCol, 33); printf(" #@ =*  %%+*@@@@@*.  +@#  :@@@@@@@@*  #@*   *@@@@@*+#  *= @@ ");
    gotoxy(startCol, 33); printf(" @@ .   *@@    #+=++##*@@@%%+=:::-#@@@###+===#:   @@*   . @@ ");
    gotoxy(startCol, 33); printf("   @@@@@@@      #@%%#@@@@=@@@@@@@%%*@@@@*%%@%%      %%@@@@@@ ");
    gotoxy(startCol, 33); printf("        =@   .%%#  %%@* .@+        +@* :@@%%  #%%:   @@      ");
    gotoxy(startCol, 33); printf("         *@*     .@@   @@  -##*=.- %%@   #@-     +@@         ");
    gotoxy(startCol, 33); printf("           %%@@@@@@     @@   :  =  .@@     @@@@@@@           ");
    gotoxy(startCol, 33); printf("                         @@+###*@@@                          ");
}


