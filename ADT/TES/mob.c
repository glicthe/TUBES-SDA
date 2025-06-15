#include "mob.h"


void createMobContainer(mobContainer *C){
	firstMob(*C) = Nil;
	currentMob(*C) = Nil;
}

void moveLeftMob(mobContainer *C) {
    if (currentMob(*C) && mobPrev(currentMob(*C))) {
        currentMob(*C) = mobPrev(currentMob(*C));
    } else if (currentMob(*C) && mobPrev(currentMob(*C)) == Nil) {
        moveToLastMob(C);
    }
}

void moveRightMob(mobContainer *C) {
    if (currentMob(*C) && mobNext(currentMob(*C))) {
        currentMob(*C) = mobNext(currentMob(*C));
    } else if (currentMob(*C) && mobNext(currentMob(*C)) == Nil) {
        moveToFirstMob(C);
    }
}

void moveToFirstMob(mobContainer *C) {
    if (firstMob(*C)) {
        currentMob(*C) = firstMob(*C);
    }
}

void moveToLastMob(mobContainer *C) {
    if (firstMob(*C)) {
        mobAddress last = firstMob(*C);
        while (mobNext(last) != Nil) {
            last = mobNext(last);
        }
        currentMob(*C) = last;
    }
}

int countMob(mobContainer C){
	int count = 0;
    mobAddress P;
	if (firstMob(C) != Nil){
	    P = firstMob(C);
	    for (;;) {
	        if (P == Nil){
	            break;
	        } else {
	            count++;
	            P = mobNext(P);
	        }
	    } 
	}
	return (count);
}

mobAddress createMob(const char* mobType, int health, mobContainer C){
    mobAddress newMob = (mobAddress)malloc(sizeof(Mob));
    if (newMob == Nil){
        printf("Error: Memory Allocation failed");
        return Nil;
    }
    
    mobPrev(newMob) = Nil;
    mobNext(newMob) = Nil;
    
    mobType(newMob) = (char*)malloc(strlen(mobType) + 1);
    if (mobType(newMob) == Nil){
        printf("Error: memory allocation for mobType");
        return Nil;
    }
    strcpy(mobType(newMob), mobType);
    
    mobActionType(newMob) = Nil;
    mobActionQuantity(newMob) = 0;
    
    mobHealth(newMob) = health;

    return newMob;
}

void InsertLast(mobContainer *C, mobAddress selectedMob) {
    if (firstMob(*C) != Nil) {
        mobAddress Last = firstMob(*C);
        while (mobNext(Last) != Nil) {
            Last = mobNext(Last);
        }
        mobNext(Last) = selectedMob;           
        mobPrev(selectedMob) = Last;           
        mobNext(selectedMob) = Nil;            
    } else {
        firstMob(*C) = selectedMob;            
        mobPrev(selectedMob) = Nil;            
        mobNext(selectedMob) = Nil;
        currentMob(*C) = selectedMob;      
    }
    
    // Assign mobCounter based on current count
    mobAddress temp = firstMob(*C);
    int counter = 1;
    while (temp != Nil) {
        mobCounter(temp) = counter++;
        temp = mobNext(temp);
    }
}

void deleteMob(mobContainer* container, mobAddress mobToDelete) {
    if (container == NULL || mobToDelete == NULL) {
        return; // Exit early if invalid parameters
    }
    
    if (mobType(mobToDelete) != NULL) {
        free(mobType(mobToDelete));
    }
    if (mobActionType(mobToDelete) != NULL) {
        free(mobActionType(mobToDelete));
    }
    
    if (mobPrev(mobToDelete) == NULL && mobNext(mobToDelete) == NULL) {
        firstMob(*container) = NULL;
        currentMob(*container) = NULL;
    }
    else if (mobPrev(mobToDelete) == NULL) {
        firstMob(*container) = mobNext(mobToDelete);
        mobPrev(mobNext(mobToDelete)) = NULL;
        
        if (currentMob(*container) == mobToDelete) {
            currentMob(*container) = mobNext(mobToDelete);
        }
    }
    
    else {
        mobNext(mobPrev(mobToDelete)) = mobNext(mobToDelete);
        
        if (mobNext(mobToDelete) != NULL) {
            mobPrev(mobNext(mobToDelete)) = mobPrev(mobToDelete);
        }
        
        if (currentMob(*container) == mobToDelete) {
            currentMob(*container) = (mobNext(mobToDelete) != NULL) ? mobNext(mobToDelete) : mobPrev(mobToDelete);
        }
    }
    
    free(mobToDelete);
}

