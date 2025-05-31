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
	initDeckInventoryToHand(&deckInventory, &P.hand);
	
    int selectedIndex = 0;
    int key;
    int running = 1;

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
	int inHandCol = startCol - 45; 
	int inHandRow = rows - startRow + 1; 
	
	while (running) {
		clearScreen();
		displayBorder();
		
		headBar(startCol, columns, P); 
		battleScreen(battleScreenCol, battleScreenRow, columns, rows); 
	    printMobContainer(C, mobStatsCol, mobStatsRow);
	    printPlayerStatus(P, playerStatsCol, playerStatsRow);
	    
	    printDeck(P.hand, inHandCol, inHandRow);
	    printCurrentCard(P.hand, playerStatsCol, playerStatsRow);
	    
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
	            }
	            break;
            case KEY_ENTER:
            	playEnterBeep();
            	playCard(&P, &deckInventory);
            	break;
            case 'h':
            	playEnterBeep();
            	executeMenuAction(4);
            	break;
	    	case 'q':
	    		playEnterBeep();
	    		SplashScreen();
	    		running = 0;
                break;
		} 
	} 
	
    
}

void headBar(int startCol, int max, Player P){
	int i, headBarRow = 3;
	int headBarCol = 2;;
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
	printf("============");
	gotoxy(startCol + 31, headBarRow + 3);
	setColorBrightWhite();
    printf("WHO'S TURN");
    gotoxy(startCol + 30, headBarRow + 4);
    setColorBrightWhite();
	printf("============");
    
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
