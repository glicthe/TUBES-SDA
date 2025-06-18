#include "loadGame.h"

// Helper function to write a key-value pair
void writeKeyValue(FILE* file, const char* key, const char* value) {
    fprintf(file, "%s=%s\n", key, value);
}

// Helper function to write integer value
void writeKeyValueInt(FILE* file, const char* key, int value) {
    fprintf(file, "%s=%d\n", key, value);
}

// Helper function to build hierarchical keys
void buildKey(char* buffer, const char* prefix, const char* suffix) {
    sprintf(buffer, "%s.%s", prefix, suffix);
}

// Helper for parsing key value
keyValue* parseKeyValue(const char* line) {
	keyValue* keyValueTemp = malloc(sizeof(keyValue));
	if (!keyValueTemp) return;
	
	//for getting the equal(=) position
	char* equalPos = strchr(line, '=');
	if (!equalPos) {
		free(keyValueTemp);
		return;
	}
	
	//copy key before equal(=)
	int keyValueLen = equalPos - line;
	strncpy(key(keyValueTemp), line, keyValueLen);
	keyValueTemp->key[keyValueLen] = '\0';
	
	//copy key After equal(=)
	strcpy(value(keyValueTemp), equalPos + 1);
	
	//remove newline from value
	char* newLine = strchr(value(keyValueTemp), '\n');
	if (newLine) {
		*newLine = '\0'; 	
	}
	
	keyValueNext(keyValueTemp) = Nil;
	return keyValueTemp;
}

//Helper for load all key value from file
keyValue* loadKeyValuePairs(const char* filename){
	FILE* file = fopen(filename, "r");
	if (!file) {
		return Nil;
	}
	
	keyValue* head = Nil;
	keyValue* tail = Nil;
	char line[512];
	
	while (fgets(line, sizeof(line), file)){
		//skip comment or blank line
		if (line[0] == '#' || line[0] == '\r' || line[0] == '\n') {
			continue;
		}
		
		keyValue* keyValueCurr = parseKeyValue(line);
		if (keyValueCurr) {
			if (!head) {
				head = tail = keyValueCurr;
			} else {
				tail->next = keyValueCurr;
				tail = keyValueCurr;
			}
		}
	}
	fclose(file);
	return head;
}

//Helper for find value by key
char* findValue(keyValue* keyValueList, const char* key){
	keyValue* curr = keyValueList;
	while (curr) {
		if (!strcmp(key(curr), key)){
			return value(curr);
		}
		curr = curr->next;
	}
	return Nil;
}

//Helper for fine int value by key
int findIntValue(keyValue* keyValueList, const char* key, int defaultValue){
	const char* value = findValue(keyValueList, key);
	if (value) {
		// ASCII to Int
		return atoi(value);
	}
	return defaultValue;	
}

//Helper for delete KeyValue list
void freeKeyValueList(keyValue* head){
	while(head){
		keyValue* temp = head;
		head = head->next;
		free(temp);
	}
}

//SAVE FUNCTIONS
void saveGameProgress(MapNode* Map, Player* Player, cardDeck* DeckInventory, mobContainer MobCon, Boss* boss) {
    remove("saved_game.txt");
	FILE* file = fopen("saved_game.txt", "w");
    if (!file) {
        perror("Error: Could not open file for saving");
        return;
    }

    fprintf(file, "# ----- Game Save ----- #\n\n");
    
    fprintf(file, "# ----- Map Save ----- #\n\n");
    // save map structure recursively
	if (Map != Nil) {
        saveMap(Map, file);
    }

	fprintf(file, "# ----- Player Save ----- #\n\n");
	// save player 
	if (Player != Nil) {
		savePlayer(Player, DeckInventory, file);		                   
	}
	
	fprintf(file, "# ----- Mob Save ----- #\n\n");
	//save mob (if the player is in the middle battle with mob)
	mobAddress saveMob = firstMob(MobCon);
	if (saveMob != Nil) {
		saveMobContainer(MobCon, file);
	} else writeKeyValue(file, "mobs.count", "0");
	
	fprintf(file, "# ----- Boss Save ----- #\n\n");
	//save boss (if the player is in the middle battle with boss)
	if (boss != Nil) {
		saveBoss(boss, file);
	} else writeKeyValue(file, "boss.exists", "false");

    fclose(file);
}

void saveMap(MapNode* node, FILE* file) {
	saveMapNode(node, file, "gameMap");
}

