#include "menu.h"

// Fungsi untuk menampilkan menu dengan design yang diperbaiki
void displayMenu(MenuItem menu[], int menuSize, int selectedIndex) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    clearScreen();

    displayBorder();
    displayGameTitle();

    int menuWidth = 40; // Lebar menu yang digunakan untuk kalkulasi padding
    int textWidth = 38; // Lebar efektif untuk teks di dalam pipa "| text |"
    int startRow = 28;
    int startCol = (columns - menuWidth) / 2;

    if (startCol < 3) startCol = 3;
    if (startCol + menuWidth > columns - 3) startCol = columns - menuWidth - 3;

    // --- Definisi Atribut Warna Tema Naga & Medieval (DIPERBARUI) ---
    const int FRAME_COLOR_ATTR = COLOR_RED;
    const int HEADER_FRAME_ATTR = (COLOR_BLACK * 16) + COLOR_LIGHT_YELLOW; // Kuning terang di atas hitam
    const int HEADER_TEXT_BG_ATTR = (COLOR_RED * 16) + COLOR_LIGHT_YELLOW;
    const int INSTRUCTION_KEY_ATTR = COLOR_LIGHT_RED;
    const int INSTRUCTION_NORMAL_TEXT_ATTR = COLOR_WHITE;
    const int ITEM_NORMAL_TEXT_ATTR = COLOR_WHITE;
    const int ITEM_SELECTED_ATTR = (COLOR_LIGHT_YELLOW * 16) + COLOR_BLACK;
    // const int STATUS_TEXT_ATTR = COLOR_LIGHT_YELLOW; // Tidak digunakan secara umum lagi, dipecah
    const int STATUS_LITERAL_ATTR = (COLOR_BLACK * 16) + COLOR_WHITE;      // "Selected: " Putih di atas Hitam
    const int STATUS_ITEMNAME_ATTR = (COLOR_BLACK * 16) + COLOR_LIGHT_RED; // Nama item Merah Terang di atas Hitam
    const int DECORATION_STAR_ATTR = COLOR_GREEN;       // Untuk <*> Hijau Tua
    const int DECORATION_SLASH_ATTR = COLOR_MAGENTA;    // Untuk /|\ Magenta
    const int INSTRUCTION_LOWER_BORDER_ATTR = HEADER_FRAME_ATTR;
    const int BLACK_BG_WHITE_FG_FOR_PADDING = (COLOR_BLACK * 16) + COLOR_WHITE; // Untuk spasi padding di status box
    // --- Akhir Definisi Atribut Warna ---

    // Menu header
    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, startRow);
    printf("+======================================+");

    gotoxy(startCol, startRow + 1);
    setTextColor(HEADER_TEXT_BG_ATTR);
    printf("|            -= MAIN MENU =-           |");

    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, startRow + 2);
    printf("+======================================+");

    // Baris Instruksi
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

    // --- Status information dengan Bingkai Baru dan Warna Teks Terpisah ---
    int statusBoxY = startRow + 9 + menuSize;

    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, statusBoxY);
    printf("+======================================+");

    gotoxy(startCol, statusBoxY + 1);
    char selectedItemText[50];
    strcpy(selectedItemText, menu[selectedIndex].text); // Salin nama item

    char statusLiteral[] = "Selected: ";
    int statusLiteralLen = strlen(statusLiteral);
    int selectedItemTextLen = strlen(selectedItemText);
    int totalTextLen = statusLiteralLen + selectedItemTextLen;
    int statusPadding = (textWidth - totalTextLen) / 2;
    if (statusPadding < 0) statusPadding = 0;

    setTextColor(HEADER_FRAME_ATTR); printf("|"); // Pipa kiri

    // Spasi padding kiri (latar hitam dari HEADER_FRAME_ATTR)
    int k;
    for(k=0; k < statusPadding; ++k) { printf(" "); }

    setTextColor(STATUS_LITERAL_ATTR); // "Selected: " Putih di atas Hitam
    printf("%s", statusLiteral);

    setTextColor(STATUS_ITEMNAME_ATTR); // Nama item Merah Terang di atas Hitam
    printf("%s", selectedItemText);

    // Spasi padding kanan (latar hitam dari HEADER_FRAME_ATTR)
    int remainingSpaces = textWidth - totalTextLen - statusPadding;
    for(k=0; k < remainingSpaces; ++k) { printf(" "); }

    setTextColor(HEADER_FRAME_ATTR); printf("|"); // Pipa kanan

    setTextColor(HEADER_FRAME_ATTR);
    gotoxy(startCol, statusBoxY + 2);
    printf("+======================================+");
    // --- Akhir Status Information ---


    // Additional decorative elements (Warna <*> diubah)
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

// Fungsi untuk menjalankan aksi menu
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
            clearScreen();
            displayBorder();
            gotoxy(startCol, startRow);
            setColorLightGreen();
            printf("+=================================================================+");
            gotoxy(startCol, startRow + 1);
            printf("|                         SETTINGS                                |");
            gotoxy(startCol, startRow + 2);
            printf("+=================================================================+");
            setColorDefault();
            gotoxy(startCol, startRow + 4);
            printf("  Game Settings:");
            gotoxy(startCol, startRow + 5);
            printf("  - Difficulty: Normal");
            gotoxy(startCol, startRow + 6);
            printf("  - Sound: ON");
            gotoxy(startCol, startRow + 7);
            printf("  - Auto-save: ON");
            gotoxy(startCol, startRow + 8);
            printf("  - Animation Speed: Normal");
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
    
    // Tunggu sampai tombol ENTER ditekan
    while (getch() != KEY_ENTER);
}

// Fungsi untuk menampilkan splash screen
void SplashScreen() {
    // Maximize console window
    Sleep(1000);
    
    // Inisialisasi menu items
    MenuItem menu[] = {
        {"New Game", 1},
        {"Load Game", 2},
        {"Settings", 3},
        {"Credits", 4},
        {"Exit Game", 5}
    };
    
    int menuSize = sizeof(menu) / sizeof(menu[0]);
    int selectedIndex = 0;
    int key;
    int running = 1;
    
    // Deklarasi variabel untuk ukuran console
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
        // Mengubah posisi tulisan ke atas, tepat setelah title
        gotoxy(promptStartCol, 30); // Mengubah dari rows - 5 menjadi 20
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
        }
    }
}
