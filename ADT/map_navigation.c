// map_navigation.c

#include "map_navigation.h"
#include "map_display.h"

void startNavigation(MapNode* mapRoot) {
    MapNode *currentNode, *selectedChild;
    int selectionIndex, keyPressed, i;
    boolean isGameRunning;

    if (mapRoot == Nil) {
        fprintf(stderr, "Error: Invalid map root node\n");
        return;
    }
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int navCol = columns / 2 - 20;
    int startRow = (rows - 20) / 2;
    int availableWidth = columns - 4;
    int startCol = 2 + (availableWidth - 70) / 2;
    if (startCol < 3) startCol = 3;
    if (startCol + 70 > columns - 3) startCol = columns - 73;
    int mapTitleCol = columns / 4 - 30;
    int mapTitleRow = 3; 
    
    
    currentNode = mapRoot;
    selectionIndex = 0;
    isGameRunning = TRUE;

    while (isGameRunning && currentNode != Nil) {
        boolean isNodeChosen = FALSE;
        currentNode->isVisited = TRUE;

        while (!isNodeChosen && isGameRunning && currentNode != Nil) {
            clearScreen();
            displayBorder();
            hideCursor();
            drawMapView(currentNode, selectionIndex);			
			
			mapTitleRow = 3;
			i = 1;
            gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("\033[1;33m     ...     ..      ..                                                                \033[1;31ms                                     ...                          .\033[1;33m                             \033[1;33m");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("   x*8888x.:*8888: -\"888:                                               oec :         \033[1;31m:8      .uef^\"                     .x888888hx    :                 @88>\033[1;33m                           ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("  X   48888X `8888H  8888                .d``                   u.     @88888        \033[1;31m.88    :d88E                       d88888888888hxx   .d``           %%8P      .u    .\033[1;33m               ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf(" X8x.  8888X  8888X  !888>        u      @8Ne.   .u       ...ue888b    8\"*88%%       \033[1;31m:888ooo `888E            .u        8\" ... `\"*8888%%`   @8Ne.   .u      .     .d88B :@8c       .u \033[1;33m    ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf(" X8888 X8888  88888   \"*8%%-    us888u.   %%8888:u@88N      888R Y888r   8b.        \033[1;31m-*8888888  888E .z8k    ud8888.     !  \"   ` .xnxx.     %%8888:u@88N   .@88u  =\"8888f8888r   ud8888.\033[1;33m   ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf(" '*888!X8888> X8888  xH8>   .@88 \"8888\"   `888I  888.     888R I888>  u888888>      \033[1;31m8888     888E~?888L :888'8888.    X X   .H8888888%%:    `888I  888. ''888E`   4888>'88\"  :888'8888.\033[1;33m  ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("   `?8 `8888  X888X X888>   9888  9888     888I  888I     888R I888>   8888R        \033[1;31m8888     888E  888E d888 '88%%\"    X 'hn8888888*\"   >    888I  888I   888E    4888> '    d888 '88%%\"\033[1;33m  ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("   -^  '888\"  X888  8888>   9888  9888     888I  888I     888R I888>   8888P        \033[1;31m8888     888E  888E 8888.+\"       X: `*88888%%`     !    888I  888I   888E    4888>      8888.+\"\033[1;33m     ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("    dx '88~x. !88~  8888>   9888  9888   uW888L  888'    u8888cJ888    *888>       \033[1;31m.8888Lu=  888E  888E 8888L         '8h.. ``     ..x8>  uW888L  888'   888E   .d888L .+   8888L\033[1;33m       ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("  .8888Xf.888x:!    X888X.: 9888  9888  '*88888Nu88P      \"*888*P\"     4888        \033[1;31m^%%888*    888E  888E '8888c. .+     `88888888888888f  '*88888Nu88P    888&   ^\"8888*\"    '8888c. .+\033[1;33m  ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf(" :\"\"888\":~\"888\"     `888*\"  \"888*\"\"888\" ~ '88888F`          'Y\"        '888          \033[1;31m'Y\"    m888N= 888>  \"88888%%        '%%8888888888*\"   ~ '88888F`      R888\"     \"Y\"       \"88888%%\033[1;33m    ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("     \"~'    \"~        \"\"     ^Y\"   ^Y'     888 ^                        88R                  \033[1;31m`Y\"   888     \"YP'            ^\"****\"\"`        888 ^         \"\"                   \"YP'\033[1;33m     ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("                                           *8E                          88>                       \033[1;31mJ88\"                                      *8E                                        \033[1;33m ");
			gotoxy(mapTitleCol, mapTitleRow + i); i++;
			printf("                                           '8>                          48                        \033[1;31m@%%                                        '8>                                         \033[1;33m");
			gotoxy(mapTitleCol, mapTitleRow + i); i++; i++; i++; i++;
			printf("                                            \"                           '8                      \033[1;31m:\"                                           \"                                          \033[0m");
			
			mapTitleRow = 7;
            gotoxy(navCol, mapTitleRow + i); i++; i++;
            printf("\033[1;31mCurrent Node\033[0m  =>  \033[1;33;41m[%s]\033[0m %s", NODE_TYPE_NAMES[currentNode->type], currentNode->name);
            gotoxy(navCol, mapTitleRow + i); i++;
            setColorDefault();
            printf("	\033[32mFloor %d, \033[31mDepth %d, \033[1;34mID:%d\033[0m", currentNode->floor, currentNode->depth, currentNode->id);

            gotoxy(navCol, mapTitleRow + i); i++;
            if (currentNode->type == NODE_BIG_BOSS) {
                setColorGreen();
                printf("?????? SELAMAT! Anda telah mencapai BIG BOSS! ??????");
                setColorDefault();
            	gotoxy(navCol, mapTitleRow + i); i++;
                printf("Tekan Enter untuk keluar...");
                while (_getch() != KEY_ENTER);
                isGameRunning = FALSE;
                break;
            }

            if (currentNode->numChildren == 0) {
                setColorRed();
                printf("Jalan buntu. Tidak ada jalan lagi dari sini.\n");
                setColorDefault();
                gotoxy(navCol, mapTitleRow + i); i++;
                printf("Tekan Enter untuk keluar...");
                while (_getch() != KEY_ENTER);
                isGameRunning = FALSE;
                break;
            }
			
	
			mapTitleRow = rows / 3 + 30;
			for (i = 20; i < columns - 18; i++){
				gotoxy(i, mapTitleRow); 
				printf("\033[1;31;41m=");
				gotoxy(i, mapTitleRow + 1); 
				printf("#"); 
				gotoxy(i, mapTitleRow + 2);
				printf("=\033[0m");
			}
			
			mapTitleRow = rows - 13;
			for (i = 20; i < columns - 18; i++){
				gotoxy(i, mapTitleRow); 
				printf("\033[1;31;41m=");
				gotoxy(i, mapTitleRow + 1); 
				printf("#"); 
				gotoxy(i, mapTitleRow + 2);
				printf("=\033[0m");
			}
			mapTitleRow = rows - 17;
			i = 0;
			gotoxy(navCol - 3, mapTitleRow + i); i++;
            printf("\033[1;33;108mNode Terpilih\033[0m    ==>");
            if (selectionIndex >= 0 && selectionIndex < currentNode->numChildren) {
                selectedChild = currentNode->children[selectionIndex];
                printf("    \033[1;33;41m[%s]\033[0m \033[1;31;40m%s", NODE_TYPE_NAMES[selectedChild->type], selectedChild->name);
                setColorDefault();
            } else {
                printf("(Tidak ada pilihan)");
            }
            

            keyPressed = _getch();

            if (keyPressed == 0 || keyPressed == 224) {
                keyPressed = _getch();
                if (currentNode->numChildren > 0) {
                    playArrowBeep();
                    switch (keyPressed) {
                        case KEY_LEFT:
                            selectionIndex = (selectionIndex - 1 + currentNode->numChildren) % currentNode->numChildren;
                            break;
                        case KEY_RIGHT:
                            selectionIndex = (selectionIndex + 1) % currentNode->numChildren;
                            break;
                        case 59: // F1
                            clearScreen();
                            gotoxy(0, 0);
                            printf("--- DEBUG: Map Structure ---\n");
                            printMapDebug(mapRoot, 0);
                            printf("--- END DEBUG ---\n");
                            printf("\nTekan Enter untuk kembali ke navigasi...");
                            while (_getch() != KEY_ENTER);
                            break;
                    }
                }
            } else {
                switch (keyPressed) {
                    case KEY_ENTER:
                        if (currentNode->numChildren > 0) {
                            playEnterBeep();
                            currentNode = currentNode->children[selectionIndex];
                            if (currentNode->type == NODE_ENEMY){
                            	inGame(startCol, startRow, 1, currentNode->depth);
							} else if (currentNode->type == NODE_SECONDARY_BOSS) {
                            	inGame(startCol, startRow, 2, currentNode->depth);								
							} else if (currentNode->type == NODE_BIG_BOSS) {
                            	inGame(startCol, startRow, 3, currentNode->depth);								
							} else if (currentNode->type == NODE_MERCHANT) {
                            	inGame(startCol, startRow, 4, currentNode->depth);																
							} else if (currentNode->type == NODE_REST) {
                            	inGame(startCol, startRow, 5, currentNode->depth);																
							}
                            selectionIndex = 0;
                            isNodeChosen = TRUE;
                        }
                        break;
                    case KEY_ESC:
                        clearScreen();
                        gotoxy(0, 10);
                        setColorRed();
                        printf("Anda memilih untuk mengakhiri simulasi.\n");
                        setColorDefault();
                        isGameRunning = FALSE;
                        Sleep(1000);
                        break;
                }
            }
            if (selectionIndex < 0 || selectionIndex >= currentNode->numChildren) {
                selectionIndex = 0;
            }
        }
    }
    setColorDefault();
}