void saveMapNode(MapNode* node, FILE* file, const char* prefix) {
    char keyBuffer[256];
    char nodePrefix[256];
    
    // Create node id
	    sprintf(nodePrefix, "%s.node_%d", prefix, node->id);
    
    // Save node properties
    buildKey(keyBuffer, nodePrefix, "id");
    writeKeyValueInt(file, keyBuffer, node->id);
    
    buildKey(keyBuffer, nodePrefix, "type");
    writeKeyValueInt(file, keyBuffer, node->type);
    
    buildKey(keyBuffer, nodePrefix, "name");
    writeKeyValue(file, keyBuffer, node->name);
    
    buildKey(keyBuffer, nodePrefix, "depth");
    writeKeyValueInt(file, keyBuffer, node->depth);
    
    buildKey(keyBuffer, nodePrefix, "floor");
    writeKeyValueInt(file, keyBuffer, node->floor);
    
    buildKey(keyBuffer, nodePrefix, "visited");
    writeKeyValueInt(file, keyBuffer, node->isVisited);
    
    buildKey(keyBuffer, nodePrefix, "branchId");
    writeKeyValueInt(file, keyBuffer, node->branchId);
    
    buildKey(keyBuffer, nodePrefix, "siblingIndex");
    writeKeyValueInt(file, keyBuffer, node->siblingIndex);
    
    buildKey(keyBuffer, nodePrefix, "numChildren");
    writeKeyValueInt(file, keyBuffer, node->numChildren);
    
    // Recursively save children
    int i;
    for (i = 0; i < node->numChildren; i++) {
        char childKey[256];
        sprintf(childKey, "\n%s.child_%d", nodePrefix, i);
        writeKeyValueInt(file, childKey, node->children[i]->id);
        
        // Recursively save child nodes
        saveMapNode(node->children[i], file, prefix);
    }
}

void savePlayer(Player* player, cardDeck* DeckInventory, FILE* file){
	writeKeyValue(file, "player.name", player->name);
	writeKeyValueInt(file, "player.health", player->health);
	writeKeyValueInt(file, "player.energy", player->energy);
	writeKeyValueInt(file, "player.shield", player->shield);
	writeKeyValueInt(file, "player.gold", player->gold);
	
	savePlayerDeckHand(player, file);
	savePlayerDeckInventory(DeckInventory, file);
}

void savePlayerDeckHand(Player* player, FILE* file) {
	cardAddress temp = deckHead(player->hand);
	int cardIndex = 0;
	int cardCount = 0;
	
	//count card first
	cardAddress counter = temp;
	while (counter != Nil) {
		cardCount++;
		counter = cardNext(counter);
	}
	
	writeKeyValueInt(file, "player.deck.count", cardCount);
	
	//save all cards
	while (temp != Nil) {
		char keyBuffer[256];
        char cardPrefix[64];
        
        sprintf(cardPrefix, "player.deck.card_%d", cardIndex);
        
        buildKey(keyBuffer, cardPrefix, "name");
		writeKeyValue(file, keyBuffer, cardName(temp));
		
		buildKey(keyBuffer, cardPrefix, "type");
		writeKeyValue(file, keyBuffer, cardType(temp));
		
		buildKey(keyBuffer, cardPrefix, "cost");
		writeKeyValueInt(file, keyBuffer, cardCost(temp));
		
		buildKey(keyBuffer, cardPrefix, "effectValue");
		writeKeyValueInt(file, keyBuffer, cardEffect(temp));
		
		buildKey(keyBuffer, cardPrefix, "upgrade");
		writeKeyValueInt(file, keyBuffer, cardUpgrade(temp));
		
		temp = cardNext(temp);
		cardIndex++;
	}
}

void savePlayerDeckInventory(cardDeck* Inventory, FILE* file) {
	cardAddress temp = deckHead(*Inventory);
	int cardIndex = 0;
	int cardCount = 0;
	
	//count card first
	cardAddress counter = temp;
	while (counter != Nil) {
		cardCount++;
		counter = cardNext(counter);
	}
	
	writeKeyValueInt(file, "deck.inventory.count", cardCount);
	
	//save all cards
	while (temp != Nil) {
		char keyBuffer[256];
        char cardPrefix[64];
        
        sprintf(cardPrefix, "deck.inventory.card_%d", cardIndex);
        
        buildKey(keyBuffer, cardPrefix, "name");
		writeKeyValue(file, keyBuffer, cardName(temp));
		
		buildKey(keyBuffer, cardPrefix, "type");
		writeKeyValue(file, keyBuffer, cardType(temp));
		
		buildKey(keyBuffer, cardPrefix, "cost");
		writeKeyValueInt(file, keyBuffer, cardCost(temp));
		
		buildKey(keyBuffer, cardPrefix, "effectValue");
		writeKeyValueInt(file, keyBuffer, cardEffect(temp));
		
		temp = cardNext(temp);
		cardIndex++;
	}
}

