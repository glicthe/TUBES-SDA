#include "menu.h"

void displayMenu(MenuItem menu[], int menuSize, int selectedIndex) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    clearScreen();

    displayBorder();
    displayGameTitle();

    int menuWidth = 40; 
    int textWidth = 38;
    int startRow = 28;
    int startCol = (columns - menuWidth) / 2;

    if (startCol < 3) startCol = 3;
    if (startCol + menuWidth > columns - 3) startCol = columns - menuWidth - 3;


    const int FRAME_COLOR_ATTR = COLOR_RED;
    const int HEADER_FRAME_ATTR = (COLOR_BLACK * 16) + COLOR_LIGHT_YELLOW;
    const int HEADER_TEXT_BG_ATTR = (COLOR_RED * 16) + COLOR_LIGHT_YELLOW;
    const int INSTRUCTION_KEY_ATTR = COLOR_LIGHT_RED;
    const int INSTRUCTION_NORMAL_TEXT_ATTR = COLOR_WHITE;
    const int ITEM_NORMAL_TEXT_ATTR = COLOR_WHITE;
    const int ITEM_SELECTED_ATTR = (COLOR_LIGHT_YELLOW * 16) + COLOR_BLACK;
    const int STATUS_LITERAL_ATTR = (COLOR_BLACK * 16) + COLOR_WHITE; 
    const int STATUS_ITEMNAME_ATTR = (COLOR_BLACK * 16) + COLOR_LIGHT_RED;
    const int DECORATION_STAR_ATTR = COLOR_GREEN;    
    const int DECORATION_SLASH_ATTR = COLOR_MAGENTA;    
    const int INSTRUCTION_LOWER_BORDER_ATTR = HEADER_FRAME_ATTR;
    const int BLACK_BG_WHITE_FG_FOR_PADDING = (COLOR_BLACK * 16) + COLOR_WHITE;


    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, startRow);
    printf("+======================================+");

    gotoxy(startCol, startRow + 1);
    setTextColor(HEADER_TEXT_BG_ATTR);
    printf("|            -= MAIN MENU =-           |");

    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, startRow + 2);
    printf("+======================================+");

    gotoxy(startCol, startRow + 3);
    setTextColor(FRAME_COLOR_ATTR); printf("|");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("      Use     ");
    setTextColor(FRAME_COLOR_ATTR); printf("|");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("   - ");
    setTextColor(INSTRUCTION_KEY_ATTR); printf("ENTER");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf(" to Select   ");
    setTextColor(FRAME_COLOR_ATTR); printf("|");

    gotoxy(startCol, startRow + 4);
    setTextColor(FRAME_COLOR_ATTR); printf("|");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("    ");
    setTextColor(INSTRUCTION_KEY_ATTR); printf("UP/DOWN");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("   ");
    setTextColor(FRAME_COLOR_ATTR); printf("|");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("   - ");
    setTextColor(INSTRUCTION_KEY_ATTR); printf("ESC");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf(" to Exit       ");
    setTextColor(FRAME_COLOR_ATTR); printf("|");

    gotoxy(startCol, startRow + 5);
    setTextColor(FRAME_COLOR_ATTR); printf("|");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("  To Navigate ");
    setTextColor(FRAME_COLOR_ATTR); printf("|");
    setTextColor(INSTRUCTION_NORMAL_TEXT_ATTR); printf("                       ");
    setTextColor(FRAME_COLOR_ATTR); printf("|");

    setTextColor(INSTRUCTION_LOWER_BORDER_ATTR);
    gotoxy(startCol, startRow + 6);
    printf("+======================================+");

    setTextColor(FRAME_COLOR_ATTR);
    gotoxy(startCol, startRow + 7);
    printf("+======================================+");

    int i;
    for (i = 0; i < menuSize; i++) {
        gotoxy(startCol, startRow + 8 + i);
        if (i == selectedIndex) {
            setTextColor(ITEM_SELECTED_ATTR);
            printf("|          >> %-18s       |", menu[i].text);
        } else {
            setTextColor(FRAME_COLOR_ATTR); printf("|");
            setTextColor(ITEM_NORMAL_TEXT_ATTR);
            printf("             %-18s       ", menu[i].text);
            setTextColor(FRAME_COLOR_ATTR); printf("|");
        }
    }

    setTextColor(FRAME_COLOR_ATTR);
    gotoxy(startCol, startRow + 8 + menuSize);
    printf("+======================================+");

    int statusBoxY = startRow + 9 + menuSize;

    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, statusBoxY);
    printf("+======================================+");

    gotoxy(startCol, statusBoxY + 1);
    char selectedItemText[50];
    strcpy(selectedItemText, menu[selectedIndex].text);

    char statusLiteral[] = "Selected: ";
    int statusLiteralLen = strlen(statusLiteral);
    int selectedItemTextLen = strlen(selectedItemText);
    int totalTextLen = statusLiteralLen + selectedItemTextLen;
    int statusPadding = (textWidth - totalTextLen) / 2;
    if (statusPadding < 0) statusPadding = 0;

    setTextColor(HEADER_FRAME_ATTR); printf("|");

    int k;
    for(k=0; k < statusPadding; ++k) { printf(" "); }

    setTextColor(STATUS_LITERAL_ATTR);
    printf("%s", statusLiteral);

    setTextColor(STATUS_ITEMNAME_ATTR);
    printf("%s", selectedItemText);

    int remainingSpaces = textWidth - totalTextLen - statusPadding;
    for(k=0; k < remainingSpaces; ++k) { printf(" "); }

    setTextColor(HEADER_FRAME_ATTR); printf("|");

    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, statusBoxY + 2);
    printf("+======================================+");
    


    if (startCol >= 13) {
        gotoxy(startCol - 8, startRow + 2);
        setTextColor(DECORATION_STAR_ATTR); // <*> Hijau Tua
        printf("  <*>");
        gotoxy(startCol - 8, startRow + 6);
        setTextColor(DECORATION_SLASH_ATTR); // /|\ Magenta
        printf("  /|\\");
    }

    if (startCol + menuWidth + 8 < columns - 3) {
        gotoxy(startCol + menuWidth + 3, startRow + 2);
        setTextColor(DECORATION_STAR_ATTR); // <*> Hijau Tua
        printf("<*>  ");
        gotoxy(startCol + menuWidth + 3, startRow + 6);
        setTextColor(DECORATION_SLASH_ATTR); // /|\ Magenta
        printf("/|\\  ");
    }

    setColorDefault();
}

