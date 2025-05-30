#ifndef BOSS_H
#define BOSS_H
#include "config.h"

typedef struct Pattern* patternAddress;
typedef struct Pattern {
	char* actionName;
	int quantity;
	patternAddress next;
}Pattern;

typedef struct{
	patternAddress firstPtrn;
	patternAddress lastPtrn;	
}patternQueue;

typedef struct Boss{
	char* bossType;
	patternAddress currAction;
	patternAddress patterns;
	int Health;
}Boss;

#define bossType(P) (P)->bossType
#define currBossAction(P) (P)->currAction
#define bossPatterns(P) (P)->patterns
#define bossHealth(P) (P)->Health

#define firstPtrn(P) (P).firstPtrn
#define lastPtrn(P) (P).lastPtrn
#define nextPtrn(P) (P)->next
#define actionName(P) (P)->actionName
#define quantity(P) (P)->quantity


// Create Function
void createPattern(patternQueue *Q);
patternAddress allocatePattern(char* action, int qty);
Boss* createBoss(const char* bossType, int Health, patternQueue *P);

void unicornPattern(patternQueue *P);
void griffinPattern();
void dragoonPattern();

// Read Function
void printPatternQueue(patternQueue Q);
boolean isEmptyPattern(patternQueue Q);
void getCurrentBossAction(Boss* boss, char* action, int* qty);
void advanceBossAction(Boss* boss);
void executeBossAction(Boss* boss, char* action, int* qty);

// Update Function
void enqueuePattern(patternQueue *Q, char* action, int qty);
void dequeuePattern(patternQueue *Q, char* action, int *qty);
int randAttackValue(const char* bossType);

// Delete Function
void deallocatePattern(patternAddress P);
void clearPatternQueue(patternQueue *Q);


#endif