void saveMobContainer(mobContainer mob, FILE* file){
	mobAddress currMob = firstMob(mob);
	int mobIndex = 0;
	int mobCount = 0;
	
	//count mob first
	mobAddress counter = currMob;
	while (counter != Nil) {
		mobCount++;
		counter = mobNext(counter);
	}
	writeKeyValueInt(file, "mobs.count", mobCount);
	
	//save all mob
	while (currMob != Nil) {
		char keyBuffer[256];
        char mobPrefix[64];
        
        sprintf(mobPrefix, "mobs.mob_%d", mobIndex);
        
        buildKey(keyBuffer, mobPrefix, "mobCounter");
		writeKeyValueInt(file, keyBuffer, mobCounter(currMob));
		
		buildKey(keyBuffer, mobPrefix, "mobType");
		writeKeyValue(file, keyBuffer, mobType(currMob));
		
		buildKey(keyBuffer, mobPrefix, "health");
		writeKeyValueInt(file, keyBuffer, mobHealth(currMob));
		
		currMob = mobNext(currMob);
		mobIndex++;
	}
}

void saveBoss(Boss* boss, FILE* file){
	writeKeyValue(file, "boss.exists", "true");
	writeKeyValue(file, "boss.type", bossType(boss));
	writeKeyValueInt(file, "boss.health", bossHealth(boss));
	
	saveBossPattern(boss, file);
}

void saveBossPattern(Boss* boss, FILE* file){
	int actionIndex = 0;
	int actionCount = 0;
	
	patternAddress temp = currBossAction(boss);
	while (temp != Nil) {
		actionCount++;
		temp = nextPtrn(temp);
	}
	writeKeyValueInt(file, "boss.pattern.count", actionCount);
	
	temp = currBossAction(boss);
	while (temp != Nil){
		char keyBuffer[256];
		char actionPrefix[64];
		
		sprintf(actionPrefix, "boss.pattern.action_%d", actionIndex);
        
        buildKey(keyBuffer, actionPrefix, "actionName");
		writeKeyValue(file, keyBuffer, actionName(temp));
		
		buildKey(keyBuffer, actionPrefix, "quantity");
		writeKeyValueInt(file, keyBuffer, quantity(temp));
		
		temp = nextPtrn(temp);
		actionIndex++;
	}
}


//LOAD FUNCITIONS
GameSave* loadGameProgress(const char* filename){
	//Get all keyValue
	keyValue* keyValueList = loadKeyValuePairs(filename);
	if (!keyValueList) {
		return Nil;
	}	
	
	GameSave* save = malloc(sizeof(GameSave));
	if (!save) {
		return Nil;
	}
	
	//load Player
	loadPlayer(keyValueList, &save->playerSaved, &save->deckInventorySaved);
	
	//load Map
	loadMap(keyValueList, &save->mapSaved);
	
	//load Mob
	loadMobContainer(keyValueList, &save->mobSaved);
	
	//load Boss
	loadBoss(keyValueList, &save->bossSaved);
	
	freeKeyValueList(keyValueList);
    return save;
	
}

void loadPlayer(keyValue* keyValueList, Player* player, cardDeck* DeckInventory){
	*player = createPlayer();
	const char* name = findValue(keyValueList, "player.name");
	
	if (name) {
		player->name = strdup(name);
	}
	
	player->health = findIntValue(keyValueList, "player.health", 100);
	player->energy = findIntValue(keyValueList, "player.energy", 3);
	player->shield = findIntValue(keyValueList, "player.shield", 0);
	player->gold = findIntValue(keyValueList, "player.gold", 90);
	initDiscard(&player->discard);
	
	//load deck inventory and hand
	loadPlayerDeckHand(keyValueList, &player->hand);
	loadPlayerDeckInventory(keyValueList, DeckInventory);
	
}

