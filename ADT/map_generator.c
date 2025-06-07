// map_generator.c

#include "map_generator.h"

// Variabel dan struktur data statis
static int nodeIdCounter = 1;
static const int d4ChildrenPattern[D4_PATTERN_SIZE] = {2,3,2,3,2,2,2,2,3,2,2,3,2,2,2,2,2};

typedef struct {
    int depth;
    int siblingIndex;
    int numChildren;
} BranchRule;

static const BranchRule branchRules[] = {
    {0, -1, START_NODE_CHILDREN}, {1, 0, 1}, {1, 1, 3}, {1, 2, 4},
    {3, -1, 1}, {5, -1, 1}, {-1, -1, 1}
};

const char* NODE_TYPE_NAMES[] = {
    "START", "ENEMY", "REST", "MERCHANT", "SECONDARY BOSS", "BIG BOSS"
};

static MapNode* createNode(NodeType type, const char* baseName, int depth, int floorNum, int branchId, int siblingIndex) {
    MapNode* newNode = (MapNode*)malloc(sizeof(MapNode));
    if (newNode == Nil) {
        perror("FATAL ERROR: createNode malloc");
        exit(EXIT_FAILURE);
    }

    newNode->id = nodeIdCounter++;
    newNode->type = type;
    snprintf(newNode->name, sizeof(newNode->name), "%s #%d", baseName, newNode->id);
    newNode->depth = depth;
    newNode->floor = floorNum;
    newNode->isVisited = (type == NODE_START);
    newNode->numChildren = 0;
    newNode->children = Nil;
    newNode->parent = Nil;
    newNode->branchId = branchId;
    newNode->siblingIndex = siblingIndex;
    return newNode;
}

static void addChild(MapNode* parent, MapNode* child) {
    MapNode** newChildren;
    if (parent == Nil || child == Nil) return;
    
    parent->numChildren++;
    newChildren = (MapNode**)realloc(parent->children, parent->numChildren * sizeof(MapNode*));
    if (newChildren == Nil) {
        perror("FATAL ERROR: addChild realloc");
        exit(EXIT_FAILURE);
    }
    parent->children = newChildren;
    parent->children[parent->numChildren - 1] = child;
    child->parent = parent;
}

void freeMapTree(MapNode* node) {
    int i;
    if (node == Nil) return;
    for (i = 0; i < node->numChildren; i++) {
        freeMapTree(node->children[i]);
    }
    free(node->children);
    free(node);
}

static int countChildrenByRule(int depth, int siblingIndex, MapNode* parentNode, int* d4PatternIndex) {
    int i;
    MapNode* grandParent;
    
    if (depth == 0) return START_NODE_CHILDREN;

    if (depth == 2) {
        grandParent = parentNode->parent;
        if (grandParent != Nil) {
            if (grandParent->siblingIndex == 0) return 3;
            return 2;
        }
        return 2;
    }
    
    if (depth == 4) {
        if (*d4PatternIndex < D4_PATTERN_SIZE) return d4ChildrenPattern[(*d4PatternIndex)++];
        return 2;
    }

    for (i = 0; i < (sizeof(branchRules) / sizeof(BranchRule)); i++) {
        if (branchRules[i].depth == depth) {
            if (branchRules[i].siblingIndex == siblingIndex || branchRules[i].siblingIndex == -1) {
                return branchRules[i].numChildren;
            }
        }
    }
    return 1;
}