void executeMenuAction(int menuId) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    int startRow = (rows - 20) / 2;
    int availableWidth = columns - 4;
    int startCol = 2 + (availableWidth - 70) / 2;
    
    if (startCol < 3) startCol = 3;
    if (startCol + 70 > columns - 3) startCol = columns - 73;
    
    clearScreen();
    displayBorder();
    
    setColorDefault();
    
    switch (menuId) {
        case 1:
            showLoading("Starting New Game...");
            clearScreen();
            displayBorder();
            gotoxy(startCol, startRow);
            setColorLightGreen();
            printf("+=================================================================+");
            gotoxy(startCol, startRow + 1);
            printf("|                        NEW GAME STARTED                         |");
            gotoxy(startCol, startRow + 2);
            printf("+=================================================================+");
            setColorDefault();
            gotoxy(startCol, startRow + 4);
            printf("  Welcome to the dungeon, brave adventurer!");
            gotoxy(startCol, startRow + 5);
            printf("  You start with a basic deck of cards...");
            gotoxy(startCol, startRow + 6);
            printf("  Choose your path wisely and build your deck strategically!");
            Sleep(2000);
            startGame();
            break;
            
        case 2:
            showLoading("Loading Saved Game...");
            clearScreen();
            displayBorder();
            gotoxy(startCol, startRow);
            setColorLightYellow();
            printf("+=================================================================+");
            gotoxy(startCol, startRow + 1);
            printf("|                        LOAD GAME                                |");
            gotoxy(startCol, startRow + 2);
            printf("+=================================================================+");
            setColorDefault();
            gotoxy(startCol, startRow + 4);
            printf("  Searching for saved game files...");
            gotoxy(startCol, startRow + 5);
            setColorLightRed();
            printf("  [No saved games found]");
            setColorDefault();
            gotoxy(startCol, startRow + 6);
            printf("  Start a new game to create a save file!");
            break;
            
        case 3:
            howToPlay();
            break;
            
        case 4:
            clearScreen();
            displayBorder();
            gotoxy(startCol, startRow);
            setColorLightYellow();
            printf("+=================================================================+");
            gotoxy(startCol, startRow + 1);
            printf("|                          CREDITS                                |");
            gotoxy(startCol, startRow + 2);
            printf("+=================================================================+");
            setColorDefault();
            gotoxy(startCol, startRow + 4);
            printf("  Roguelike Turn-Based Deck Building Game");
            gotoxy(startCol, startRow + 5);
            printf("  Version 1.0");
            gotoxy(startCol, startRow + 7);
            printf("  Developed with passion using C programming language");
            gotoxy(startCol, startRow + 9);
            setColorLightGreen();
            printf("  Thank you for playing!");
            setColorDefault();
            break;
    }
    
    gotoxy(startCol, startRow + 12);
    setColorLightYellow();
    printf("  Press ENTER to return to main menu...");
    setColorDefault();
    
    while (getch() != KEY_ENTER);
}

