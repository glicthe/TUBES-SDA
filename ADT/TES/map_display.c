#include "map_display.h"

void drawMapView(MapNode* activeNode, int selectedIndex) {
    int currentY = MAP_START_Y;
    int i, textLen, padding;
    char nodeCurrentStr[60];

    if (activeNode == Nil) {
        gotoxy(MAP_START_X, currentY);
        printf("   No active node.\n");
        return;
    }

    sprintf(nodeCurrentStr, "[%s]", NODE_TYPE_NAMES[activeNode->type]);
    gotoxy(MAP_START_X + 92, currentY);
    applyNodeColor(activeNode, TRUE, FALSE, FALSE);
    printf("%s", nodeCurrentStr);
    setColorDefault();
    textLen = strlen(nodeCurrentStr);
    padding = NODE_DISPLAY_WIDTH_L > textLen ? NODE_DISPLAY_WIDTH_L - textLen : 0;
    for (i = 0; i < padding; ++i) printf(" ");
    printf(" <==(You Are Here!)");
    currentY += 2;

    if (activeNode->type == NODE_BIG_BOSS || activeNode->numChildren == 0) return;

    if (activeNode->depth == 0) {
        drawPattern_D0_Start(activeNode, selectedIndex, &currentY);
    } else if (activeNode->depth == 1) {
        if (activeNode->siblingIndex == 0) drawPattern_D1_S0(activeNode, selectedIndex, &currentY);
        else if (activeNode->siblingIndex == 1) drawPattern_D1_S1(activeNode, selectedIndex, &currentY);
        else if (activeNode->siblingIndex == 2) drawPattern_D1_S2(activeNode, selectedIndex, &currentY);
    } else if (activeNode->depth == 2) {
        if (activeNode->parent->siblingIndex == 0) drawPattern_D2_S0_Children(activeNode, selectedIndex, &currentY);
        else drawPattern_D2_S1_S2_Children(activeNode, selectedIndex, &currentY);
    } else if (activeNode->depth == 3 && activeNode->children[0]->type == NODE_SECONDARY_BOSS) {
        drawPattern_D3_To_Boss(activeNode, selectedIndex, &currentY);
    } else if (activeNode->depth == 4 && activeNode->type == NODE_SECONDARY_BOSS) {
        drawPattern_D4_Boss(activeNode, selectedIndex, &currentY);
    } else if (activeNode->depth >= 3 && activeNode->numChildren > 0) {
        drawPattern_Single_Child(activeNode, selectedIndex, &currentY);
    } else {
        gotoxy(MAP_START_X, currentY++);
        printf("                 (Default visualization not available)\n");
        if (activeNode->numChildren > 0) {
            gotoxy(MAP_START_X, currentY++);
            printf("                 Paths: ");
            for (i = 0; i < activeNode->numChildren; ++i) {
                applyNodeColor(activeNode->children[i], FALSE, (i == selectedIndex), FALSE);
                printf("[%s] ", NODE_TYPE_NAMES[activeNode->children[i]->type]);
                setColorDefault();
            }
            printf("\n");
        }
    }
}


 void applyNodeColor(MapNode* node, boolean isPlayer, boolean isSelected, boolean isGrandchild) {
    if (node == Nil) {
        setColorDefault();
        return;
    }
    if (isPlayer) {
        setColorGray();
    } else if (isSelected && !isGrandchild) {
        setColorHighlight_Map();
    } else if (node->isVisited) {
        setColorGray();
    } else {
        switch (node->type) {
            case NODE_MERCHANT:       setColorCyan(); break;
            case NODE_REST:           setColorGreen(); break;
            case NODE_SECONDARY_BOSS: setTextColor(COLOR_LIGHT_MAGENTA); break;
            case NODE_BIG_BOSS:       setColorMagenta(); break;
            case NODE_ENEMY:          setColorRed(); break;
            default:                  setColorDefault(); break;
        }
    }
}