static NodeType determineChildType(int childDepth, boolean* isRestPlaced, boolean* isMerchantPlaced, char* nameBuffer) {
    NodeType type = NODE_ENEMY;
    int typeRoll, attemptCount = 0;
    boolean typeFinalized = FALSE;

    if (childDepth == 4) {
        snprintf(nameBuffer, 50, "BOSS PENJAGA WILAYAH");
        return NODE_SECONDARY_BOSS;
    }
    if (childDepth == 6) {
        snprintf(nameBuffer, 50, "TAHTA PENGUASA AKHIR");
        return NODE_BIG_BOSS;
    }

    while (!typeFinalized && attemptCount < 20) {
        attemptCount++;
        typeRoll = generateRandomRange(0, 99); // Menggunakan fungsi original dari config.h
        
        if (childDepth == 1) {
            snprintf(nameBuffer, 50, "Pos Jaga Awal");
            typeFinalized = TRUE;
        } else if (childDepth == 2 || childDepth == 3 || childDepth == 5) {
            if (typeRoll < PROB_ENEMY_COMMON) {
                snprintf(nameBuffer, 50, "Rintangan Umum");
                typeFinalized = TRUE;
            } else if (typeRoll < PROB_REST_NODE) {
                if (!(*isRestPlaced)) {
                    type = NODE_REST;
                    snprintf(nameBuffer, 50, "Tempat Istirahat");
                    *isRestPlaced = TRUE;
                    typeFinalized = TRUE;
                }
            } else {
                if (!(*isMerchantPlaced)) {
                    type = NODE_MERCHANT;
                    snprintf(nameBuffer, 50, "Pedagang");
                    *isMerchantPlaced = TRUE;
                    typeFinalized = TRUE;
                }
            }
        } else {
            snprintf(nameBuffer, 50, "Node Darurat");
            typeFinalized = TRUE;
        }
    }
    if (!typeFinalized) {
        snprintf(nameBuffer, 50, "Jalur Darurat");
    }
    return type;
}

static void buildMapRecursive(MapNode* parentNode, int maxDepth, int floorNum, boolean* isRestPlaced, boolean* isMerchantPlaced, int* d4PatternIndex) {
    int i, numChildren, childDepth;
    char childName[50];
    NodeType childType;
    MapNode* childNode;
    
    if (parentNode == Nil || parentNode->depth >= maxDepth) return;

    if (parentNode->depth == maxDepth - 1) {
        if (parentNode->numChildren == 0) {
            childNode = createNode(NODE_BIG_BOSS, "TAHTA PENGUASA AKHIR", maxDepth, floorNum, parentNode->branchId, 0);
            addChild(parentNode, childNode);
        }
        return;
    }

    numChildren = countChildrenByRule(parentNode->depth, parentNode->siblingIndex, parentNode, d4PatternIndex);

    for (i = 0; i < numChildren; i++) {
        childDepth = parentNode->depth + 1;
        childType = determineChildType(childDepth, isRestPlaced, isMerchantPlaced, childName);
        childNode = createNode(childType, childName, childDepth, floorNum, parentNode->branchId, i);
        addChild(parentNode, childNode);

        if (childNode->type != NODE_BIG_BOSS) {
            buildMapRecursive(childNode, maxDepth, floorNum, isRestPlaced, isMerchantPlaced, d4PatternIndex);
        }
    }
}

MapNode* generateMap(int currentFloor) {
    int i, d4PatternIndex = 0;
    boolean isRestPlaced, isMerchantPlaced;
    char childName[60];
    NodeType childType;
    MapNode *root, *d1Node;
    
    nodeIdCounter = 1;
    root = createNode(NODE_START, "Gerbang Awal", 0, currentFloor, 0, 0);

    for (i = 0; i < START_NODE_CHILDREN; i++) {
        isRestPlaced = FALSE;
        isMerchantPlaced = FALSE;
        
        childType = determineChildType(1, &isRestPlaced, &isMerchantPlaced, childName);
        d1Node = createNode(childType, childName, 1, currentFloor, i + 1, i);
        addChild(root, d1Node);

        buildMapRecursive(d1Node, MAP_MAX_DEPTH, currentFloor, &isRestPlaced, &isMerchantPlaced, &d4PatternIndex);
    }
    return root;
}

void printMapDebug(MapNode* node, int indentLevel) {
    int i;
    if (node == Nil) return;
    for (i = 0; i < indentLevel; i++) {
        printf("    |  ");
    }
    printf("---o ID:%3d (L%d,D%d,B%d,S%d) [%-16s] \"%s\" (%d Children)\n",
           node->id, node->floor, node->depth, node->branchId, node->siblingIndex,
           NODE_TYPE_NAMES[node->type], node->name, node->numChildren);

    for (i = 0; i < node->numChildren; i++) {
        printMapDebug(node->children[i], indentLevel + 1);
    }
}
