#ifndef LOADGAME_H
#define LOADGAME_H

#include "display.h"
#include "map_generator.h"


typedef struct {
    MapNode mapSaved;
    Player playerSaved;
    cardDeck deckInventorySaved;
    mobContainer mobSaved;
    Boss* bossSaved;
}GameSave;

#define mapSaved(P) (P)->mapSaved
#define playerSaved(P) (P)->playerSaved
#define deckInventorySaved(P) (P)->deckInventorySaved
#define mobSaved(P) (P)->mobSaved
#define bossSaved(P) (P)->bossSaved

// Key-Value structure for hierarchical loading
typedef struct {
    char key[256];
    char value[256];
    struct keyValue* next;
}keyValue;

#define key(P) (P)->key
#define value(P) (P)->value
#define keyValueNext(P) (P)->next


//helper functions
void writeKeyValue(FILE* file, const char* key, const char* value);
void writeKeyValueInt(FILE* file, const char* key, int value);
void buildKey(char* buffer, const char* prefix, const char* suffix);
keyValue* parseKeyValue(const char* line);
keyValue* loadKeyValuePairs(const char* filename);
char* findValue(keyValue* keyValueList, const char* key);
int findIntValue(keyValue* keyValueList, const char* key, int deafultValue);
void freeKeyValueList(keyValue* head);


//save functions
void saveGameProgress(MapNode* saveMap, Player* savePlayer, cardDeck* DeckInventory, mobContainer saveMobCon, Boss* saveBoss);
void saveMap(MapNode* node, FILE* file);
void saveMapNode(MapNode* node, FILE* file, const char* prefix);
void savePlayer(Player* player, cardDeck* DeckInventory, FILE* file);
void savePlayerDeckHand(Player* player, FILE* file);
void savePlayerDeckInventory(cardDeck* inventory, FILE* file);
void saveMobContainer(mobContainer mob, FILE* file);
void saveBoss(Boss* boss, FILE* file);
void saveBossPattern(Boss* boss, FILE* file);

//load functions
GameSave* loadGameProgress(const char* filename);
void loadPlayer(keyValue* keyValueList, Player* player, cardDeck* DeckInventory);
void loadPlayerDeckHand(keyValue* keyValueList, cardDeck* playerHand);
void loadPlayerDeckInventory(keyValue* keyValueList, cardDeck* DeckInventory);
void loadMap(keyValue* keyvalueList, MapNode* map);
MapNode* createLoadMapNode(int id);
void loadSingleMapNode(keyValue* keyValueList, MapNode* node, int nodeId);
void connectMapNode(keyValue* keyValueList, MapNode** nodes, int nodeCount);
void loadMobContainer(keyValue* keyValueList, mobContainer* mob);
void loadBoss(keyValue* keyValueList, Boss** boss);
void loadBossActionPattern(keyValue* keyValueList, Boss* boss);


#endif 

//Player* player, cardDeck* deckInventory, mobContainer* mob, Boss* boss, GameSave* save
