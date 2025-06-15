#include "boss.h"

//										//
//										//
//           Create Function			//
//										//
//										//
void createPattern(patternQueue *Q){
	firstPtrn(*Q) = Nil;
	lastPtrn(*Q) = Nil;
}

patternAddress allocatePattern(char* action, int qty){
    patternAddress P = (patternAddress)malloc(sizeof(Pattern));
    if(P != Nil){
        actionName(P) = (char*)malloc((strlen(action) + 1) * sizeof(char));
        if(actionName(P) != Nil){
            strcpy(actionName(P), action);
            quantity(P) = qty;
            nextPtrn(P) = Nil;
        } else {
            free(P);
            P = Nil;
        }
    }
    return P;
}

Boss* createRandSecondaryBoss(){
	int num = (randNumGenerator() % 2);
	
	if (num == 0) {
		patternQueue unicorn;
		return createBoss("unicorn", 60, &unicorn);
	} else {
		patternQueue griffin;
		return createBoss("griffin", 60, &griffin);
	}
}


Boss* createBoss(const char* bossType, int Health, patternQueue *P){
	createPattern(P);
	Boss* newBoss = (Boss*)malloc(sizeof(Boss));
	if (newBoss == Nil){
		printf("Error: Memory Allocation failed");
		return Nil;
	}
	
	bossType(newBoss) = (char*)malloc(strlen(bossType) + 1);
	if (bossType(newBoss) == Nil){
		printf("Error: memory allocation for mobType");
		return Nil;
	}
	strcpy(bossType(newBoss), bossType);
	if (strcmp(bossType(newBoss), "dragoon") == 0) {
		dragoonPattern(P, newBoss);
	} else if (strcmp(bossType(newBoss), "unicorn") == 0) {
		unicornPattern(P, newBoss);
	} else if (strcmp(bossType(newBoss), "griffin") == 0) {
		griffinPattern(P, newBoss);
	}
		
	currBossAction(newBoss) = firstPtrn(*P);
	bossPatterns(newBoss) = firstPtrn(*P);
	bossHealth(newBoss) = Health;
	
	return newBoss;
	
}

int randAttackValue(const char* bossType){
	int min, max, value;
	if (strcmp(bossType, "dragoon") == 0){
		min = 18;
		max = 24;
		value = rand() % (max - min  + 1) + min;
	} else if (strcmp(bossType, "griffin") == 0 || strcmp(bossType, "unicorn") == 0){
		min = 12;
		max = 16;
		value = rand() % (max - min  + 1) + min;
	}
	return value;
}

//										//
//										//
//           Delete Function			//
//										//
//										//

void deallocatePattern(patternAddress P){
    if(P != Nil){
        if(actionName(P) != Nil){
            free(actionName(P));
        }
        free(P);
    }
}

void clearPatternQueue(patternQueue *Q){
    char tempAction[100];
    int tempQty;
    while(!isEmptyPattern(*Q)){
        dequeuePattern(Q, tempAction, &tempQty);
    }
}

void deleteBoss(Boss* boss){
    if(boss != Nil){
        if(bossType(boss) != Nil){
            free(bossType(boss));
        }
        
        patternAddress current = bossPatterns(boss);
        while(current != Nil){
            patternAddress next = nextPtrn(current);
            deallocatePattern(current);
            current = next;
        }
        
        free(boss);
    }
}


//										//
//										//
//             Read Function			//
//										//
//										//

boolean isEmptyPattern(patternQueue Q){
    return (firstPtrn(Q) == Nil);
}

void printPatternQueue(patternQueue Q){
    patternAddress current = firstPtrn(Q);
    printf("Pattern Queue: \n");
    while(current != Nil){
        printf("[%s:%d]\n", actionName(current), quantity(current));
		printf("   |   \n");
        printf("   V   \n");
        
        current = nextPtrn(current);
    } 
    printf("  End");
}

void getCurrentBossAction(Boss* boss, char* action, int* qty){
	if (currBossAction(boss) != Nil){
		strcpy(action, actionName(currBossAction(boss)));
		*qty = quantity(currBossAction(boss));
	}
}