void deleteCurrentMob(mobContainer* container) {
    if (container == NULL || currentMob(*container) == NULL) {
        return; // Nothing to delete
    }
    
    mobAddress mobToDelete = currentMob(*container);
    
    if (mobNext(mobToDelete) != NULL) {
        currentMob(*container) = mobNext(mobToDelete);
    } else if (mobPrev(mobToDelete) != NULL) {
        currentMob(*container) = mobPrev(mobToDelete);
    } else {
        currentMob(*container) = NULL;
    }
    
    deleteMob(container, mobToDelete);
}

void checkMobHealth(mobContainer *C){
	mobAddress curr = currentMob(*C);
	
	if (curr != Nil && mobHealth(curr) <= 0){
		deleteCurrentMob(C);
	}	
}

mobAddress search(mobContainer C, const char* mobType, int mobPosition){
    mobAddress mob;
    boolean found = false;
    mob = firstMob(C);
    while ((mob != Nil) && (!found)){
        if (strcmp(mobType(mob), mobType) == 0 && mobCounter(mob) == mobPosition){
            found = true;
        } else {
            mob = mobNext(mob);
        }
    } 
    return (mob);
}

void attacked (int damage, mobContainer *C){
	if (currentMob(*C) != Nil){
		mobHealth(currentMob(*C)) -= damage;
	}
}

void mobheal(mobAddress *selectedMob){
	if (*selectedMob != Nil){
		mobHealth(*selectedMob) += mobActionQuantity(*selectedMob);
		if (mobHealth(*selectedMob) > 14 && strcmp(mobType(*selectedMob), "Ghost") == 0 ){
			mobHealth(*selectedMob) = 14; 
		} else if (mobHealth(*selectedMob) > 16 && strcmp(mobType(*selectedMob), "Goblin") == 0){
			mobHealth(*selectedMob) = 16; 
		}
	}
}

int attack(mobAddress selectedMob){
	if (selectedMob != Nil){
		return mobActionQuantity(selectedMob);
	}
}
 

void randAction(mobContainer C){
	mobAddress selectedMob = firstMob(C);
	
	while (selectedMob != Nil){
		int value = randNumGenerator();
		if (value <= 7) {
			free(mobActionType(selectedMob));
			mobActionType(selectedMob) = (char*)malloc(strlen("attack") + 1);
			strcpy(mobActionType(selectedMob), "attack");
			
			if (strcmp(mobType(selectedMob), "Ghost") == 0){
				mobActionQuantity(selectedMob) = 5;
			} else if (strcmp(mobType(selectedMob), "Goblin") == 0){
				mobActionQuantity(selectedMob) = 7;			
			}
		} else {
			free(mobActionType(selectedMob));
			mobActionType(selectedMob) = (char*)malloc(strlen("heal") + 1);
			strcpy(mobActionType(selectedMob), "heal");
			
			mobActionQuantity(selectedMob) = 5;
		}
		selectedMob = mobNext(selectedMob);
	}
}

