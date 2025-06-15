#ifndef MOB_H
#define MOB_H

#include "config.h"
#include "Player.h"

#define GHOST 14
#define GOBLIN 16

typedef struct Action {
    char* actionType;
    int quantity;
} Action;

#define actionType(P) (P).actionType
#define damage(P) (P).quantity

typedef struct Mob* mobAddress;
typedef struct Mob {
    mobAddress prev;       	// Previous node pointer
    int mobCounter;			// Count Mob
	char* mobType;         	// Mob type (string)
    int health;            	// Health points
    Action action;         	// Action struct
    mobAddress next;          	// Next node pointer
} Mob;

#define mobPrev(P) (P)->prev
#define mobNext(P) (P)->next
#define mobCounter(P) (P)->mobCounter
#define mobType(P) (P)->mobType 
#define mobHealth(P) (P)->health
#define mobAction(P) (P)->action
#define mobActionQuantity(P) (P)->action.quantity
#define mobActionType(P) (P)->action.actionType

typedef struct {
	mobAddress firstMob;
	mobAddress currentMob;
} mobContainer;

#define firstMob(P) (P).firstMob
#define currentMob(P) (P).currentMob

// Create function
void createMobContainer(mobContainer *C);
mobAddress createMob(const char* mobType, int health, mobContainer C);

// Navigation functions
void moveLeftMob(mobContainer *C);
void moveRightMob(mobContainer *C);
void moveToFirstMob(mobContainer *C);
void moveToLastMob(mobContainer *C);

// read function
mobAddress search(mobContainer C, const char* mobType, int mobPosition);
int countMob(mobContainer C);
void InsertLast(mobContainer *C, mobAddress selectedMob);
void printMobContainer(mobContainer C, int startCol, int startRow);
void printCurrentMob(mobContainer C, int startCol, int startRow);
void printMob(int startCol, int startRow, int columns, int rows, mobContainer C, boolean state);

// delete function
void deleteMob(mobContainer *C, mobAddress mobToDelete);
void deleteCurrentMob(mobContainer* container);
void checkMobHealth(mobContainer *C);

// update function
void attacked(int damage, mobContainer *C);
void mobheal(mobAddress *selectedMob);
int attack(mobAddress selectedMob);

// random generator
void randAction(mobContainer C);
void randGenerateMob(mobContainer *C);



#endif