void advanceBossAction(Boss* boss){
    if (currBossAction(boss) != Nil){
        patternAddress toRemove = currBossAction(boss);
        patternAddress nextAction = nextPtrn(toRemove);
        
        // If this is the last pattern, regenerate the pattern
        if (nextAction == Nil) {
            // Free current pattern
            deallocatePattern(toRemove);
            
            // Regenerate pattern based on boss type
            patternQueue newPattern;
            createPattern(&newPattern);
            
            if (strcmp(bossType(boss), "unicorn") == 0) {
                unicornPattern(&newPattern, boss);
            } else if (strcmp(bossType(boss), "griffin") == 0) {
                griffinPattern(&newPattern, boss); // when implemented
            } else if (strcmp(bossType(boss), "dragoon") == 0) {
                dragoonPattern(&newPattern, boss); // when implemented
            }
            
            bossPatterns(boss) = firstPtrn(newPattern);
            currBossAction(boss) = firstPtrn(newPattern);
        } else {
            // Move to next pattern and remove current
            currBossAction(boss) = nextAction;
            
            // Update the pattern queue structure
            if (toRemove == bossPatterns(boss)) {
                bossPatterns(boss) = nextAction;
            } else {
                // Find previous pattern
                patternAddress prev = bossPatterns(boss);
                while (prev != Nil && nextPtrn(prev) != toRemove) {
                    prev = nextPtrn(prev);
                }
                if (prev != Nil) {
                    nextPtrn(prev) = nextAction;
                }
            }
            deallocatePattern(toRemove);
        }
    }
}

void printBossStats(Boss* boss, int startCol, int startRow) {
    if (boss == Nil) {
        return;
    }
    int i = 0;
    gotoxy(startCol, startRow - 1);
    setColorLightRed();
    printf("=========[Boss Status]=========");
    gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+----------------------------+");
    
    gotoxy(startCol, startRow + i); i++;
    setColorLightRed();
	printf("  ENEMY	[%s]", bossType(boss));
    
	gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+----------------------------+");
        
	gotoxy(startCol, startRow + i); i++;
    setColorGreen();
    printf("  HEALTH	[%d]", bossHealth(boss));
    
    gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+----------------------------+\n");
	
	gotoxy(startCol, startRow + i); i++; 
    setTextColor((COLOR_RED * 16) + COLOR_LIGHT_YELLOW);
    printf("         NEXT ACTION:         ", bossHealth(boss));
    
    gotoxy(startCol, startRow + i); i++;
    setTextColor((COLOR_RED * 16) + COLOR_LIGHT_YELLOW);
    printf("         [%s][%d]         ", actionName(currBossAction(boss)), quantity(currBossAction(boss)));
    
    gotoxy(startCol, startRow + i); i++;
    setColorDefault();
	printf("+----------------------------+\n");
}

