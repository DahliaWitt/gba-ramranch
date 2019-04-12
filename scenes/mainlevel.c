#include "mainlevel.h"
#include "../images/rootytootypointnshooty.h"
#include "../images/fordraptor.h"
#include "../logic.h"
#include <stddef.h>
#include <stdlib.h>

MainLevelState state;

void initMainLevel(void) {
    state.nextState = MAIN_LEVEL;
    Cowboy cowboy;
    cowboy.col = 40;
    cowboy.row = 10;
    state.cowboy = cowboy;
    fillScreenDMA(0xFFFF); // Fill screen with white
    // TODO: Howdy yall
    drawImageDMA(10, 40, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);

    state.vBlanksUntilNextTruck = 120;
    state.truckPosition = 0;
    state.numTrucks = 0;
}

void spawnTruck(void) {
    FordRaptorTruck *truck = (FordRaptorTruck *) malloc(sizeof(FordRaptorTruck));
    truck->row = (70 * state.truckPosition) + 10;
    truck->col = 160;
    // find first non-empty
    int i = 0;
    while (state.trucks[i] != NULL) {
        i++;
    }
    state.trucks[i] = truck;
    // TODO: Error check
    state.numTrucks++;

    if (state.truckPosition == 2) {
        state.truckPosition = 0;
    } else {
        state.truckPosition++;
    }
}

void spawnBullet(void) {
    Bullet *bulletBill = (Bullet *) malloc(sizeof(Bullet));
    bulletBill->row = state.cowboy.row + 23;
    bulletBill->col = state.cowboy.col + ROOTYTOOTYPOINTNSHOOTY_WIDTH;
    // find first non-empty
    int i = 0;
    while (state.bullets[i] != NULL) {
        i++;
    }
    state.bullets[i] = bulletBill;
    // TODO: Error check
    state.numBullets++;
}

void yeetusDeletusCowboy(void) {
    drawCenteredString(10, 10, WIDTH, HEIGHT, "Cowboy ded lmfao", 0xAAAA);
    state.nextState = TITLE_SCREEN;
}

void removeBullet(int index) {
    free(state.bullets[index]);
    state.bullets[index] = NULL;
    state.numBullets--;
}

void removeTruck(int index) {
    free(state.trucks[index]);
    state.trucks[index] = NULL;
    state.numTrucks--;
}

void drawBullets(void) {
    for (int i = 0; i < 30; i++) {
        if (state.bullets[i] != NULL) {
            if (state.bullets[i]->col > 234) {
                removeBullet(i);
            } else {
                drawRectDMA(state.bullets[i]->col, state.bullets[i]->row, 6, 2, 0x0000);
                state.bullets[i]->col += 2;
                checkForBulletCollisions(i);
            }
        }

    }
}

void redrawTruck(void) {
    for (int i = 0; i < state.numTrucks; i++) {
        drawImageDMA(state.trucks[i]->col, state.trucks[i]->row, FORDRAPTOR_WIDTH, FORDRAPTOR_HEIGHT, fordraptor);
        state.trucks[i]->col--;
    }}

void redrawCowboy(void) {
    drawImageDMA(state.cowboy.col, state.cowboy.row, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
    if (state.numTrucks > 0) {
        checkForPlayerCollisions();
    }
}

void redrawScene(void) {
    fillScreenDMA(0xFFFF); // Fill screen with black
    if (state.numBullets > 0) {
        drawBullets();
    }
    redrawCowboy();
    redrawTruck();
}

//////////////////////////////
// COLLISION LOGIC
/////////////////////////////
void checkForBulletCollisions(int bulletIndex) {
    for (int i = 0; i < state.numTrucks; i++) {
        // Check for bullet collision
        if (state.bullets[bulletIndex]->col == state.trucks[i]->col && COMPARE_THREE_NUMBERS(state.trucks[i]->row,
                state.bullets[bulletIndex]->row, state.trucks[i]->row + FORDRAPTOR_HEIGHT)) {
            // delet this
            removeTruck(i);
            removeBullet(bulletIndex);
        }
    }
}

void checkForPlayerCollisions(void) {
    for (int i = 0; i < state.numTrucks; i++) {
        // Check for player collision
        int cowboyColEnd = state.cowboy.col + ROOTYTOOTYPOINTNSHOOTY_WIDTH;
        int truckColEnd = state.trucks[i]->col + FORDRAPTOR_WIDTH;
        int cowboyRowEnd = state.cowboy.row + ROOTYTOOTYPOINTNSHOOTY_HEIGHT;
        int truckRowEnd = state.trucks[i]->row + FORDRAPTOR_HEIGHT;
        if ((cowboyColEnd >= state.trucks[i]->col) &&
                (state.cowboy.col <= truckColEnd) &&
                (cowboyRowEnd >= state.trucks[i]->row) &&
                (state.cowboy.row <= truckRowEnd)) {
            yeetusDeletusCowboy();
        }
    }
}


void mainLevelEventListener(u32 currentButtons, u32 previousButtons) {
    if (KEY_DOWN(BUTTON_UP, currentButtons) && 0 < state.cowboy.row) {
        state.cowboy.row--;
    }

    if (KEY_DOWN(BUTTON_DOWN, currentButtons) && state.cowboy.row < HEIGHT - ROOTYTOOTYPOINTNSHOOTY_HEIGHT) {
        state.cowboy.row++;
    }

    if (KEY_DOWN(BUTTON_LEFT, currentButtons) && state.cowboy.col > 0) {
        state.cowboy.col--;
    }

    if (KEY_DOWN(BUTTON_RIGHT, currentButtons) && state.cowboy.col < WIDTH - ROOTYTOOTYPOINTNSHOOTY_WIDTH) {
        state.cowboy.col++;
    }

    if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
        spawnBullet();
    }

//    if (state.vBlanksUntilNextTruck-- == 0) {
//        spawnTruck();
//    }
}



/**
 * Control flow?:
 * Init things
 * - black background
 * - draw cowboy
 * - grid of trucks? random seed???
 *
 * every vblank
 * - key down?
 *    - move cowboy, redraw
 * - detect if colision with trucks
 * - shooting
 */

/*
 * WHAT I GENERALLY WANT TO DO:
 * - Set background to black box
 * - (eventually) start music
 * - draw cowboy
 * - init cowboy controls
 */