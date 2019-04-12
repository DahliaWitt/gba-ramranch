#include "mainlevel.h"
#include "../images/rootytootypointnshooty.h"
#include "../images/fordraptor.h"
#include <stddef.h>
#include <stdlib.h>

MainLevelState state;

void initMainLevel(void) {
    Cowboy cowboy;
    cowboy.col = 40;
    cowboy.row = 10;
    state.cowboy = cowboy;
    fillScreenDMA(0xFFFF); // Fill screen with white
    // TODO: Howdy yall
    drawImageDMA(10, 40, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);

    FordRaptorTruck *truck = (FordRaptorTruck *) malloc(sizeof(FordRaptorTruck));
    truck->col = 160;
    truck->row = 40;
    state.trucks[0] = truck;
    state.numTrucks++;
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
                state.bullets[i]->col += 1;
                checkBulletTruckCollision(i);
            }
        }

    }
}

void redrawTruck(void) {
    for (int i = 0; i < state.numTrucks; i++) {
        drawImageDMA(state.trucks[i]->col, state.trucks[i]->row, FORDRAPTOR_WIDTH, FORDRAPTOR_HEIGHT, fordraptor);
    }}

void redrawCowboy(void) {
    drawImageDMA(state.cowboy.col, state.cowboy.row, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
}

void redrawScene(void) {
    fillScreenDMA(0xFFFF); // Fill screen with black
    redrawCowboy();
    drawBullets();
    redrawTruck();
    // drawGhost(row, col, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
}

//////////////////////////////
// COLLISION LOGIC
/////////////////////////////
void checkBulletTruckCollision(int bulletIndex) {
    for (int i = 0; i < state.numTrucks; i++) {
        if (state.bullets[bulletIndex]->col == state.trucks[i]->col && COMPARE_THREE_NUMBERS(state.trucks[i]->row,
                state.bullets[bulletIndex]->row, state.trucks[i]->row + FORDRAPTOR_HEIGHT)) {
            // delet this
            removeTruck(i);
            waitForVBlank();
            state.bullets[bulletIndex] = NULL;

            // removeBullet(bulletIndex);
        }
    }
}


void mainLevelEventListener(u32 currentButtons, u32 previousButtons) {
    if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
        state.cowboy.row--;
    }

    if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
        state.cowboy.row++;
    }

    if (KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
        state.cowboy.col--;
    }

    if (KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {
        state.cowboy.col++;
    }

    if (KEY_DOWN(BUTTON_A, currentButtons)) {
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