void loadPlayerDeckHand(keyValue* keyValueList, cardDeck* playerHand) {
	int cardCount = findIntValue(keyValueList, "player.deck.count", 0);
	
	initDeck(playerHand);
	int i;
	for (i = 0; i < cardCount; i++) {
		char keyBuffer[256];
		
		//get all Card 
		sprintf(keyBuffer, "player.deck.card_%d.name", i);
		const char* cardName = findValue(keyValueList, keyBuffer);
		
		sprintf(keyBuffer, "player.deck.card_%d.type", i);
		const char* cardType = findValue(keyValueList, keyBuffer);
		
		sprintf(keyBuffer, "player.deck.card_%d.cost", i);
		int cardCost = findIntValue(keyValueList, keyBuffer, 0);
		
		sprintf(keyBuffer, "player.deck.card_%d.effectValue", i);
		int cardEffect = findIntValue(keyValueList, keyBuffer, 0);
		
		sprintf(keyBuffer, "player.deck.card_%d.isUpgrade", i);
		int isUpgrade = findIntValue(keyValueList, keyBuffer, 0);
		
		cardAddress loadCard = createCard(cardName, cardType, cardCost, cardEffect);
		addCardToDeck(playerHand, loadCard);
	}
}

void loadPlayerDeckInventory(keyValue* keyValueList, cardDeck* DeckInventory) {
	int cardCount = findIntValue(keyValueList, "deck.inventory.count", 0);
	
	
	initDeck(DeckInventory);
	int i;
	for (i = 0; i < cardCount; i++) {
		char keyBuffer[256];
		
		//get all Card 
		sprintf(keyBuffer, "deck.inventory.card_%d.name", i);
		const char* cardName = findValue(keyValueList, keyBuffer);
		
		sprintf(keyBuffer, "deck.inventory.card_%d.type", i);
		const char* cardType = findValue(keyValueList, keyBuffer);
		
		sprintf(keyBuffer, "deck.inventory.card_%d.cost", i);
		int cardCost = findIntValue(keyValueList, keyBuffer, 0);
		
		sprintf(keyBuffer, "deck.inventory.card_%d.effectValue", i);
		int cardEffect = findIntValue(keyValueList, keyBuffer, 0);
		
		sprintf(keyBuffer, "deck.inventory.card_%d.isUpgrade", i);
		int isUpgrade = findIntValue(keyValueList, keyBuffer, 0);
		
		cardAddress loadCard = createCard(cardName, cardType, cardCost, cardEffect);
		addCardToDeck(DeckInventory, loadCard);
	}
}

void loadMap(keyValue* keyValueList, MapNode* map) {
	MapNode* nodes[122];
	int nodeCount = 0;
	
	// scan all keys to find node
	keyValue* curr = keyValueList;
	while (curr) {
		// look for node definiton
		if (!strncmp(key(curr), "gameMap.node_", 13)){
			//skip gameMap.node_
			char* nodeIdStr = key(curr) + 13;
			char* dotPos = strchr (nodeIdStr, '.');
			if (dotPos && !strcmp(dotPos, ".id")){
				// get node id
				int nodeId = atoi(value(curr));
				
				// create map node if not already created
				MapNode* node = createLoadMapNode(nodeId);
				if (node) {
					loadSingleMapNode(keyValueList, node, nodeId);
					nodes[nodeCount++] = node;
				}
			}
		}
		curr = curr->next;
	}
	//connect parent-child relationship
	connectMapNode(keyValueList, nodes, nodeCount);

	
	//find root node
	if (nodeCount > 0) {
		*map = *nodes[0]; //copy root node data
	}
}

MapNode* createLoadMapNode(int id) {
	MapNode* newNode = malloc(sizeof(MapNode));
	if (!newNode) return Nil;
	
	// init default values 
	newNode->id = id;
	newNode->type = 0;
	newNode->name[0] = '\0';
	newNode->depth = 0;
	newNode->floor = 0;
	newNode->isVisited = 0;
	newNode->branchId = 0;
	newNode->siblingIndex = 0;
	newNode->numChildren = 0;
	newNode->children = Nil;
	
	return newNode;
}

void loadSingleMapNode(keyValue* keyValueList, MapNode* node, int nodeId){
	char keyBuffer[256];
	
	//load node properties
	sprintf(keyBuffer, "gameMap.node_%d.type", nodeId);
	node->type = findIntValue(keyValueList, keyBuffer, 0);
	
	sprintf(keyBuffer, "gameMap.node_%d.name", nodeId);
	const char* name = findValue(keyValueList, keyBuffer);
	if (name) {
		strncpy(node->name, name, sizeof(node->name) - 1);
		node->name[sizeof(node->name) - 1]= '\0';
	}
	
	sprintf(keyBuffer, "gameMap.node_%d.depth", nodeId);
	node->depth = findIntValue(keyValueList, keyBuffer, 0);
	
	sprintf(keyBuffer, "gameMap.node_%d.floor", nodeId);
	node->floor = findIntValue(keyValueList, keyBuffer, 1);
	
	sprintf(keyBuffer, "gameMap.node_%d.visited", nodeId);
	node->isVisited = findIntValue(keyValueList, keyBuffer, 0);
	
	sprintf(keyBuffer, "gameMap.node_%d.branchId", nodeId);
	node->branchId = findIntValue(keyValueList, keyBuffer, 0);
	
	sprintf(keyBuffer, "gameMap.node_%d.siblingIndex", nodeId);
	node->siblingIndex = findIntValue(keyValueList, keyBuffer, 0);
	
	sprintf(keyBuffer, "gameMap.node_%d.numChildren", nodeId);
	node->numChildren = findIntValue(keyValueList, keyBuffer, 0);
	
	if (node->numChildren > 0) {
        node->children = malloc(node->numChildren * sizeof(MapNode*));
        if (node->children) {
            // Initialize all pointers to NULL
            int i;
            for (i = 0; i < node->numChildren; i++) {
                node->children[i] = NULL;
            }
        }
    }
}

