//
// Created by Drake Witt on 2019-04-10.
//
#include "../gba.h"

#ifndef GBA_RAMRANCH_MAINLEVEL_H
#define GBA_RAMRANCH_MAINLEVEL_H

#define COMPARE_THREE_NUMBERS(x, y, z) ((x) <= (y) && (y) <= (z))

typedef struct {
    int row;
    int col;
} Cowboy;

typedef struct {
    int row;
    int col;
} Bullet;

typedef struct {
    int row;
    int col;
} FordRaptorTruck;

typedef struct {
    Bullet *bullets[30];
    int numBullets;
    FordRaptorTruck *trucks[28]; // 28 us marines pulling up in ford raptor trucks
    int numTrucks;
    Cowboy cowboy;
} MainLevelState;

void redrawScene(void);
void drawCowboy(void);
void initMainLevel(void);
void mainLevelEventListener(u32 currentButtons, u32 previousButtons);
void checkBulletTruckCollision(int bulletIndex);

#endif //GBA_RAMRANCH_MAINLEVEL_H
