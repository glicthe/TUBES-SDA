#include "mob.h"

mobContainer createMobContainer(){
	mobContainer C;
	firstMob(C) = Nil;
	return C;
}

int countMob(mobContainer C){
	int count = 0;
    address P;
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

address createMob(const char* mobType, int health, Action action, mobContainer C){
	address newMob = (address)malloc(sizeof(Mob));
	if (newMob == Nil){
		printf("Error: Memory Allocation failed");
		return Nil;
	}
	
	mobPrev(newMob) = Nil;
	mobNext(newMob) = Nil;
	
	int count = countMob(C);
	mobCounter(newMob) = count;
	
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
	mobAction(newMob) = action;

	return newMob;
}

void InsertLast(mobContainer *C, address selectedMob){
    address Last;
    if (firstMob(*C) != Nil) {
        Last = firstMob(*C);
        while (mobNext(Last) != Nil){
            Last = mobNext(Last);
        }
        mobNext(Last) = selectedMob;
    } else {
        firstMob(*C) = selectedMob;
    }
}

void deleteMob(mobContainer *C, address mobToDelete) {
    if (mobToDelete == Nil || C == Nil) {
        return;
    }
    
    // If it's the first mob in the list
    if (firstMob(*C) == mobToDelete) {
        firstMob(*C) = mobNext(mobToDelete);
        if (mobNext(mobToDelete) != Nil) {
            mobPrev(mobNext(mobToDelete)) = Nil;
        }
    } else {
        // Connect previous node to next node
        if (mobPrev(mobToDelete) != Nil) {
            mobNext(mobPrev(mobToDelete)) = mobNext(mobToDelete);
        }
        if (mobNext(mobToDelete) != Nil) {
            mobPrev(mobNext(mobToDelete)) = mobPrev(mobToDelete);
        }
    }
    
    // Free the memory
    if (mobType(mobToDelete) != Nil) {
        free(mobType(mobToDelete));
    }
    if (mobActionType(mobToDelete) != Nil) {
        free(mobActionType(mobToDelete));
    }
    free(mobToDelete);
}

void checkMobHealth(mobContainer *C){
	address curr = firstMob(*C);
	address next;
	
	while (curr != Nil){
		next = mobNext(curr);
		
		if (mobHealth(curr) <= 0){
			deleteMob(C, curr);
		}
		curr = next;
	}
}

address search(mobContainer C, const char* mobType, int mobPosition){
    address mob;
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

void attacked (Action playerAction, address selectedMob, mobContainer *C){
	// address selectedMob = search(C, mobType);
	if (selectedMob != Nil){
		mobHealth(selectedMob) -= damage(playerAction);
	}
	
	if (mobHealth(selectedMob) <= 0){
		deleteMob(C, selectedMob);
	}
}

void heal(address selectedMob){
	if (selectedMob != Nil){
		mobHealth(selectedMob) += mobActionQuantity(selectedMob);
	}
}

 
int randNumGenerator(){
	int min = 1, max = 10;
	
	int value = rand() % (max - min + 1) + min;
	return value;
}

void randAction(int value, address selectedMob){
	if (value <= 7) {
		free(mobActionType(selectedMob));
		mobActionType(selectedMob) = (char*)malloc(strlen("attack") + 1);
		strcpy(mobActionType(selectedMob), "attack");
		
		if (strcmp(mobType(selectedMob), "Ghost")){
			mobActionQuantity(selectedMob) = 5;
		} else if (strcmp(mobType(selectedMob), "Goblin")){
			mobActionQuantity(selectedMob) = 7;			
		}
	} else {
		free(mobActionType(selectedMob));
		mobActionType(selectedMob) = (char*)malloc(strlen("heal") + 1);
		strcpy(mobActionType(selectedMob), "heal");
		
		mobActionQuantity(selectedMob) = 5;
	}
}
