#include "display.h"

// Fungsi untuk menampilkan border dekoratif
void displayBorder() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    setTextColor(7); // White color for border

    // Top border
    gotoxy(0, 0);
    int i;
    for(i = 0; i < columns; i++) printf("=");

    // Bottom border
    gotoxy(0, rows - 1);
    for(i = 0; i < columns; i++) printf("=");

    // Side borders
    for(i = 1; i < rows - 1; i++) {
        gotoxy(0, i);
        printf("||");
        gotoxy(columns - 2, i);
        printf("||");
    }
}

// Fungsi untuk menampilkan judul game
void displayGameTitle() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // ------------------- MODIFIKASI DIMULAI DI SINI -------------------
    // GANTI NILAI INI dengan lebar visual aktual dari baris terpanjang pada ASCII art judul Anda.
    // Hitung karakter yang terlihat, jangan sertakan escape codes ANSI.
    // Contoh perhitungan kasar untuk baris terpanjang:
    // "          ---__----___/ __ \\--  || |  --/ __ \\___----__---  " (sekitar 58 char) +
    // "  (_______)--------------------------------------------------------------------------------------------------------------------------(_______)" (sekitar 130 char)
    // Total perkiraan = 188. Anda HARUS menghitungnya dengan akurat.
    int artWidth = 188; // <--- SESUAIKAN NILAI INI!

    // Lebar yang tersedia untuk seni ASCII di dalam border (border kiri "||" dan kanan "||" masing-masing 2 karakter)
    int availableWidthForArt = columns - 4;

    // Hitung kolom awal untuk memusatkan seni ASCII
    int startCol = (availableWidthForArt - artWidth) / 2;

    // Tambahkan offset untuk border kiri ("||") agar posisi dihitung dari setelah border
    startCol += 2;

    // Pastikan seni ASCII tidak menimpa border kiri
    if (startCol < 3) { // Minimal kolom ke-3 (setelah "||")
        startCol = 3;
    }

    // Pastikan seni ASCII tidak menimpa border kanan
    // columns - 2 adalah posisi tepat sebelum border kanan "||"
    if (startCol + artWidth > columns - 2) {
        // Jika seni ASCII terlalu lebar untuk konsol saat ini dan akan menimpa border kanan:
        if (columns > artWidth + 4) { // Cek apakah ada cukup ruang jika dipusatkan
             // Jika masih ada ruang, geser ke kiri agar pas sebelum border kanan
            startCol = columns - artWidth - 2;
        } else {
            // Jika konsol sangat sempit, mulai dari kiri setelah border kiri
            startCol = 3;
        }
    }
    // ------------------- MODIFIKASI BERAKHIR DI SINI -------------------

    // ASCII art title Anda dengan posisi yang diperbaiki
    // (Bagian printf di bawah ini tetap sama, hanya nilai startCol yang memengaruhi posisinya)
    gotoxy(startCol - 5, 3);
    printf("\033[1;32m                                 \033[35m** \033[0m");
    gotoxy(startCol - 5, 4);
    printf("\033[1;32m                                 \033[33m||                                           ");
    gotoxy(startCol - 5, 5);
    printf("\033[1;32m       -==-____        _--_   \033[33m___||___   \033[32m_--_        ____-==-  \033[1;33m_______                                                                                                                            _______");
    gotoxy(startCol - 5, 6);
    printf("\033[1;32m          ---__----___/ __ \\--  \033[37m|| |  \033[32m--/ __ \\___----__---  \033[1;33m  (_______)--------------------------------------------------------------------------------------------------------------------------(_______)");
    gotoxy(startCol - 5, 7);
    printf("\033[1;32m               ---__ / /  \\ \\   \033[37m\\\\ /\033[37m   \033[32m/ /  \\ \\ __---          \033[1;33m|     |\033[31m     ...     ..            ..                            ..          \033[0m.x+=:.                    .                            \033[1;33m|     |");
    gotoxy(startCol - 5, 8);
    printf("\033[1;32m                    -\\|    \\ \\  _\033[37m\\/\033[37m\033[32m\\_  \033[32m/ /    |/-              \033[1;33m|     |\033[31m  .=*8888x <\"?88h.   x .d88\"                           dF           \033[0mz`    ^%%                  @88>                          \033[1;33m|     |");
    gotoxy(startCol - 5, 9);
    printf("\033[1;32m                   __/ \\_\033[31m()\033[32m/\\ \\\\/  \\\\/ /\\\033[31m()\033[32m_/ \\__              \033[1;33m|     |\033[31m X>  '8888H> '8888    5888R          u.          u.   '88bu.           \033[0m.   <k  .d``           %%8P      .u    .              \033[1;33m|     |");
    gotoxy(startCol - 5, 10);
    printf("\033[1;32m                  /_ \\ / ~~  `-'    `-'  ~~ \\ / _\\             \033[1;33m|     |\033[1;31m'88h. `8888   8888    '888R    ...ue888b   ...ue888b  '*88888bu      \033[0m.@8Ned8\"  @8Ne.   .u      .     .d88B :@8c       .u    \033[1;33m|     |");
    gotoxy(startCol - 5, 11);
    printf("\033[1;32m                 |/_\\ |(~/   /\\  /\\  /\\   \\~)| /_\\|            \033[1;33m|     |\033[1;31m'8888 '8888    \"88>    888R    888R Y888r  888R Y888r   ^\"*8888N   \033[0m.@^%%8888\"   %%8888:u@88N   .@88u  =\"8888f8888r   ud8888.  \033[1;33m|     |");
    gotoxy(startCol - 5, 12);
    printf("\033[1;32m                  /_  | /   (O ` \\/ ' O)   \\ |  _\\             \033[1;33m|     |\033[1;31m `888 '8888.xH888x.    888R    888R I888>  888R I888>  beWE \"888L \033[0mx88:  `)8b.   `888I  888. ''888E`   4888>'88\"  :888'8888. \033[1;33m|     |");
    gotoxy(startCol - 5, 13);
    printf("\033[1;32m                   _\\ \\_\\/\\___--~~~~--___/\\/_/ /_              \033[1;33m|     |\033[1;31m   X\" :88*~  `*8888>   888R    888R I888>  888R I888>  888E  888E \033[0m8888N=*8888    888I  888I   888E    4888> '    d888 '88%%\" \033[1;33m|     |");
    gotoxy(startCol - 5, 14);
    printf("\033[1;32m                  /    _/\\\033[0m^\033[32m\\ \033[0mV~~V/~V~~V\033[32m /\033[0m^\033[32m/\\_    \\             \033[1;33m|     |\033[1;31m ~\"   !\"`      \"888>   888R    888R I888>  888R I888>  888E  888E  \033[0m%%8\"    R88    888I  888I   888E    4888>      8888.+\"    \033[1;33m|     |");
    gotoxy(startCol - 5, 15);
    printf("\033[1;32m                  \\/\\ / \\ \\\033[0m^\033[32m\\  \033[31m|( /\033[32m    /\033[0m^\033[32m/ / \\ /\\/             \033[1;33m|     |\033[1;31m.H8888h.         ?88   888R   u8888cJ888  u8888cJ888   888E  888F   \033[0m@8Wou 9%%\"  uW888L  888'   888E   .d888L .+   8888L      \033[1;33m|     |");
    gotoxy(startCol - 5, 16);
    printf("\033[1;32m                     \\\\   /\\\033[0m^\033[32m\\  \033[31m\\\\\\\033[32m   /\033[0m^\033[32m/\\   //                \033[1;33m|     |\033[1;31m :\"^\"88888h.    '!    .888B .  \"*888*P\"    \"*888*P\"   .888N..888  \033[0m.888888P`   '*88888Nu88P    888E   ^\"8888*\"    '8888c. .+ \033[1;33m|     |");
    gotoxy(startCol - 5, 17);
    printf("\033[1;32m                       \\ | /\\\033[0m^\033[32m\\  \033[31m\\/\033[32m  /\033[0m^\033[32m/\\ | /                  \033[1;33m|     |\033[1;31m ^    \"88888hx.+\"     ^*888%%     'Y\"         'Y\"       `\"888*\"\"   \033[0m`   ^\"F     ~ '88888F`     R888\"     \"Y\"        \"88888%%   \033[1;33m|     |");
    gotoxy(startCol - 5, 18);
    printf("\033[1;32m                         |( /\\_\\\033[0m^__\033[0m^\033[32m/_/\\ )|                    \033[1;33m|     |\033[1;31m        ^\"**\"\"          \"%%                                \"\"                     \033[0m888 ^         \"\"                   \"YP'    \033[1;33m|     |");
    gotoxy(startCol - 5, 19);
    printf("\033[1;32m                         | \\\\__--__--__// |                    \033[1;33m|     |\033[1;31m                                                                                 \033[0m*8E                                        \033[1;33m|     |");
    gotoxy(startCol - 5, 20);
    printf("\033[1;32m                        \033[34m/~~~~~~~~~~~~~~~~~~\\                   \033[1;33m|     |\033[1;31m                                                                                 \033[0m'8>                                        \033[1;33m|     |");
    gotoxy(startCol - 5, 21);
    printf("\033[1;32m                       \033[34m|/|  \033[33m/\\  /\\/\\  /\\  \033[34m|\\|         \033[1;33m         |_____|\033[1;31m                                                                                  \033[0m\"                                         \033[1;33m|_____|");
    gotoxy(startCol - 5, 22);
    printf("\033[1;32m                       \033[34m||| \033[33m| | ( \033[36m()\033[33m ) | | \033[34m|||              \033[1;33m   (_______)--------------------------------------------------------------------------------------------------------------------------(_______)");
    gotoxy(startCol - 5, 23);
    printf("\033[1;32m                       \033[34m|\\|  \033[33m\\/  \\/\\/  \\/  \033[34m|/|             ");
    gotoxy(startCol - 5, 24);
    printf("\033[1;32m                        \033[34m\\__________________/                  ");
    gotoxy(startCol - 5, 25);
    printf("\033[1;32m                        | (____------____) |                   \033[0m");
}