void SplashScreen() {
    Sleep(800);
    
    MenuItem menu[] = {
        {"New Game", 1},
        {"Load Game", 2},
        {"How To Play", 3},
        {"Credits", 4},
        {"Exit Game", 5}
    };
    
    int menuSize = sizeof(menu) / sizeof(menu[0]);
    int selectedIndex = 0;
    int key;
    int running = 1;
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 0;
    int rows = 0;
    
    hideCursor();
    
    while (1) {
        clearScreen();
        displayBorder();
        displayGameTitle();
        
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        
        int availableWidth = columns - 4;
        int promptStartCol = 2 + (availableWidth - 40) / 2;

        gotoxy(promptStartCol, 30);
        setColorLightYellow();
        printf("Press ENTER to continue...");
        setColorDefault();
        
        key = getch();
        if (key == KEY_ENTER) {
            playEnterBeep();
            break;
        }
    }
    
    while (running) {
        displayMenu(menu, menuSize, selectedIndex);
        
    	key = getch();
        
        if (key == 224) {
            key = getch();
            
            switch (key) {
                case KEY_UP:
                    playArrowBeep();
                    selectedIndex--;
                    if (selectedIndex < 0) selectedIndex = menuSize - 1;
                    break;
                    
                case KEY_DOWN:
                    playArrowBeep();
                    selectedIndex++;
                    if (selectedIndex >= menuSize) selectedIndex = 0;
                    break;
            }
        }
        else if (key == KEY_ENTER) {
            playEnterBeep();
            if (menu[selectedIndex].id == 5) {
                clearScreen();
                displayBorder();
                
                GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
                columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                
                int availableWidth = columns - 4;
                int startRow = (rows - 8) / 2;
                int startCol = 2 + (availableWidth - 50) / 2;
                
                setColorLightRed();
                gotoxy(startCol, startRow);
                printf("+================================================+");
                gotoxy(startCol, startRow + 1);
                printf("|                                                |");
                gotoxy(startCol, startRow + 2);
                printf("|         Thank you for playing our game!        |");
                gotoxy(startCol, startRow + 3);
                printf("|                See you next time!              |");
                gotoxy(startCol, startRow + 4);
                printf("|                                                |");
                gotoxy(startCol, startRow + 5);
                printf("+================================================+");
                setColorDefault();
                
                Sleep(2000);
                running = 0;
                break;
            } else {
                executeMenuAction(menu[selectedIndex].id);
            }
        }
        else if (key == KEY_ESC) {
            playEnterBeep();
            clearScreen();
            displayBorder();
            
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            
            int availableWidth = columns - 4;
            int startRow = rows / 3;
            int startCol = 2 + (availableWidth - 40) / 2;
            
            setColorLightRed();
            gotoxy(startCol, startRow);
            printf("+================================================+");
            gotoxy(startCol, startRow + 1);
            printf("|                                                |");
            gotoxy(startCol, startRow + 2);
            printf("|                    Thank you                   |");
            gotoxy(startCol, startRow + 3);
            printf("|                See you next time!              |");
            gotoxy(startCol, startRow + 4);
            printf("|                                                |");
            gotoxy(startCol, startRow + 5);
            printf("+================================================+");
            setColorDefault();
            Sleep(1500);
            running = 0;
            break;
        }
    }
}

