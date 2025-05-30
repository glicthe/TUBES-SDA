#include "inGameLayout.h"

void inGame(int startCol, int startRow){
	// initiate
	setColorDefault;
    mobContainer C;
    cardDeck deckInventory;
    cardDeck deckInHand;
    Player P = createPlayer();

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int i, columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int mobStatsCol = startCol + 117;
	int mobStatsRow = (startRow / 2);
	int playerStatsCol = startCol - 77;
	int playerStatsRow = (startRow / 2);
	
	clearScreen();
	displayBorder();
	
	headBar(startCol, columns, P); 
    initDeck(&deckInventory);
    initDeck(&deckInHand);
    
    /*
    starterDeckInventory(&D);
    initDeckInventoryToHand(deckInventory, &deckInHand);
	*/
    
    
	createMobContainer(&C);
    randGenerateMob(&C);
    printMobContainer(C, mobStatsCol, mobStatsRow);
    printPlayerStatus(P, playerStatsCol, playerStatsRow);
    
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
    printf("[E] EXIT!");
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

void playerCardInHand(){
	
}
