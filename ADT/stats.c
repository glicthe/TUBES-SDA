#include "stats.h"
#include "config.h"

GameStats g_gameStats;

void initGameStats() {
    g_gameStats.enemiesDefeated = 0;
    g_gameStats.highestDepthCompleted = 0;
    g_gameStats.totalCardsOwned = 0;
}

void showGameStats(const Player *player) {
    clearScreen();
    displayBorder();

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    
    int startX = (columns - 140) / 2;
    int startY = 18;

    gotoxy(startX + 10, startY++);
    printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. %s\n", LYELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\%s\n", YELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /%s\n", LYELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / %s\n", YELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s / /\\%s          ...              s                     s       .       .x+=:.        s       .                 .x+=:.     %s/ /\\ \n",LYELLOW, LRED, LYELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s/ /\\ \\%s     .x888888hx    :     :8                    :8      @88>    z`    ^%%      :8      @88>              z`    ^%%   %s/ /\\ \\\n",YELLOW, LRED, YELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s\\ \\/ /%s    d88888888888hxx     .88                   .88      %%8P        .   <k    .88      %%8P                  .   <k  %s\\ \\/ /\n",LYELLOW, LRED, LYELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s \\/ /%s    8\" ... `\"*8888%%`    :888ooo       u       :888ooo    .       .@8Ned8\"   :888ooo    .          .      .@8Ned8\"   %s\\/ / \n",YELLOW, LRED, YELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s / /\\%s   !  \"   ` .xnxx.    -*8888888    us888u.  -*8888888  .@88u   .@^%%8888\"  -*8888888  .@88u   .udR88N   .@^%%8888\"    %s/ /\\ \n",LYELLOW, LRED, LYELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s/ /\\ \\%s  X X   .H8888888%%:    8888    .@88 \"8888\"   8888    ''888E` x88:  `)8b.   8888    ''888E` <888'888k x88:  `)8b.  %s/ /\\ \\\n",YELLOW, LRED, YELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s\\ \\/ /%s  X 'hn8888888*\"   >   8888    9888  9888    8888      888E  8888N=*8888   8888      888E  9888 'Y\"  8888N=*8888  %s\\ \\/ /\n",LYELLOW, LRED, LYELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s \\/ /%s   X: `*88888%%`     !   8888    9888  9888    8888      888E   %%8\"    R88   8888      888E  9888       %%8\"    R88   %s\\/ / \n",YELLOW, LRED, YELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s / /\\%s   '8h.. ``     ..x8>  .8888Lu= 9888  9888   .8888Lu=   888E    @8Wou 9%%   .8888Lu=   888E  9888        @8Wou 9%%    %s/ /\\ \n",LYELLOW, LRED, LYELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s/ /\\ \\%s   `88888888888888f   ^%%888*   9888  9888   ^%%888*     888&  .888888P`    ^%%888*     888&  ?8888u../ .888888P`    %s/ /\\ \\\n",YELLOW, LRED, YELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s\\ \\/ /%s    '%%8888888888*\"      'Y\"    \"888*\"\"888\"    'Y\"      R888\" `   ^\"F        'Y\"      R888\"  \"8888P'  `   ^\"F      %s\\ \\/ /\n",LYELLOW, LRED, LYELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s \\/ /%s        ^\"****\"\"`                ^Y\"   ^Y'               \"\"                            \"\"      \"P'                  %s\\/ / \n",YELLOW, LRED, YELLOW);
    gotoxy(startX + 10, startY++);
    printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ %s\n", LYELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\%s\n", YELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /%s\n", LYELLOW, RESET);
    gotoxy(startX + 10, startY++);
    printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' %s\n", LYELLOW, RESET);

    const int separatorWidth = 69;
    const int statsBlockWidth = 40;

    int separatorX = (columns - separatorWidth) / 2;
    int statsTextX = (columns - statsBlockWidth) / 2;

    int currentY = startY + 2; 

    printStatistics_Top(separatorX, currentY);
    currentY += 5;

    gotoxy(statsTextX, currentY);
    printf("  %-25s => ", "Highest Depth Completed");
    setColorGreen();
    printf("%d", g_gameStats.highestDepthCompleted);
    setColorDefault();
    currentY += 2; 

    gotoxy(statsTextX, currentY);
    printf("  %-25s => ", "Total Enemies Defeated");
    setColorRed();
    printf("%d", g_gameStats.enemiesDefeated);
    setColorDefault();
    currentY += 2;

    gotoxy(statsTextX, currentY);
    printf("  %-25s => ", "Total Cards in Deck");
    setColorCyan();
    printf("%d", g_gameStats.totalCardsOwned);
    setColorDefault();
    currentY += 2;

    gotoxy(statsTextX, currentY);
    printf("  %-25s => ", "Current Gold");
    setColorYellow();
    printf("%d", player->gold);
    setColorDefault();
    currentY += 3;

    gotoxy(statsTextX + 2, currentY);
    setColorWhite();
    printf("Press ");
    setColorGreen();
    printf("[ENTER]");
    setColorWhite();
    printf(" to return to menu...");
    setColorDefault();

    currentY += 2;
    printStatistics_Bottom(separatorX, currentY);

    while(true) {
    if (getch() == KEY_ENTER) {
        playEnterBeep();
        break;
        }
    }
}

void printStatistics_Top(int x, int y) {
	setColorBrightWhite();
	gotoxy(x, y);     printf("                                   %s/\\", CYAN);
	gotoxy(x, y + 1); printf("%s __                                %s\\/                             %s__", LYELLOW, CYAN, LYELLOW);
	gotoxy(x, y + 2); printf("%s(________________________________/\\/\\/\\_____________________________)", LYELLOW);
	setColorDefault();
}

void printStatistics_Bottom(int x, int y) {
	setColorBrightWhite();
	gotoxy(x, y);     printf(" %s______________________________      _____________________________", LYELLOW);
	gotoxy(x, y + 1); printf("%s(__                            \\/\\/\\/                           __)", LYELLOW);
	gotoxy(x, y + 2); printf("                                 %s/\\", CYAN);
	gotoxy(x, y + 3); printf("                                 %s\\/", CYAN);
	setColorDefault();
}