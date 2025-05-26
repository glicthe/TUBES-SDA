#ifndef MOB_H
#define MOB_H

#include "config.h"

typedef struct Action {
    char* actionType;
    int quantity;
} Action;

#define actionType(P) P.actionType
#define damage(P) P.quantity

typedef struct Mob* address;
typedef struct Mob {
    address prev;       	// Previous node pointer
    int mobCounter;			// Count Mob
	char* mobType;         	// Mob type (string)
    int health;            	// Health points
    Action action;         	// Action struct
    address next;          	// Next node pointer
} Mob;

typedef struct {
	address firstMob;
} mobContainer;

#define mobPrev(P) P->prev
#define mobNext(P) P->next
#define mobCounter(P) P->mobCounter
#define mobType(P) P->mobType
#define mobHealth(P) P->health
#define mobAction(P) P->action
#define firstMob(P) (P).firstMob
#define mobActionQuantity(P) P->action.quantity
#define mobActionType(P) P->action.actionType

// Create function
mobContainer createMobContainer();
address createMob(const char* mobType, int health, Action action, mobContainer C);

// read function
address search(mobContainer C, const char* mobType, int mobPosition);
int countMob(mobContainer C);
void InsertLast(mobContainer *C, address selectedMob);

// delete function
void deleteMob(mobContainer *C, address mobToDelete);
void checkMobHealth(mobContainer *C);

// update function
void attacked(Action playerAction, address selectedMob, mobContainer *C);
void heal(address sselectedMob);

int randNumGenerator();
void randAction(int value, address selectedMob);



#endif
