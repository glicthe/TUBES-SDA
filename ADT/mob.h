#ifndef MOB_H
#define MOB_H

#include "config.h"
#define GHOST 14
#define GOBLIN 16

typedef struct Action {
    char* actionType;
    int quantity;
} Action;

#define actionType(P) (P).actionType
#define damage(P) (P).quantity

typedef struct Mob* address;
typedef struct Mob {
    address prev;       	// Previous node pointer
    int mobCounter;			// Count Mob
	char* mobType;         	// Mob type (string)
    int health;            	// Health points
    Action action;         	// Action struct
    address next;          	// Next node pointer
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
	address firstMob;
} mobContainer;

#define firstMob(P) (P).firstMob
// Create function
void createMobContainer(mobContainer *C);
address createMob(const char* mobType, int health, mobContainer C);

// read function
address search(mobContainer C, const char* mobType, int mobPosition);
int countMob(mobContainer C);
void InsertLast(mobContainer *C, address selectedMob);
void printMobContainer(mobContainer C);

// delete function
void deleteMob(mobContainer *C, address mobToDelete);
void checkMobHealth(mobContainer *C);

// update function
void attacked(Action playerAction, address selectedMob, mobContainer *C);
void heal(address sselectedMob);

// random generator
int randNumGenerator();
void randAction(mobContainer C);
void randGenerateMob(mobContainer *C);



#endif