void printMobContainer(mobContainer C, int startCol, int startRow) {
    mobAddress current = firstMob(C);
    gotoxy(startCol, startRow - 1);
    setColorLightRed();
    printf("=========[Mob Status]=========");
	
	int i = 0;
    if (current == Nil) {
    	gotoxy(startCol, startRow + i);
        printf("(Empty)");
        return;
    }

    
    while (current != Nil) {
    	gotoxy(startCol, startRow + i); i++;
    	setColorBrightWhite();
    	printf("[%d]", mobCounter(current));
    	
		gotoxy(startCol, startRow + i); i++;
    	setColorDefault();
		printf("+----------------------------+");
		
		gotoxy(startCol, startRow + i); i++;
        setColorLightRed();
        printf("  ENEMY	[%s]", mobType(current));
        
		gotoxy(startCol, startRow + i); i++;
        setColorDefault();
		printf("+----------------------------+");
        
		gotoxy(startCol, startRow + i); i++;
        setColorGreen();
		printf("  HEALTH	[%d]", mobHealth(current));
        
		gotoxy(startCol, startRow + i); i++;
        setColorDefault();
		printf("+----------------------------+");
        
		gotoxy(startCol, startRow + i); i++;
        setColorBrightWhite();
		printf("  NEXT TURN => %s [%d]", mobActionType(current), mobActionQuantity(current));
        
		gotoxy(startCol, startRow + i); i++;
        setColorDefault();
		printf("+----------------------------+\n");
		i++;
        current = mobNext(current);
    }
}

void printCurrentMob(mobContainer C, int startCol, int startRow) {
    int i = 23;
    if (currentMob(C)) {
        gotoxy(startCol, startRow + i); i++;
        setColorLightRed();
        printf("=======[Current Mob]=======\n");
        
        gotoxy(startCol, startRow + i); i++;
        setColorDefault();
        printf("+---------------------------+");
        
        gotoxy(startCol, startRow + i); i++;
        setColorLightRed();
        printf("  ENEMY	[%s]", mobType(currentMob(C)));
        
        gotoxy(startCol, startRow + i); i++;
        setColorDefault();
        printf("+---------------------------+");
        
        gotoxy(startCol, startRow + i); i++;
        setColorGreen();
        printf("  HEALTH	[%d]", mobHealth(currentMob(C)));
        
        gotoxy(startCol, startRow + i); i++;
        setColorDefault();
        printf("+---------------------------+");
        
        gotoxy(startCol, startRow + i); i++;
        setColorBrightWhite();
        printf("  NEXT TURN => %s [%d]", mobActionType(currentMob(C)), mobActionQuantity(currentMob(C)));
        
        gotoxy(startCol, startRow + i); i++;
        setColorDefault();
        printf("+---------------------------+");
    } else {
        gotoxy(startCol, startRow + 3);
        printf("No mob selected.\n");
    }
}