// Fungsi untuk menampilkan loading animation
void showLoading(char* message) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int startRow = rows / 3;
    int availableWidth = columns - 4;
    int boxWidth = 50; // Lebar box loading
    int startColMessage = 2 + (availableWidth - boxWidth) / 2; // Disesuaikan dengan boxWidth

    if (startColMessage < 3) startColMessage = 3;
    if (startColMessage + boxWidth > columns - 3) startColMessage = columns - boxWidth - 3;

    clearScreen();
    displayBorder();

    setTextColor(7);
    gotoxy(startColMessage, startRow);
    printf("+================================================+"); // Lebar 50 karakter
    gotoxy(startColMessage, startRow + 1);
    printf("|                                                |");
    gotoxy(startColMessage, startRow + 2);
    printf("| %-*s |", boxWidth - 4, message); // Sesuaikan padding dengan boxWidth
    gotoxy(startColMessage, startRow + 3);
    printf("|                                                |");
    gotoxy(startColMessage, startRow + 4);
    printf("+================================================+");

    char loading[] = "|/-\\";
    int i;
    for(i = 0; i < 20; i++) {
        // Pusatkan teks loading di bawah kotak pesan
        int loadingTextLen = strlen("Loading X"); // X adalah karakter animasi
        int startColLoading = 2 + (availableWidth - loadingTextLen) / 2;
        if (startColLoading <3) startColLoading = 3;

        gotoxy(startColLoading, startRow + 6);
        setTextColor(14);
        printf("Loading %c", loading[i % 4]);
        setTextColor(7);
        Sleep(100);
    }
}