void printPaddedNode(MapNode* node, int width, boolean isPlayer, boolean isSelected, boolean isGrandchild) {
    int k, textLen, padding;
    char rawNodeText[30];

    if (node == Nil) {
        for (k = 0; k < width; ++k) printf(" ");
        setColorDefault();
        return;
    }
    sprintf(rawNodeText, "[%s]", NODE_TYPE_NAMES[node->type]);
    textLen = strlen(rawNodeText);
    padding = width > textLen ? width - textLen : 0;

    applyNodeColor(node, isPlayer, isSelected, isGrandchild);
    printf("%s", rawNodeText);
    setColorDefault();
    for (k = 0; k < padding; ++k) printf(" ");
}

void drawPattern_D0_Start(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0 = activeNode->children[0];
    MapNode *l1c1 = activeNode->children[1];
    MapNode *l1c2 = activeNode->children[2];
    MapNode *l2gc[8] = {Nil};

    l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
    l2gc[1] = (l1c1 && l1c1->numChildren > 0) ? l1c1->children[0] : Nil;
    l2gc[2] = (l1c1 && l1c1->numChildren > 1) ? l1c1->children[1] : Nil;
    l2gc[3] = (l1c1 && l1c1->numChildren > 2) ? l1c1->children[2] : Nil;
    l2gc[4] = (l1c2 && l1c2->numChildren > 0) ? l1c2->children[0] : Nil;
    l2gc[5] = (l1c2 && l1c2->numChildren > 1) ? l1c2->children[1] : Nil;
    l2gc[6] = (l1c2 && l1c2->numChildren > 2) ? l1c2->children[2] : Nil;
    l2gc[7] = (l1c2 && l1c2->numChildren > 3) ? l1c2->children[3] : Nil;

    gotoxy(MAP_START_X + 65, *currentY); printf(".-~'-.-.~:~.-.-`~-."); 
	gotoxy(MAP_START_X + 94, *currentY); printf(",|`            "); 
	gotoxy(MAP_START_X + 108, *currentY); printf(".-~'-.-.~:~.-.-`~-.\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 61, *currentY); printf(".-~'                   `~-."); 
	gotoxy(MAP_START_X + 88, *currentY); printf("      ';`        "); 
	gotoxy(MAP_START_X + 104, *currentY); printf(".-~'                   `~-.\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 57, *currentY); printf(".-~'                           ~-.__/ ' \\__.-~'                           `~-.\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 53, *currentY); printf(".-~'                                  `-' | `-'                                    `~-.\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 52, *currentY); printf("/;                                        .:,                                          `|;\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 51, *currentY); printf(":.                                          ;`                                            `._-_\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 49, *currentY);
    printPaddedNode(l1c0, NODE_DISPLAY_WIDTH_L, FALSE, (0 == selectedIndex), FALSE);
    gotoxy(MAP_START_X + 92, *currentY);
    printPaddedNode(l1c1, NODE_DISPLAY_WIDTH_L, FALSE, (1 == selectedIndex), FALSE);
    gotoxy(MAP_START_X + 144, *currentY);
    printPaddedNode(l1c2, NODE_DISPLAY_WIDTH_L, FALSE, (2 == selectedIndex), FALSE);
    printf("\n"); (*currentY)++;
    
    gotoxy(MAP_START_X + 51, *currentY); printf("|                                       .-~ | `~-.__                                     _--_/ | | \\_-`.,_\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 51, *currentY); printf("/-                                  _.,/     \\.    |__                      .;__-.;`~_.;      ;  \\_.     \\~._\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 51, *currentY); printf("\\`                                /           |        \\_-_;              ./          _.;~_./      \\        \\._-\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 50, *currentY); printf("./                         _---;`~ ;           /             \\            /;          |;             |;,        ,\\;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 47, *currentY);
    
    printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("             ");
    printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("         ");
    printPaddedNode(l2gc[2], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("   ");
    printPaddedNode(l2gc[3], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf(" ");
    printPaddedNode(l2gc[4], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf(" ");
    printPaddedNode(l2gc[5], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf(" ");
    printPaddedNode(l2gc[6], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
    
    printPaddedNode(l2gc[7], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); printf("\n"); (*currentY)++;
}

void drawPattern_D1_S0(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0 = activeNode->children[0];
    MapNode *l2gc[3] = {Nil};
    
    l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
    l2gc[1] = (l1c0 && l1c0->numChildren > 1) ? l1c0->children[1] : Nil;
    l2gc[2] = (l1c0 && l1c0->numChildren > 2) ? l1c0->children[2] : Nil;

    gotoxy(MAP_START_X + 95, *currentY); printf("|\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("/-\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("\\`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("./\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 92, *currentY);
    printPaddedNode(l1c0, NODE_DISPLAY_WIDTH_L, FALSE, (0 == selectedIndex), FALSE); 
	printf("\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 93, *currentY); printf(".;/\\_-~`;'\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 80, *currentY); printf("_/```_-`\";.,/   :      \\_`_`'._``_\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 78, *currentY); printf("~                \\;`              -\\~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 77, *currentY); printf(".\\                .|                  /;\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 75, *currentY);
    printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("      ");
    printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("       ");
    printPaddedNode(l2gc[2], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("\n"); 
	(*currentY)++;
}

void drawPattern_D1_S1(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0 = activeNode->children[0]; 
	MapNode *l1c1 = activeNode->children[1]; 
	MapNode *l1c2 = activeNode->children[2];
    MapNode *l2gc[6] = {Nil};
    
    l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
    l2gc[1] = (l1c0 && l1c0->numChildren > 1) ? l1c0->children[1] : Nil;
    l2gc[2] = (l1c1 && l1c1->numChildren > 0) ? l1c1->children[0] : Nil;
    l2gc[3] = (l1c1 && l1c1->numChildren > 1) ? l1c1->children[1] : Nil;
    l2gc[4] = (l1c2 && l1c2->numChildren > 0) ? l1c2->children[0] : Nil;
    l2gc[5] = (l1c2 && l1c2->numChildren > 1) ? l1c2->children[1] : Nil;

    gotoxy(MAP_START_X + 79, *currentY); printf(".-~.-`_--;___-`-|.-~.-`_--;___-`-_-~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 73, *currentY); printf("_.,/                  /.                  |__\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 72, *currentY); printf("/                     |                       \\_-_;-_\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 64, *currentY); printf("_---;`~ ;                     \\;                              \\_-`-\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 60, *currentY);
    
    printPaddedNode(l1c0, NODE_DISPLAY_WIDTH_M, FALSE, (0 == selectedIndex), FALSE); 
	printf("                      ");
    printPaddedNode(l1c1, NODE_DISPLAY_WIDTH_M, FALSE, (1 == selectedIndex), FALSE); 
	printf("                         ");
    printPaddedNode(l1c2, NODE_DISPLAY_WIDTH_M, FALSE, (2 == selectedIndex), FALSE); 
	printf("\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 57, *currentY); printf("-_/.;   \\_.                         _/   \\_-`_                             ;|   \\._\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 53, *currentY); printf("_-`_|           \\                       |         \\                          ;|         \\._-.;,\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 49, *currentY); printf("-`-|                 |_.                  ./           |,                       .,/             \\.\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 47, *currentY); printf("_;/                       \\               _;|            |                      /                  \\.~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 45, *currentY);
    
    printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("             ");
    printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("    ");
    printPaddedNode(l2gc[2], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("    ");
    printPaddedNode(l2gc[3], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("         ");
    printPaddedNode(l2gc[4], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("           ");
    printPaddedNode(l2gc[5], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("\n"); 
	(*currentY)++;
}

void drawPattern_D1_S2(MapNode* activeNode, int selectedIndex, int* currentY) {
    int i, j, currentL2Index = 0;
    MapNode* l1Children[] = {activeNode->children[0], activeNode->children[1], activeNode->children[2], activeNode->children[3]};
    MapNode* l2gc[8] = {Nil};

    for (i = 0; i < 4; ++i) {
        if (l1Children[i] != Nil) {
            for (j = 0; j < l1Children[i]->numChildren && j < 2 && currentL2Index < 8; ++j) {
                l2gc[currentL2Index++] = l1Children[i]->children[j];
            }
        }
    }

    gotoxy(MAP_START_X + 64, *currentY); printf("_`>`__--`_;.;,.,.;_`;:`__--_/ | | \\_-`.,__---__;*~';;;:`>,.'\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 33, *currentY); printf(".;__-.;`-`;-__;;-`;``~~~.,.;-~/                 __-~`_-*_^_-/  :.,                         \\_-~*>,.;-__--~-`;.;,,;.~-`-\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 30, *currentY); printf("./                                          _.;~_./                  ~\\_-.,:_>;~`;*\\                                      \\._-\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 29, *currentY); printf("/;                                         |;                                        |;,                                      ,\\;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 27, *currentY);
    
    printPaddedNode(l1Children[0], NODE_DISPLAY_WIDTH_M, FALSE, (0 == selectedIndex), FALSE); 
	printf("                              ");
    printPaddedNode(l1Children[1], NODE_DISPLAY_WIDTH_M, FALSE, (1 == selectedIndex), FALSE); 
	printf("                               ");
    printPaddedNode(l1Children[2], NODE_DISPLAY_WIDTH_M, FALSE, (2 == selectedIndex), FALSE); 
	printf("                               ");
    printPaddedNode(l1Children[3], NODE_DISPLAY_WIDTH_M, FALSE, (3 == selectedIndex), FALSE); 
	printf("\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 25, *currentY); printf("-_/.;     \\_.                         ~`__.;_/     \\_-`_-:                        _-;>',_`!''__-~;                                -_/.   \\;[`_.\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 21, *currentY); printf(" _|             \\                       _|                   \\                     ;|                \\._-.;,                    _-`_|           \\.~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 18, *currentY); printf(" .;|                |_.                  ./                       |,               .,/                        \\.                  ./                  |,\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 16, *currentY); printf("  /                     \\               _;|                           |              /                            \\.~            _;|                       \\\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 15, *currentY);
    
    for (i = 0; i < 8; ++i) {
        printPaddedNode(l2gc[i], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
        if (i == 0) printf("          ");
        else if (i == 1) printf("   ");
        else if (i == 2) printf("                   ");
        else if (i == 3) printf("  ");
        else if (i == 4) printf("                   ");
        else if (i == 5) printf("     ");
        else if (i == 6) printf("           ");
    }
    printf("\n"); (*currentY)++;
}

void drawPattern_D2_S0_Children(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0 = (activeNode->numChildren > 0) ? activeNode->children[0] : Nil;
    MapNode *l1c1 = (activeNode->numChildren > 1) ? activeNode->children[1] : Nil;
    MapNode *l1c2 = (activeNode->numChildren > 2) ? activeNode->children[2] : Nil;
    MapNode *l2gc[3];
    l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
    l2gc[1] = (l1c1 && l1c1->numChildren > 0) ? l1c1->children[0] : Nil;
    l2gc[2] = (l1c2 && l1c2->numChildren > 0) ? l1c2->children[0] : Nil;

    gotoxy(MAP_START_X + 93, *currentY); printf(".;/\\_-~`;'\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 79, *currentY); printf("_/```_-`\";.,/   :       \\_`_`'._``_\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 79, *currentY); printf("~                \\;`              -\\~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 78, *currentY); printf(".\\                .|                  /;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 77, *currentY);
    
    printPaddedNode(l1c0, NODE_DISPLAY_WIDTH_M, FALSE, (0 == selectedIndex), FALSE); 
	printf("     ");
    printPaddedNode(l1c1, NODE_DISPLAY_WIDTH_M, FALSE, (1 == selectedIndex), FALSE); 
	printf("      ");
    printPaddedNode(l1c2, NODE_DISPLAY_WIDTH_M, FALSE, (2 == selectedIndex), FALSE); 
	printf("\n"); (*currentY)++;
	
    gotoxy(MAP_START_X + 80, *currentY); printf("|;              /;`               /.;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 79, *currentY); printf("~               `\\                \\-`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 79, *currentY); printf(".;              />                |.\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 78, *currentY); printf("\\`                .`                /`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 72, *currentY);
    
    printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("      ");
    printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("      ");
    printPaddedNode(l2gc[2], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("\n"); 
	(*currentY)++;
}

 void drawPattern_D2_S1_S2_Children(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0 = activeNode->children[0];
    MapNode *l1c1 = activeNode->children[1];
    MapNode *l2gc[2];
    l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
    l2gc[1] = (l1c1 && l1c1->numChildren > 0) ? l1c1->children[0] : Nil;

    gotoxy(MAP_START_X + 92, *currentY); printf("_-/` \\_.;-_\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 89, *currentY); printf("~           `\\\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 87, *currentY); printf(".;             />\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 87, *currentY); printf("\\`               .`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 84, *currentY);
    
    printPaddedNode(l1c0, NODE_DISPLAY_WIDTH_M, FALSE, (0 == selectedIndex), FALSE); 
	printf("     ");
    printPaddedNode(l1c1, NODE_DISPLAY_WIDTH_M, FALSE, (1 == selectedIndex), FALSE); 
	printf("\n"); 
	(*currentY)++;
	
    gotoxy(MAP_START_X + 85, *currentY); printf("|;               /;`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 87, *currentY); printf("~                `\\\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 85, *currentY); printf(".;                />\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 85, *currentY); printf("\\`                .`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 80, *currentY);
    
    printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("        ");
    printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
	printf("\n"); 
	(*currentY)++;
}

 void drawPattern_D3_To_Boss(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *secondaryBoss = activeNode->children[0];
    MapNode *l2gc[3] = {Nil};

    l2gc[0] = (secondaryBoss && secondaryBoss->numChildren > 0) ? secondaryBoss->children[0] : Nil;
    l2gc[1] = (secondaryBoss && secondaryBoss->numChildren > 1) ? secondaryBoss->children[1] : Nil;
    l2gc[2] = (secondaryBoss && secondaryBoss->numChildren > 2) ? secondaryBoss->children[2] : Nil;

    gotoxy(MAP_START_X + 95, *currentY); printf("|;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("/~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf(".;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("\\`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 89, *currentY);
    
    printPaddedNode(secondaryBoss, NODE_DISPLAY_WIDTH_L, FALSE, (0 == selectedIndex), FALSE);
    printf("\n");
    (*currentY)++;

    if (secondaryBoss && secondaryBoss->numChildren > 0) {
        if (secondaryBoss->numChildren == 3) {
            gotoxy(MAP_START_X + 93, *currentY); printf(".;/\\_-~`;'\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 79, *currentY); printf("_/```_-`\";.,/   :       \\_`_`'._``_\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 79, *currentY); printf("~                \\;`              -\\~\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 78, *currentY); printf(".\\                .|                  /;\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 77, *currentY);
            
            printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
            printf("     ");
            printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
            printf("      ");
            printPaddedNode(l2gc[2], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
            printf("\n");
            (*currentY)++;

        } else if (secondaryBoss->numChildren == 2) {
            gotoxy(MAP_START_X + 92, *currentY); printf("_-/` \\_.;-_\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 89, *currentY); printf("~           `\\\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 87, *currentY); printf(".;             />\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 87, *currentY); printf("\\`               .`\n");
            (*currentY)++;
            gotoxy(MAP_START_X + 84, *currentY);
            
            printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
            printf("     ");
            printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
            printf("\n");
            (*currentY)++;
        }
    }
}

void pembatas(int y_pos, int console_width, int line_length) {
    int startX = (console_width - line_length) / 2;
    int i;

    gotoxy(startX, y_pos);
    setColorLightYellow();
    for (i = 0; i < line_length; i++) {
        printf("-");
    }
    setColorDefault();
}

void printMapSeparator_Top(int x, int y) {
    setColorBrightWhite();
    gotoxy(x, y);     printf("                                                                                      %s/\\", CYAN);
    gotoxy(x, y + 1); printf("%s __                                                                                   %s\\/                                                                                   %s__", LYELLOW, CYAN, LYELLOW);
    gotoxy(x, y + 2); printf("%s(___________________________________________________________________________________/\\/\\/\\___________________________________________________________________________________)", LYELLOW);
    setColorDefault();
}

void printMapSeparator_Bottom(int x, int y) {
    setColorBrightWhite();
    gotoxy(x, y);     printf(" %s___________________________________________________________________________________      ___________________________________________________________________________________", LYELLOW);
    gotoxy(x, y + 1); printf("%s(__                                                                                 \\/\\/\\/                                                                                 __)", LYELLOW);
    gotoxy(x, y + 2); printf("                                                                                      %s/\\", CYAN);
    gotoxy(x, y + 3); printf("                                                                                      %s\\/", CYAN);
    setColorDefault();
}

void drawPattern_D4_Boss(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0, *l1c1, *l1c2;
    MapNode *l2gc[3] = {Nil};

    if (activeNode->numChildren == 3) {
        l1c0 = activeNode->children[0];
        l1c1 = activeNode->children[1];
        l1c2 = activeNode->children[2];
        l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
        l2gc[1] = (l1c1 && l1c1->numChildren > 0) ? l1c1->children[0] : Nil;
        l2gc[2] = (l1c2 && l1c2->numChildren > 0) ? l1c2->children[0] : Nil;
        drawPattern_D2_S0_Children(activeNode, selectedIndex, currentY);
    } else if (activeNode->numChildren == 2) {
        drawPattern_D2_S1_S2_Children(activeNode, selectedIndex, currentY);
    }
}

void drawPattern_Single_Child(MapNode* activeNode, int selectedIndex, int* currentY) {
    MapNode *l1c0 = activeNode->children[0];
    MapNode *l2gc[2] = {Nil};
    l2gc[0] = (l1c0 && l1c0->numChildren > 0) ? l1c0->children[0] : Nil;
    l2gc[1] = (l1c0 && l1c0->numChildren > 1) ? l1c0->children[1] : Nil;

    gotoxy(MAP_START_X + 95, *currentY); printf("|;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("/~\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf(".;\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 95, *currentY); printf("\\`\n"); 
	(*currentY)++;
    gotoxy(MAP_START_X + 91, *currentY);
    
    printPaddedNode(l1c0, NODE_DISPLAY_WIDTH_L, FALSE, (0 == selectedIndex), FALSE); printf("\n"); (*currentY)++;

    if (l1c0 && l1c0->numChildren > 0) {
        gotoxy(MAP_START_X + 92, *currentY); printf("_-/` \\_.;-_\n"); 
		(*currentY)++;
        gotoxy(MAP_START_X + 87, *currentY); printf("~           `\\\n"); 
		(*currentY)++;
        gotoxy(MAP_START_X + 85, *currentY); printf(".;             />\n"); 
		(*currentY)++;
        gotoxy(MAP_START_X + 85, *currentY); printf("\\`               .`\n");
		(*currentY)++;
        gotoxy(MAP_START_X + 84, *currentY);
        
        printPaddedNode(l2gc[0], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE);
		printf("     ");
        printPaddedNode(l2gc[1], NODE_DISPLAY_WIDTH_M, FALSE, FALSE, TRUE); 
		printf("\n");
		(*currentY)++;
    }
    
}
