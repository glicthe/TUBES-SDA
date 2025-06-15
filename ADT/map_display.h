#ifndef MAP_DISPLAY_H
#define MAP_DISPLAY_H

#include "map_generator.h"
#include "config.h"

void drawMapView(MapNode* activeNode, int selected_child_idx);
void printMapSeparator_Top(int x, int y);
void printMapSeparator_Bottom(int x, int y);
void pembatas(int y_pos, int console_width, int line_length);

void applyNodeColor(MapNode* node, boolean isPlayer, boolean isSelected, boolean isGrandchild);
void printPaddedNode(MapNode* node, int width, boolean isPlayer, boolean isSelected, boolean isGrandchild);
void drawPattern_D0_Start(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D1_S0(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D1_S1(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D1_S2(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D2_S0_Children(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D2_S1_S2_Children(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D3_To_Boss(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_D4_Boss(MapNode* activeNode, int selectedIndex, int* currentY);
void drawPattern_Single_Child(MapNode* activeNode, int selectedIndex, int* currentY);

#endif
