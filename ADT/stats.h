// stats.h
#ifndef STATS_H
#define STATS_H
#include "player.h"

typedef struct Player Player;

typedef struct {
    int enemiesDefeated;
    int highestDepthCompleted;
    int totalCardsOwned;
} GameStats;

extern GameStats g_gameStats;

void initGameStats();

void showGameStats(const Player *player);
void printStatistics_Top(int x, int y);
void printStatistics_Bottom(int x, int y);


#endif