void howToPlay() {
	clearScreen();
	displayBorder();
	int columns, rows, startCol, startRow, i;
	int currentPage = 1; // Track which page we're on
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	while (1) {
		if (currentPage == 1) {
			clearScreen();
			displayBorder();
			
			startCol = columns / 3 - 12;
			startRow = rows / 4 - 15;
			i = 1;
			gotoxy(startCol, startRow + i); i++;
			printf("\033[1;31m                                      ..             ..                            ");
			gotoxy(startCol, startRow + i); i++;
			printf("  .uef^\"                            dF         . uW8\"                              ");
			gotoxy(startCol, startRow + i); i++;
			printf(":d88E                              '88bu.      `t888                      .u    .  ");
			gotoxy(startCol, startRow + i); i++;
			printf("`888E            .u          u     '*88888bu    8888   .         u      .d88B :@8c ");
			gotoxy(startCol, startRow + i); i++;
			printf(" 888E .z8k    ud8888.     us888u.    ^\"*8888N   9888.z88N     us888u.  =\"8888f8888r");
			gotoxy(startCol, startRow + i); i++;
			printf(" 888E~?888L :888'8888. .@88 \"8888\"  beWE \"888L  9888  888E .@88 \"8888\"   4888>'88\" ");
			gotoxy(startCol, startRow + i); i++;
			printf(" 888E  888E d888 '88%%\" 9888  9888   888E  888E  9888  888E 9888  9888    4888> '   ");
			gotoxy(startCol, startRow + i); i++;
			printf(" 888E  888E 8888.+\"    9888  9888   888E  888E  9888  888E 9888  9888    4888>     ");
			gotoxy(startCol, startRow + i); i++;
			printf(" 888E  888E 8888L      9888  9888   888E  888F  9888  888E 9888  9888   .d888L .+  ");
			gotoxy(startCol, startRow + i); i++;
			printf(" 888E  888E '8888c. .+ 9888  9888  .888N..888  .8888  888\" 9888  9888   ^\"8888*\"   ");
			gotoxy(startCol, startRow + i); i++;
			printf("m888N= 888>  \"88888%%   \"888*\"\"888\"  `\"888*\"\"    `%%888*%%\"   \"888*\"\"888\"     \"Y\"     ");
			gotoxy(startCol, startRow + i); i++;
			printf(" `Y\"   888     \"YP'     ^Y\"   ^Y'      \"\"          \"`       ^Y\"   ^Y'              ");
			gotoxy(startCol, startRow + i); i++;
			printf("      J88\"                                                                         ");
			gotoxy(startCol, startRow + i); i++;
			printf("      @%%                                                                           ");
			gotoxy(startCol, startRow + i); i++; i++; i++; 
			printf("    :\"                                                                             \033[0m");
			
			gotoxy(startCol, startRow + i); i++; i++;
			printf("	\033[1;33;41m [Q] QUIT         \033[0m		==>	\033[1;34mPress\033[0m \033[1;33;100m'Q'\033[0m to quit the game");
			gotoxy(startCol, startRow + i); i++; i++;
			printf("	\033[1;33;41m [n] GOLD         \033[0m		==>	\033[1;33mGold\033[0m for buying something in the merchant");
			gotoxy(startCol, startRow + i); i++; i++;
			printf("	\033[1;33;41m [0] WHO's TURN   \033[0m		==>	Counting the \033[1;36mround\033[0m that already have been played");
			gotoxy(startCol, startRow + i); i++; i++;
			printf("	                          		and telling who's turn is it");
			gotoxy(startCol, startRow + i); i++; i++;
			printf("	\033[1;33;41m LEVEL [n]        \033[0m		==>	Telling which \033[1;32mlevel\033[0m is right now");
			gotoxy(startCol, startRow + i); i++; i++; i++;
			printf("	\033[1;33;41m [H] HOW TO PLAY? \033[0m		==>	\033[1;34mPress\033[0m \033[1;33;100m'H'\033[0m to move to how to play tab");
			
			gotoxy(startCol, startRow + i); i++; 
			printf("\033[1;31m                                                                             ..                          ");
			gotoxy(startCol, startRow + i); i++;
			printf("                                                                       x .d88\"                ..         ");
			gotoxy(startCol, startRow + i); i++;
			printf("                             ..    .     :                .d``          5888R                @L          ");
			gotoxy(startCol, startRow + i); i++;
			printf("       uL           u      .888: x888  x888.       .u     @8Ne.   .u    '888R         u     9888i   .dL  ");
			gotoxy(startCol, startRow + i); i++;
			printf("   .ue888Nc..    us888u.  ~`8888~'888X`?888f`   ud8888.   %%8888:u@88N    888R      us888u.  `Y888k:*888. ");
			gotoxy(startCol, startRow + i); i++;
			printf("  d88E`\"888E` .@88 \"8888\"   X888  888X '888>  :888'8888.   `888I  888.   888R   .@88 \"8888\"   888E  888I ");
			gotoxy(startCol, startRow + i); i++;
			printf("  888E  888E  9888  9888    X888  888X '888>  d888 '88%%\"    888I  888I   888R   9888  9888    888E  888I ");
			gotoxy(startCol, startRow + i); i++;
			printf("  888E  888E  9888  9888    X888  888X '888>  8888.+\"       888I  888I   888R   9888  9888    888E  888I ");
			gotoxy(startCol, startRow + i); i++;
			printf("  888E  888E  9888  9888    X888  888X '888>  8888L       uW888L  888'   888R   9888  9888    888E  888I ");
			gotoxy(startCol, startRow + i); i++;
			printf("  888& .888E  9888  9888   \"*88%%\"\"*88\" '888!` '8888c. .+ '*88888Nu88P   .888B . 9888  9888   x888N><888' ");
			gotoxy(startCol, startRow + i); i++;
			printf("  *888\" 888&  \"888*\"\"888\"    `~    \"    `\"`    \"88888%%   ~ '88888F`     ^*888%%  \"888*\"\"888\"   \"88\"  888  ");
			gotoxy(startCol, startRow + i); i++;
			printf("   `\"   \"888E  ^Y\"   ^Y'                         \"YP'       888 ^         \"%%     ^Y\"   ^Y'          88F  ");
			gotoxy(startCol, startRow + i); i++;
			printf("  .dWi   `88E                                               *8E                                    98\"   ");
			gotoxy(startCol, startRow + i); i++;
			printf("  4888~  J8%%                                                '8>                                  ./\"     ");
			gotoxy(startCol, startRow + i); i++; i++; i++; ;
			printf("   ^\"===*\"`                                                  \"                                  ~`       \033[0m");
			
			gotoxy(startCol, startRow + i); i++; 
			printf("                      				\033[1;33;100m 'ARROW KEY_UP' \033[0m");	
			gotoxy(startCol, startRow + i); i++; 
			printf("	\033[1;33;41m    Select Mob    \033[0m		==>	\033[1;34mPress\033[0m 	       OR       \033[0m");	
			gotoxy(startCol, startRow + i); i++; i++;
			printf("                      				\033[1;33;100m'ARROW KEY_DOWN'\033[0m");
			
			gotoxy(startCol, startRow + i); i++; 
			printf("                      				\033[1;33;100m'ARROW KEY_LEFT' \033[0m");	
			gotoxy(startCol, startRow + i); i++; 
			printf("	\033[1;33;41m    Select Card   \033[0m		==>	\033[1;34mPress\033[0m 	       OR        \033[0m");	
			gotoxy(startCol, startRow + i); i++; i++;
			printf("                      				\033[1;33;100m'ARROW KEY_RIGHT'\033[0m");
			
			gotoxy(startCol, startRow + i); i++; i++; i++; i++; i++; i++;
			printf("	\033[1;33;41mPlay Selected Card\033[0m		==>	\033[1;34mPress\033[0m 	\033[1;33;100m'KEY_ENTER'\033[0m");
			
			startCol = columns - 50;
			startRow = rows - 5;
			i = 0;
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("\033[31;103m[SPACE]\033[0m	==>	\033[1;34mPress\033[0m \033[1;33;100m'SPACE'\033[0m to go to PAGE 2");
			gotoxy(startCol, startRow + i); i++;
			printf("\033[31;103m [ESC] \033[0m	==>	\033[1;34mPress\033[0m \033[1;33;100m'ESC'\033[0m to return");
		} else if (currentPage == 2) {
			clearScreen();
			displayBorder();
			startCol = columns / 3 - 26;
			startRow = rows / 4 - 15;
			i = 1;
			gotoxy(startCol, startRow + i); i++;
			printf("\033[1;31m                                      ..                                                                                            .             ");
			gotoxy(startCol, startRow + i); i++; 
			printf("                                    dF                                                       .uef^\"                                @88>           ");
			gotoxy(startCol, startRow + i); i++; 
			printf("                         .u    .   '88bu.            ..    .     :                         :d88E                      u.    u.     %%8P            ");
			gotoxy(startCol, startRow + i); i++; 
			printf("      .         u      .d88B :@8c  '*88888bu       .888: x888  x888.       .u          .   `888E             u      x@88k u@88c.    .          .  ");
			gotoxy(startCol, startRow + i); i++; 
			printf(" .udR88N     us888u.  =\"8888f8888r   ^\"*8888N     ~`8888~'888X`?888f`   ud8888.   .udR88N   888E .z8k     us888u.  ^\"8888\"\"8888\"  .@88u   .udR88N ");
			gotoxy(startCol, startRow + i); i++; 
			printf("<888'888k .@88 \"8888\"   4888>'88\"   beWE \"888L      X888  888X '888>  :888'8888. <888'888k  888E~?888L .@88 \"8888\"   8888  888R  ''888E` <888'888k");
			gotoxy(startCol, startRow + i); i++; 
			printf("9888 'Y\"  9888  9888    4888> '     888E  888E      X888  888X '888>  d888 '88%%\" 9888 'Y\"   888E  888E 9888  9888    8888  888R    888E  9888 'Y\" ");
			gotoxy(startCol, startRow + i); i++; 
			printf("9888      9888  9888    4888>       888E  888E      X888  888X '888>  8888.+\"    9888       888E  888E 9888  9888    8888  888R    888E  9888     ");
			gotoxy(startCol, startRow + i); i++; 
			printf("9888      9888  9888   .d888L .+    888E  888F      X888  888X '888>  8888L      9888       888E  888E 9888  9888    8888  888R    888E  9888     ");
			gotoxy(startCol, startRow + i); i++; 
			printf("?8888u../ 9888  9888   ^\"8888*\"    .888N..888      \"*88%%\"\"*88\" '888!` '8888c. .+ ?8888u../  888E  888E 9888  9888   \"*88*\" 8888\"   888&  ?8888u../");
			gotoxy(startCol, startRow + i); i++; 
			printf(" \"8888P'  \"888*\"\"888\"     \"Y\"       `\"888*\"\"         `~    \"    `\"`    \"88888%%    \"8888P'  m888N= 888> \"888*\"\"888\"    \"\"   'Y\"     R888\"  \"8888P' ");
			gotoxy(startCol, startRow + i); i++; 
			printf("   \"P'     ^Y\"   ^Y'                   \"\"                                \"YP'       \"P'     `Y\"   888   ^Y\"   ^Y'                   \"\"      \"P'   ");
			gotoxy(startCol, startRow + i); i++; 
			printf("                                                                                                 J88\"                                             ");
			gotoxy(startCol, startRow + i); i++; 
			printf("                                                                                                 @%%                                               ");
			gotoxy(startCol, startRow + i); i++; 
			printf("                                                                                               :\"                                                 \033[0m");
			
			startCol = columns / 3 - 22;
			gotoxy(startCol, startRow + i); i++; i++;
			printf("	   	     \033[1;33;41m CARDS:         \033[0m");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     \033[33m[n]\033[0m------------");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |			\033[33m[n]\033[0m ==> How much energy cost");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |		==> 	\033[31m[n]\033[0m ==> How much the value of the \033[31mAttack\033[0m OR \033[34mShield\033[0m");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |			If the border of the card is colored \033[34mBLUE\033[0m ");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |			then it means, it's the current card");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     |             |");
			gotoxy(startCol, startRow + i); i++; 
			printf("	   	     ------------\033[31m[n]\033[0m			Like this: \033[33m[n]\033[0m\033[34m------------\033[0m");
			gotoxy(startCol, startRow + i); i++;
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++; 
			printf("	                    				       	   \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++; 
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++; 
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++; 
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++;
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++;
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++;
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++;
			printf("	                    				           \033[34m|             |\033[0m");
			gotoxy(startCol, startRow + i); i++; i++; i++; i++;
			printf("	                    				           \033[34m------------\033[0m\033[31m[n]\033[0m");

			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   	     \033[1;33;41m DECK IN HAND   \033[0m 		==>	Every new \033[1;36mround\033[0m start, \033[1;34mdraw\033[0m cards from \033[1;33mdeck inventory\033[0m.");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						The \033[1;34mdraw\033[0m cards from \033[1;33mdeck inventory\033[0m is based on the cards");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						that left in the \033[1;31mhand\033[0m, max \033[1;34mdraw\033[0m from the \033[1;33mdeck inventory\033[0m is \033[1;33;100m5 cards\033[0m.");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						If there are cards left in the \033[1;31mhand\033[0m it will \033[1;34mdraw\033[0m");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						based by \033[1;33;100m5 - cards left in the hand\033[0m.");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   	     \033[1;33;41m DECK INVENTORY \033[0m		==>	All cards that you had is in here, and it graduately decrease");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						because it moved to the \033[1;31mhand\033[0m");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   	     \033[1;33;41m DISCARD PILE   \033[0m 		==>	After you play your card, it'll be moved to here");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						and when the \033[1;33mdeck inventory\033[0m reach 0, all cards in \033[1;35mdiscard pile\033[0m");
			gotoxy(startCol, startRow + i); i++; i++; 
			printf("	   						will be moved to the \033[1;33mdeck inventory\033[0m again");
			gotoxy(startCol, startRow + i); i++; i++; i++; i++; i++;

			startCol = 4;
			startRow = rows - 5;
			i = 0;
			gotoxy(startCol, startRow + i); i++; i++;
			printf("\033[31;103m[SPACE]\033[0m	==>	\033[1;34mPress\033[0m \033[1;33;100m'SPACE'\033[0m to go to PAGE 1");
			gotoxy(startCol, startRow + i); i++;
			printf("\033[31;103m [ESC] \033[0m	==>	\033[1;34mPress\033[0m \033[1;33;100m'ESC'\033[0m to return");
		}
		
		// Handle input
		int key = getch();
		
		if (key == KEY_ESC) { // ESC key
			playEnterBeep();
			clearScreen();
			displayBorder();
			return; // Exit the function completely
		}
		else if (key == KEY_SPACE) { 
			playEnterBeep();
			if (currentPage == 1) {
				currentPage = 2; // Go to card mechanics page
			} else {
				currentPage = 1; // Go back to controls page
			}
		} 
	}
}

void startGame() {
	MapNode* gameMap;
    g_isGameActive = true;
    srand(time(0));
    hideCursor();

    gameMap = generateMap(1);

    if (gameMap != Nil) {
        startNavigation(gameMap);
    } else {
        clearScreen();
        gotoxy(0,0);
        printf("ERROR: Failed to generate map.\n");
        Sleep(2000);
    }

    clearScreen();
    gotoxy(0,5);
    freeMapTree(gameMap);
}