void printBoss(int startCol, int startRow, Boss* boss, boolean state) {
	int i;
	if (!strcmp(bossType(boss), "griffin")) {
        i = 1;
        startRow -= 4;
        setColorLightYellow();
        if (!state) setColorRed();
        gotoxy(startCol, startRow + i); i++;
		printf("                           _");
		gotoxy(startCol, startRow + i); i++;
		printf("                          _)..-.");
		gotoxy(startCol, startRow + i); i++;
		printf("         .-.__,___,_.-=-. )\\`  a`\\_");
		gotoxy(startCol, startRow + i); i++;
		printf("     .-.__\\__,__,__.-=-. `/  \\     `\\");
		gotoxy(startCol, startRow + i); i++;
		printf("     {~,-~-,-~.-~,-,;;;;\\ |   '--;`)/");
		gotoxy(startCol, startRow + i); i++;
		printf("      \\-,~_-~_-,~-,(_(_(;\\/   ,;/");
		gotoxy(startCol, startRow + i); i++;
		printf("       \",-.~_,-~,-~,)_)_)'.  ;;(");
		gotoxy(startCol, startRow + i); i++;
		printf("         `~-,_-~,-~(_(_(_(_\\  `;\\");
		gotoxy(startCol, startRow + i); i++;
		printf("   ,          `\"~~--,)_)_)_)\\_   \\");
		gotoxy(startCol, startRow + i); i++;
		printf("   |\\              (_(_/_(_,   \\  ;");
		gotoxy(startCol, startRow + i); i++;
		printf("   \\ '-.       _.--'  /_/_/_)   | |");
		gotoxy(startCol, startRow + i); i++;
		printf("    '--.\\    .'          /_/    | |");
		gotoxy(startCol, startRow + i); i++;
		printf("        ))  /       \\      |   /.'");
		gotoxy(startCol, startRow + i); i++;
		printf("       //  /,        | __.'|  ||");
		gotoxy(startCol, startRow + i); i++;
		printf("      //   ||        /`    (  ||");
		gotoxy(startCol, startRow + i); i++;
		printf("     ||    ||      .'       \\ \\\\");
		gotoxy(startCol, startRow + i); i++;
		printf("     ||    ||    .'_         \\ \\\\");
		gotoxy(startCol, startRow + i); i++;
		printf("      \\\\   //   / _ `\\        \\ \\\\__");
		gotoxy(startCol, startRow + i); i++;
		printf("       \\'-'/(   _  `\\,;        \\ '--:,");
		gotoxy(startCol, startRow + i); i++;
		printf("        `\"`  `\"` `-,,;         `\"`\",,;"); 
	} else if (!strcmp(bossType(boss), "unicorn")) {
    	i = 1;
     	startCol += 10; 
       	startRow -= 8;
       	if (!state) setColorRed();
       	gotoxy(startCol, startRow + i); i++;
		printf("\033[1;35m    \\");
       	gotoxy(startCol, startRow + i); i++;
		printf("     \\");
       	gotoxy(startCol, startRow + i); i++;
		printf("      \\\\");
       	gotoxy(startCol, startRow + i); i++;
		printf("       \\\\");
       	gotoxy(startCol, startRow + i); i++;
		printf("        \033[0m>\033[1;35m\\\033[0m/7\033[35m,,\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("    _.-(6'  \\\\\033[35m(;\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("   (=___._/` \\\033[35m))),\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("        )  \\ |\033[35m((((;\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("       /   / |\033[35m)))));\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("      /    > /\033[35m((((((\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("     j    < _\\\033[35m))))))\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf(" _.-' :      ``.\033[35m((((\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf(" \\ r=._\\        `.\033[35m;'\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("<`\\\\_  \\         .`-.");
       	gotoxy(startCol, startRow + i); i++;
		printf(" \\ r-7  `-. ._  ' .  `\\ \033[35m   ,'mm'.\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("  \\`,      `-.`7  7)   )\\_,-\033[35m_.,-(\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("   \\/         \\|  \\'  /;{,\033[35m'-'}\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("              ||    .'\033[35m'\033[0m");
       	gotoxy(startCol, startRow + i); i++;
		printf("               \\\\  (");
       	gotoxy(startCol, startRow + i); i++;
		printf("               >\\  >");
       	gotoxy(startCol, startRow + i); i++;
		printf("            ,.-' >.'");
       	gotoxy(startCol, startRow + i); i++;
		printf("           <.'_.''");
       	gotoxy(startCol, startRow + i); i++;
		printf("             <'");
	} else if (!strcmp(bossType(boss), "dragoon")){
		i = 1;
		startCol += 8;
		startRow -= 13;
		setColorLightRed();
		if (!state) setColorGreen();
		gotoxy(startCol, startRow + i); i++;
		printf("        //                                \\\\\n");
		gotoxy(startCol, startRow + i); i++;
		printf("       ///                                 \\|");
		gotoxy(startCol, startRow + i); i++;
		printf("      /( \\                                  )\\");
		gotoxy(startCol, startRow + i); i++;
		printf("      \\\\  \\_                               //)");
		gotoxy(startCol, startRow + i); i++;
		printf("       \\\\  :\\__                           ///");
		gotoxy(startCol, startRow + i); i++;
		printf("        \\\\     )                         // \\");
		gotoxy(startCol, startRow + i); i++;
		printf("         \\\\:  /                         // |/");
		gotoxy(startCol, startRow + i); i++;
		printf("          \\\\ / \\                       //  \\");
		gotoxy(startCol, startRow + i); i++;
		printf("           /)   \\   __..-'           (|  \\|");
		gotoxy(startCol, startRow + i); i++;
		printf("          //     /'' _.'              \\ \\  \\");
		gotoxy(startCol, startRow + i); i++;
		printf("         /|       \\ \\________          \\ | /");
		gotoxy(startCol, startRow + i); i++;
		printf("        (| _ _  __/          '-.       ) /.'");
		gotoxy(startCol, startRow + i); i++;
		printf("         \\\\ .  '-.__            \\_    / / \\");
		gotoxy(startCol, startRow + i); i++;
		printf("          \\\\'.     > --. '.     \\  / / /");
		gotoxy(startCol, startRow + i); i++;
		printf("           \\ \\      \\     \\  \\     .' /.'");
		gotoxy(startCol, startRow + i); i++;
		printf("            \\ \\  '._ /     \\ )    / .' |");
		gotoxy(startCol, startRow + i); i++;
		printf("             \\ \\_     \\_   |    .'_/ __/");
		gotoxy(startCol, startRow + i); i++;
		printf("              \\  \\      \\_ |   / /  / \\");
		gotoxy(startCol, startRow + i); i++;
		printf("               \\  \\       / _.' /  /    \\");
		gotoxy(startCol, startRow + i); i++;
		printf("               \\   |     /.'   / .'      '-,_");
		gotoxy(startCol, startRow + i); i++;
		printf("                \\   \\  .'   .'/              \\");
		gotoxy(startCol, startRow + i); i++;
		printf("   /\\    /\\      ) __(    /.'           \\    |");
		gotoxy(startCol, startRow + i); i++;
		printf("  | \\_// \\    (.'      _/               |    |");
		gotoxy(startCol, startRow + i); i++;
		printf("  \\/_  __  /--'`    ,                   __/  /");
		gotoxy(startCol, startRow + i); i++;
		printf("  (b\\ /d)  \\  '.   :            \\.-'/ \\	  /");
		gotoxy(startCol, startRow + i); i++;
		printf("  /:/:  _      ) :        (      /.'/-'| _ /");
		gotoxy(startCol, startRow + i); i++;
		printf(" /:/: _/ \\ >  __,.----.\\    /        (/(/(/");
		gotoxy(startCol, startRow + i); i++;
		printf(" (\\./)v ^)/--'    _/  __/ |   /");
		gotoxy(startCol, startRow + i); i++;
		printf("  VvvV  ^//`    _.-' _.'     \\   \\");
		gotoxy(startCol, startRow + i); i++;
		printf("   /^--^//     (((/->/        |   /");
		gotoxy(startCol, startRow + i); i++;
		printf("   'M_M,'        ~='          \\  |");
		gotoxy(startCol, startRow + i); i++;
		printf("                              | |,,,,");
		gotoxy(startCol, startRow + i); i++;
		printf("                              \\  \\  /");
		gotoxy(startCol, startRow + i); i++;
		printf("                               '.)\n");
	}
}

void printBossAttack(int startCol, int startRow, char* state) {
	int i = 0;
	if (!strcmp(state, "dragoon")){
		int dragoonCol = startCol + 15;
		int dragoonRow = startRow + 15;
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("\033[1;31m                            /  , /");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                          ,/' /`'");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                         /(/`'   _");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                        f'/)  ,-'");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                       /    ,'");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                      f,/  /");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                      /''  7");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                     / ,f /");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                \033[0m\033[31m)\033[1;31m   / / |J");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("                   7,(\033[0m ;\033[1;31m|j\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("         \033[31m,       \033[33m(\033[1;33m. ''`/\033[0m\033[33m ('\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("             \033[33m`    \033[1;33m)`-'/ l\033[0m\033[33m `(\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("	     \033[33m(  (    \033[1;33m) '   ' (_,\033[0m\033[33m'  \033[31m)      (\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("\033[31m	 (     \033[1;33m,)  7`  /  /,  (,\033[0m\033[33m (       '    \033[31m(\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("\033[31m  	 ,  \033[33m) (\033[1;33m,- `-'  /  (,   -') \033[0m\033[33m(}'_.)_-  )\033[31m'\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("\033[31m   ).,'\033[33m(_ ( `-_(\033[1;33m,_,'_(_(__ )_, _`-_,\033[0m\033[33m _-;-)\033[31m(,.__.,.,''\033[0m");
		gotoxy(dragoonCol, dragoonRow + i); i++;
		printf("\033[31mC_ ( `-_(,_,\033[33m'n(_(__ )_, m`-_, _';,.^nm''\033[31m_-+==.,;;o''wm\033[0m");
	} else if (!strcmp(state, "unicorn")) {
		int unicornCol = startCol + 25;
		int unicornRow = startRow + 13;
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("\033[35m               ,,))))))));,");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("           __)))))))))))))),");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("\033[1;33m\\|/\033[0m       \033[35m-\\(((((''''((((((((.\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("\033[1;33m-*\033[0m\033[1;35m-==//////\033[0m\033[35m((\033[0m''  .     \033[35m`)))))),\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("\033[1;33m/|\\\033[0m      \033[35m))\033[0m| o    ;-.    \033[35m'(((((                                  ,(,\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("         \033[35m(\033[0m `|    /  )    ;\033[35m))))'                               ,_))^;(~\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("            |   |   |   ,\033[35m))((((\033[0m_     _____-------.        \033[35m%,;(;(>';'\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("            o_);   ;    \033[35m)))(((\033[0m` ---  ::           \\      \033[35m%%~~)(v;(('~\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("                  ;    ''''`         `:       `:::|\\,__,%%    \033[35m);`'; ~\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("                 |   _                )     /      `:|`----'     \033[35m`-'\033[0m");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("           ______/\\/~    |                 /        /");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("         /~;;.____/;;'  /          ___--,-(   `;;;/");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("        / //  _;______;'------~~~~~    /;;/\\    /");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("       //  | |                        / ;   \\;;,\\");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("      (<_  | ;                      /',/-----'  _>");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("       \\_| ||_                     //~;~~~~~~~~~");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("           `\\_|                   (,~~");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("                                   \\~\\");
		gotoxy(unicornCol, unicornRow + i); i++;
		printf("                                    ~~");
	} else if (!strcmp(state, "griffin")) {
		int griffinCol = startCol + 25;
		int griffinRow = startRow + 13;
		setColorLightYellow();
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("        _____,    _..-=-=-=-=-====--,");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("     _.'a   /  .-',___,..=--=--==-'`");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("    ( _     \\ /  //___/-=---=----'");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("     ` `\\    /  //---/--==----=-'");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("  ,-.    | / \\_//-_.'==-==---='");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf(" (.-.`\\  | |'../-'=-=-=-=--'");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("  (' `\\`\\| //_|-\\.`;-~`~,        _");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("       \\ | \\,,_\\.'        \\     .'_`\\");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("        `\\            ,    , \\    || `\\\\");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("          \\    /   .--\\    \\ '..'/  / |");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("          /  /---'   \\ \\   |'---'   \\/");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("         / /'          \\ ;-. \\");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("      __/ /           __) \\ ) `|");
		gotoxy(griffinCol, griffinRow + i); i++;
		printf("    ((='--;)         (,/(,/");
	}
}

void executeBossAction(Boss* boss, char* action, int* qty){
	getCurrentBossAction(boss, action, qty);
	advanceBossAction(boss);
}


//										//
//										//
//           Update Function			//
//										//
//										//
void enqueuePattern(patternQueue *Q, char* action, int qty){
    patternAddress P = allocatePattern(action, qty);
    Boss* B = firstPtrn(*Q);
    if(P != Nil){
        if(isEmptyPattern(*Q)){
            firstPtrn(*Q) = P;
            lastPtrn(*Q) = P;
        } else {
            nextPtrn(lastPtrn(*Q)) = P;
            lastPtrn(*Q) = P;
        }
    }
}

void dequeuePattern(patternQueue *Q, char* action, int *qty){
    if(!isEmptyPattern(*Q)){
        patternAddress P = firstPtrn(*Q);
        strcpy(action, actionName(P));
        *qty = quantity(P);
        
        firstPtrn(*Q) = nextPtrn(P);
        if(firstPtrn(*Q) == Nil){
            lastPtrn(*Q) = Nil;
        }
        
        deallocatePattern(P);
    }
}

void bossHeal(Boss* boss, int heal){
	bossHealth(boss) += heal;
	if (bossHealth(boss) > 80 && !strcmp(bossType(boss), "dragoon")) {
		bossHealth(boss) = 80;
	} else if (bossHealth(boss) > 60) {
		bossHealth(boss) = 60;
	}
}

void attackedBoss(int damage, Boss* boss){
	if (boss != Nil) {
		bossHealth(boss) -= damage;
	}
}

//=======================================================
//=======================================================
//=======================================================
//===================BOSS PATTERN========================
//=======================================================
//=======================================================

void unicornPattern(patternQueue *P, Boss* boss){
	int DamageAttack[9], i;
	for (i = 0; i < 9; i++){
		DamageAttack[i] = randAttackValue("unicorn");
	} 
	
	if (bossHealth(boss) < 30){
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[0]);
		enqueuePattern(P, "Attack", DamageAttack[1]);
		enqueuePattern(P, "Attack", DamageAttack[2]);
		enqueuePattern(P, "Attack", DamageAttack[3]);
		enqueuePattern(P, "Attack", DamageAttack[4]);
		enqueuePattern(P, "Attack", DamageAttack[5]);
		enqueuePattern(P, "Attack", DamageAttack[6]);
		enqueuePattern(P, "Attack", DamageAttack[7]);
		enqueuePattern(P, "Attack", DamageAttack[8]);
	} else {
		enqueuePattern(P, "Attack", DamageAttack[0]);
		enqueuePattern(P, "Attack", DamageAttack[1]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[2]);
		enqueuePattern(P, "Attack", DamageAttack[3]);
		enqueuePattern(P, "Attack", DamageAttack[4]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[5]);
		enqueuePattern(P, "Attack", DamageAttack[6]);
		enqueuePattern(P, "Attack", DamageAttack[7]);
		enqueuePattern(P, "Attack", DamageAttack[8]);
		enqueuePattern(P, "Heal", 20);
	}
	
}
	
void griffinPattern(patternQueue *P, Boss* boss){
	int DamageAttack[9], i;
	for (i = 0; i < 8; i++){
		DamageAttack[i] = randAttackValue("griffin");
	} 
	
	if (bossHealth(boss) < 30){
		enqueuePattern(P, "Attack", DamageAttack[0]);
		enqueuePattern(P, "Attack", DamageAttack[1]);
		enqueuePattern(P, "Attack", DamageAttack[2]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[3]);
		enqueuePattern(P, "Attack", DamageAttack[4]);
		enqueuePattern(P, "Attack", DamageAttack[5]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[6]);
		enqueuePattern(P, "Attack", DamageAttack[7]);
		enqueuePattern(P, "Attack", DamageAttack[0]);
	} else {
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[0]);
		enqueuePattern(P, "Attack", DamageAttack[1]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[2]);
		enqueuePattern(P, "Attack", DamageAttack[3]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[4]);
		enqueuePattern(P, "Attack", DamageAttack[5]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[6]);
		enqueuePattern(P, "Attack", DamageAttack[7]);
	}
}

void dragoonPattern(patternQueue *P, Boss* boss){
		int DamageAttack[9], i;
	for (i = 0; i < 8; i++){
		DamageAttack[i] = randAttackValue("dragoon");
	} 
	
	if (bossHealth(boss) < 40){
		enqueuePattern(P, "Heal", 80);
		enqueuePattern(P, "Attack", DamageAttack[0]);
		enqueuePattern(P, "Attack", DamageAttack[1]);
		enqueuePattern(P, "Attack", DamageAttack[2]);
		enqueuePattern(P, "Attack", DamageAttack[3]);
		enqueuePattern(P, "Attack", DamageAttack[4]);
		enqueuePattern(P, "Attack", DamageAttack[5]);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Heal", 20);
		enqueuePattern(P, "Attack", DamageAttack[6]);
		enqueuePattern(P, "Attack", DamageAttack[7]);
		enqueuePattern(P, "Attack", DamageAttack[0]);
	} else {
		enqueuePattern(P, "Attack", DamageAttack[0]);
		enqueuePattern(P, "Attack", DamageAttack[1]);
		enqueuePattern(P, "Attack", DamageAttack[2]);
		enqueuePattern(P, "Attack", DamageAttack[3]);
		enqueuePattern(P, "Attack", DamageAttack[4]);
		enqueuePattern(P, "Attack", DamageAttack[5]);
		enqueuePattern(P, "Attack", DamageAttack[6]);
		enqueuePattern(P, "Attack", DamageAttack[7]);
	}
	
}
	