void connectMapNode(keyValue* keyValueList, MapNode** nodes, int nodeCount){
	int i, childIndex, j;
	for (i = 0; i < nodeCount; i++) {
        MapNode* parentNode = nodes[i];
        if (parentNode->numChildren > 0 && parentNode->children != Nil) {
            for (childIndex = 0; childIndex < parentNode->numChildren; childIndex++) {
                char keyBuffer[256];
                sprintf(keyBuffer, "gameMap.node_%d.child_%d", parentNode->id, childIndex);
                int childId = findIntValue(keyValueList, keyBuffer, -1);

                if (childId != -1) {
                    boolean found = false;
                    for (j = 0; j < nodeCount; j++) {
                        if (nodes[j] != Nil && nodes[j]->id == childId) {
                            parentNode->children[childIndex] = nodes[j];
                            nodes[j]->parent= parentNode;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        fprintf(stderr, "Error: Child node with ID %d not found for parent node %d.\n", childId, parentNode->id);
                    }
                }
            }
        }
    }
}

void loadMobContainer(keyValue* keyValueList, mobContainer *mob) {
	int mobCount = findIntValue(keyValueList, "mobs.count", 0);
	
	//init mob container
	createMobContainer(mob);
	
	int i;
	for (i = 0; i < mobCount; i++) {
		char keyBuffer[256];
		
		//get all mob data
		sprintf(keyBuffer, "mobs.mob_%d.mobCounter", i);
		int count = findIntValue(keyValueList, keyBuffer, 0);
		
		sprintf(keyBuffer, "mobs.mob_%d.mobType", i);
		const char* mobType = findValue(keyValueList, keyBuffer);
		
		sprintf(keyBuffer, "mobs.mob_%d.health", i);
		int mobHealth = findIntValue(keyValueList, keyBuffer, 0);
		
		mobAddress loadMob = createMob(mobType, mobHealth, *mob);
		InsertLast(mob, loadMob);
		randAction(*mob);
	}
}

void loadBoss(keyValue* keyValueList, Boss** boss){
	const char* exists = findValue(keyValueList, "boss.exists");
    if (!exists || strcmp(exists, "false") == 0) {
        *boss = Nil; 
        return;
    }
    
    // Allocate memory for the boss
    *boss = malloc(sizeof(Boss));
    if (!(*boss)) {
        return;
    }
	
	 // Load boss data
    const char* bossType = findValue(keyValueList, "boss.type");
    if (bossType) {
        (*boss)->bossType = strdup(bossType); // Or however you handle string assignment
    }
    
    (*boss)->Health = findIntValue(keyValueList, "boss.health", 0);
	
	//load Boss action pattern
	loadBossActionPattern(keyValueList, *boss);
}

void loadBossActionPattern(keyValue* keyValueList, Boss* boss) {
	int patternCount = findIntValue(keyValueList, "boss.pattern.count", 0);
	
	boss->patterns = Nil;
	
	patternQueue tempQueue;
	createPattern(&tempQueue);
	
	int i;
	for (i = 0; i < patternCount; i++){
		char keyBuffer[256];
		
		sprintf(keyBuffer, "boss.pattern.action_%d.actionName", i);
		char* actionName = findValue(keyValueList, keyBuffer);
		
		sprintf(keyBuffer, "boss.pattern.action_%d.quantity", i);
		int quantity = findIntValue(keyValueList, keyBuffer, 0);
		
		enqueuePattern(&tempQueue, actionName, quantity);
	}
	
	bossPatterns(boss) = firstPtrn(tempQueue);
	currBossAction(boss) = firstPtrn(tempQueue);
}
