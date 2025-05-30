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
		//dragoonPattern(P);
	} else if (strcmp(bossType(newBoss), "unicorn") == 0) {
		unicornPattern(P);
	} else if (strcmp(bossType(newBoss), "griffin") == 0) {
		//griffinPattern(P);
	}
		
	currBossAction(newBoss) = firstPtrn(*P);
	bossPatterns(newBoss) = firstPtrn(*P);
	bossHealth(newBoss) = Health;
	
	return newBoss;
	
}

int randAttackValue(const char* bossType){
	int min, max, value;
	if (strcmp(bossType, "dragoon") == 0){
		min = 16;
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
		currBossAction(boss) = nextPtrn(currBossAction(boss));
		
		if (currBossAction(boss) == Nil){
			currBossAction(boss) = bossPatterns(boss);
		}
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


//=======================================================
//=======================================================
//=======================================================
//===================BOSS PATTERN========================
//=======================================================
//=======================================================

void unicornPattern(patternQueue *P){
	int DamageAttack[9], i;
	for (i = 0; i < 9; i++){
		DamageAttack[i] = randAttackValue("unicorn");
	} 
	
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
	

void griffinPattern(){
	patternQueue griffin;
	createPattern(&griffin);
	
	enqueuePattern(&griffin, "Heal", 20);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Heal", 20);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Heal", 20);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Heal", 20);
	enqueuePattern(&griffin, "Attack", 12);
	enqueuePattern(&griffin, "Attack", 12);
	
	printPatternQueue(griffin);
}

void dragoonPattern(){
	patternQueue dragoon;
	createPattern(&dragoon);
	
}
	