void printMob(int startCol, int startRow, int columns, int rows, mobContainer C, boolean state) {
	int i;
	mobAddress current = firstMob(C);
	
	if (current != Nil) {
		startCol = columns - 125;
		startRow = rows / 3;
		while (current != Nil) {
			i = 1;
			if (!strcmp(mobType(current), "Goblin")) {
				setColorLightCyan();
				gotoxy(startCol, startRow + i); i++;
				printf(" [%d] ", mobCounter(current));
				if (!state) setColorRed();
				else setColorGreen();
			} else if (!strcmp(mobType(current), "Ghost")) {
				i = 1;
				setColorLightCyan();
				gotoxy(startCol, startRow + i); i++;
				printf(" [%d] ", mobCounter(current));
				if (!state) setColorRed();
				else setColorBrightWhite(); 
			}
			if (current == currentMob(C) && state){
				gotoxy(startCol, startRow);
				setColorGray();
			}
	
			if (!strcmp(mobType(current), "Goblin")){
				gotoxy(startCol, startRow + i); i++;
				printf("            _.._     \n");
				gotoxy(startCol, startRow + i); i++;
				printf("     (`._.\"      \"._.')\n");
				gotoxy(startCol, startRow + i); i++;
				printf("      '._          _.'              /\\\n");
				gotoxy(startCol, startRow + i); i++;
				printf("       | /`-.  .-'\\ |             .'.'\n");
				gotoxy(startCol, startRow + i); i++;
				printf("       |(_()_\\/_()_)| __         ( (\n");
				gotoxy(startCol, startRow + i); i++;
				printf("       ;   ,____,   ;'  `\\        ) )\n");
				gotoxy(startCol, startRow + i); i++;
				printf("        \\  /VvvV\\  /    \\  \\.__   / /\n");
				gotoxy(startCol, startRow + i); i++;
				printf("      _/`'._----_.'      \\  \\  `\\/ /\n");
				gotoxy(startCol, startRow + i); i++;
				printf("     /  ._-_`--'     .----.  \\    /\n");
				gotoxy(startCol, startRow + i); i++;
				printf("    / _/      )     /  .------\\`.|  \n");
				gotoxy(startCol, startRow + i); i++;
				printf("   / / |    ``    _,|  (_`-'_\\   \\\n");
				gotoxy(startCol, startRow + i); i++;
				printf("  / /   \\   \\`\"\"`    \\\\\\\\     \\   \\\n");
				gotoxy(startCol, startRow + i); i++;
				printf(" / / _   \\  /                 /`  /`\n");
				gotoxy(startCol, startRow + i); i++;
				printf("/ _\\/(    | |               ./  .'_\n");
				gotoxy(startCol, startRow + i); i++;
				printf("| ( \\  '--'  \\             .'  (__)'\\\n");
				gotoxy(startCol, startRow + i); i++;
				printf("\\\\\\\\ `-------'            /________.''\n");
			} else if (!strcmp(mobType(current), "Ghost")) {
				gotoxy(startCol, startRow + i); i++;
				printf("   ^           ^\n");
				gotoxy(startCol, startRow + i); i++;
				printf("  /(__.-----.__)\\\n");
				gotoxy(startCol, startRow + i); i++;
				printf(" (.`           `.) \n");
				gotoxy(startCol, startRow + i); i++;
				printf(".`               `.\n");
				gotoxy(startCol, startRow + i); i++;
				printf(";   |\\       /|   ;\n");
				gotoxy(startCol, startRow + i); i++;
				printf(";   |X\\     /X|   :\n");
				gotoxy(startCol, startRow + i); i++;
				printf(":   |XX\\   /XX|   ;\n");
				gotoxy(startCol, startRow + i); i++;
				printf(";                 ;\n");
				gotoxy(startCol, startRow + i); i++;
				printf(":  |`.       .`|  ;\n");
				gotoxy(startCol, startRow + i); i++;
				printf(";  |--`|`.`|`--|  `,\n");
				gotoxy(startCol, startRow + i); i++;
				printf(":   | `.;;;.` |     ;._.--.  \n");
				gotoxy(startCol, startRow + i); i++;
				printf("`.   |.-.-.-.|         _`-`\n");
				gotoxy(startCol, startRow + i); i++;
				printf(" `;                   _-\n");
				gotoxy(startCol, startRow + i); i++;
				printf("   ;                .- \n");
				gotoxy(startCol, startRow + i); i++;
				printf("    `.;`;`-;-`;-`;-`\n");
			}
			startCol += 35;
			current = mobNext(current);
		}
	} 
}

void randGenerateMob(mobContainer *C){ 
	int makeMob = (randNumGenerator() % 2) + 1;
	while (makeMob != 0){
		int randNum = randNumGenerator();
		if (randNum < 6){
			mobAddress newMob = createMob("Ghost", GHOST, *C);
			InsertLast(C, newMob);
			randAction(*C);
		} else {
			mobAddress newMob = createMob("Goblin", GOBLIN, *C);
			InsertLast(C, newMob);
			randAction(*C);
		}
		makeMob -= 1;
	}
}

