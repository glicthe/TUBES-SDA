// map_navigation.c

#include "map_navigation.h"
#include "map_display.h"

void startNavigation(MapNode* mapRoot) {
    MapNode *currentNode, *selectedChild;
    int selectionIndex, keyPressed;
    boolean isGameRunning;

    if (mapRoot == Nil) {
        fprintf(stderr, "Error: Invalid map root node\n");
        return;
    }

    currentNode = mapRoot;
    selectionIndex = 0;
    isGameRunning = TRUE;

    while (isGameRunning && currentNode != Nil) {
        boolean isNodeChosen = FALSE;
        currentNode->isVisited = TRUE;

        while (!isNodeChosen && isGameRunning && currentNode != Nil) {
            clearScreen();
            gotoxy(0, 0);

            drawMapView(currentNode, selectionIndex);

            gotoxy(0, 20);
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("Node Saat Ini: ");
            setTextColor(COLOR_GRAY);
            printf("[%s] %s", NODE_TYPE_NAMES[currentNode->type], currentNode->name);
            setColorDefault();
            printf(" (Floor %d, Depth %d, ID:%d)\n", currentNode->floor, currentNode->depth, currentNode->id);

            if (currentNode->type == NODE_BIG_BOSS) {
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                setColorGreen();
                printf("?????? SELAMAT! Anda telah mencapai BIG BOSS! ??????\n");
                setColorDefault();
                printf("Tekan Enter untuk keluar...");
                while (_getch() != KEY_ENTER);
                isGameRunning = FALSE;
                break;
            }

            if (currentNode->numChildren == 0) {
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                setColorRed();
                printf("Jalan buntu. Tidak ada jalan lagi dari sini.\n");
                setColorDefault();
                printf("Tekan Enter untuk keluar...");
                while (_getch() != KEY_ENTER);
                isGameRunning = FALSE;
                break;
            }

            printf("Node Terpilih: ");
            if (selectionIndex >= 0 && selectionIndex < currentNode->numChildren) {
                selectedChild = currentNode->children[selectionIndex];
                setColorHighlight_Map();
                printf("[%s] %s", NODE_TYPE_NAMES[selectedChild->type], selectedChild->name);
                setColorDefault();
            } else {
                printf("(Tidak ada pilihan)");
            }
            printf("\n------------------------------------------------------------------------------------------------------------------------\n");
            printf("Gunakan Panah Kiri/Kanan untuk memilih jalur, Enter untuk Konfirmasi, Esc untuk Keluar.\n");
            printf("Tekan F1 untuk melihat struktur peta lengkap (DEBUG).\n");
            printf("------------------------------------------------------------------------------------------------------------------------\n");

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
