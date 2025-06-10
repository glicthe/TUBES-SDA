// map_generator.h

#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "config.h"

typedef enum {
    NODE_START, NODE_ENEMY, NODE_REST,
    NODE_MERCHANT, NODE_SECONDARY_BOSS, NODE_BIG_BOSS
} NodeType;

extern const char* NODE_TYPE_NAMES[];

typedef struct MapNode {
    int id;
    NodeType type;
    char name[60];
    int depth;
    int floor;
    boolean isVisited;
    int numChildren;
    struct MapNode **children;
    struct MapNode *parent;
    int branchId;
    int siblingIndex;
} MapNode;

MapNode* generateMap(int currentFloor);
void freeMapTree(MapNode* node);
void printMapDebug(MapNode* node, int indentLevel);

#endif // MAP_GENERATOR_H
