#include "mob.h"


void createMobContainer(mobContainer *C){
	firstMob(*C) = Nil;
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
	
	int count = countMob(C);
	mobCounter(newMob) = count + 1;
	
	mobType(newMob) = (char*)malloc(strlen(mobType) + 1);
	if (mobType(newMob) == Nil){
		printf("Error: memory allocation for mobType");
		return Nil;
	}
	strcpy(mobType(newMob), mobType);
	
	mobActionType(newMob) = (char*)malloc(strlen(mobType) + 1);
	if (mobType(newMob) == Nil){
		printf("Error: memory allocation for mobType");
		return Nil;
	}
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
    }
}

void deleteMob(mobContainer *C, mobAddress mobToDelete) {
    if (mobToDelete == Nil || C == Nil) {
        return;
    }
    
    if (firstMob(*C) == mobToDelete) {
        firstMob(*C) = mobNext(mobToDelete);
        if (mobNext(mobToDelete) != Nil) {
            mobPrev(mobNext(mobToDelete)) = Nil;
        }
    } else {
        if (mobPrev(mobToDelete) != Nil) {
            mobNext(mobPrev(mobToDelete)) = mobNext(mobToDelete);
        }
        if (mobNext(mobToDelete) != Nil) {
            mobPrev(mobNext(mobToDelete)) = mobPrev(mobToDelete);
        }
    }
    
    if (mobType(mobToDelete) != Nil) {
        free(mobType(mobToDelete));
    }
    if (mobActionType(mobToDelete) != Nil) {
        free(mobActionType(mobToDelete));
    }
    free(mobToDelete);
}

void checkMobHealth(mobContainer *C){
	mobAddress curr = firstMob(*C);
	mobAddress next;
	
	while (curr != Nil){
		next = mobNext(curr);
		
		if (mobHealth(curr) <= 0){
			deleteMob(C, curr);
		}
		curr = next;
	}
}

mobAddress search(mobContainer C, const char* mobType, int mobPosition){
    mobAddress mob;
    boolean found = false;
    mob = firstMob(C);
    while ((mob != Nil) && (!found)){
        if (strcmp(mobType(mob), mobType) && mobCounter(mob) == mobPosition){
            found = true;
        } else {
            mob = mobNext(mob);
        }
    } 
    return (mob);
}

void attacked (Action playerAction, mobAddress selectedMob, mobContainer *C){
	// mobAddress selectedMob = search(C, mobType);
	if (selectedMob != Nil){
		mobHealth(selectedMob) -= damage(playerAction);
	}
	
	if (mobHealth(selectedMob) <= 0){
		deleteMob(C, selectedMob);
	}
}

void heal(mobAddress selectedMob){
	if (selectedMob != Nil){
		mobHealth(selectedMob) += mobActionQuantity(selectedMob);
		if (mobHealth(selectedMob) > 14 && strcmp(mobType(selectedMob), "Ghost") == 0 ){
			mobHealth(selectedMob) = 14; 
		} else if (mobHealth(selectedMob) > 16 && strcmp(mobType(selectedMob), "Goblin") == 0){
			mobHealth(selectedMob) = 16; 
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

    if (current == Nil) {
        printf("  (Empty)\n");
        return;
    }
	int i = 0;
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
