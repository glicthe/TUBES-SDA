// map_navigation.h

#ifndef MAP_NAVIGATION_H
#define MAP_NAVIGATION_H

#include "map_generator.h"
#include "inGameLayout.h"
#include "config.h"

void startNavigation(MapNode* mapRoot, GameSave* loadGame);
MapNode* gotoCurrNode(MapNode* checkMap);
void drawMapHeaderSeparator(int x, int y, int width);
void drawMapFooterSeparator(int x, int y, int width);

#endif
