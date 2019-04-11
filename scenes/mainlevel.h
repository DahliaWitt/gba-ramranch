//
// Created by Drake Witt on 2019-04-10.
//
#include "../gba.h"

#ifndef GBA_RAMRANCH_MAINLEVEL_H
#define GBA_RAMRANCH_MAINLEVEL_H

void redrawScene(void);
void drawCowboy(void);
void initMainLevel(void);
void mainLevelEventListener(u32 currentButtons, u32 previousButtons);

#endif //GBA_RAMRANCH_MAINLEVEL_H
