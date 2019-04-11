#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

typedef enum {
    SPLASH_SCREEN,
    TITLE_SCREEN,
    TITLE_SCREEN_NODRAW,
    INTRO_CUTSCENE,
    MAIN_LEVEL_INIT,
    MAIN_LEVEL,
    GAME_OVER,
    GAME_OVER_NODRAW
} GBAState;

typedef struct {
    GBAState state;
} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
