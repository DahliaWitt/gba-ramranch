#include "mainlevel.h"
#include "../images/rootytootypointnshooty.h"
#include "../images/fordraptor.h"
#include "../logic.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

MainLevelState state;
int score;

void initMainLevel(void) {
    state.nextState = MAIN_LEVEL;
    score = 0;
    Cowboy cowboy;
    cowboy.col = 40;
    cowboy.row = 75;
    state.cowboy = cowboy;
    fillScreenDMA(0xFFFF); // Fill screen with white
    state.vBlanksUntilNextTruck = 0;
    state.truckPosition = 0;
    state.numTrucks = 0;
    redrawScore();
}

void spawnTruck(void) {
    FordRaptorTruck *truck = (FordRaptorTruck *) malloc(sizeof(FordRaptorTruck));
    truck->row = (45 * state.truckPosition) + 10;
    truck->col = 160;
    // find first non-empty
    int i = 0;
    while (state.trucks[i] != NULL) {
        i++;
    }
    state.trucks[i] = truck;
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
    state.numBullets++;
}

void yeetusDeletusCowboy(void) {
    state.nextState = TITLE_SCREEN;
}

void removeBullet(int index) {
    drawRectDMA(state.bullets[index]->col - 2, state.bullets[index]->row, 6, 2, 0xFFFF);
    free(state.bullets[index]);
    state.bullets[index] = NULL;
    state.numBullets--;
}

void removeTruck(int index) {
    drawRectDMA(state.trucks[index]->col, state.trucks[index]->row, FORDRAPTOR_WIDTH + 1, FORDRAPTOR_HEIGHT, 0xFFFF);
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
                // Bullets will always move one way
                drawRectDMA(state.bullets[i]->col - 2, state.bullets[i]->row, 2, 2, 0xFFFF);
                state.bullets[i]->col += 2;
                checkForBulletCollisions(i);
            }
        }

    }
}

void redrawTruck(void) {
    for (int i = 0; i < state.numTrucks; i++) {
        // if it gets to the edge, despawn because it gets janky
        if (state.trucks[i]->col < 0) {
            removeTruck(i);
        } else {
            drawImageDMA(state.trucks[i]->col, state.trucks[i]->row, FORDRAPTOR_WIDTH, FORDRAPTOR_HEIGHT, fordraptor);
            // Truck will always move one way
            drawRectDMA(state.trucks[i]->col + FORDRAPTOR_WIDTH, state.trucks[i]->row, 1, FORDRAPTOR_HEIGHT, 0xFFFF);
            state.trucks[i]->col -= 1;
        }
    }}

void redrawCowboy(void) {
    drawImageDMA(state.cowboy.col, state.cowboy.row, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
    if (state.numTrucks > 0) {
        checkForPlayerCollisions();
    }
}

void redrawScore(void) {
    char str[8];
    sprintf(str, "Score: %d", score);
    drawRectDMA(0, 1, 50, 7, 0xFFFF);
    drawString(0,1, str, 0x0000);
}

void redrawScene(void) {
    if (state.numBullets > 0) {
        drawBullets();
    }
    redrawTruck();
    redrawCowboy();

    if (state.vBlanksUntilNextTruck-- == 0) {
        if (state.numTrucks < 3) {
            spawnTruck();
        }
        state.vBlanksUntilNextTruck = 180;
    }
}


//////////////////////////////
// COLLISION LOGIC
/////////////////////////////
void checkForBulletCollisions(int bulletIndex) {
    for (int i = 0; i < state.numTrucks; i++) {
        // Check for bullet collision
        if (state.trucks[i] != NULL) {
            if ((state.bullets[bulletIndex]->col >= state.trucks[i]->col) &&
                (state.bullets[bulletIndex]->row >= state.trucks[i]->row) &&
                (state.bullets[bulletIndex]->row <= state.trucks[i]->row + FORDRAPTOR_HEIGHT)) {
                score++;
                redrawScore();
                // delet this
                removeTruck(i);
                removeBullet(bulletIndex);
            }
        }
    }
}

void checkForPlayerCollisions(void) {
    for (int i = 0; i < state.numTrucks; i++) {
        if (state.trucks[i] != NULL) {
            // Check for player collision
            int cowboyColEnd = state.cowboy.col + ROOTYTOOTYPOINTNSHOOTY_WIDTH;
            int truckColEnd = state.trucks[i]->col + FORDRAPTOR_WIDTH;
            int cowboyRowEnd = state.cowboy.row + ROOTYTOOTYPOINTNSHOOTY_HEIGHT;
            int truckRowEnd = state.trucks[i]->row + FORDRAPTOR_HEIGHT;
            if ((cowboyColEnd >= state.trucks[i]->col) &&
                (state.cowboy.col <= truckColEnd) &&
                (cowboyRowEnd >= state.trucks[i]->row) &&
                (state.cowboy.row <= truckRowEnd)) {
                removeTruck(i);
                yeetusDeletusCowboy();
            }
        }
    }
}


void mainLevelEventListener(u32 currentButtons, u32 previousButtons) {
    if (KEY_DOWN(BUTTON_UP, currentButtons) && 8 < state.cowboy.row) {
        state.cowboy.row--;
        drawRectDMA(state.cowboy.col - 1, (state.cowboy.row) + ROOTYTOOTYPOINTNSHOOTY_HEIGHT, ROOTYTOOTYPOINTNSHOOTY_WIDTH + 2, 1, 0xFFFF);
    }

    if (KEY_DOWN(BUTTON_DOWN, currentButtons) && state.cowboy.row < HEIGHT - ROOTYTOOTYPOINTNSHOOTY_HEIGHT) {
        state.cowboy.row++;
        drawRectDMA(state.cowboy.col - 1, state.cowboy.row - 1, ROOTYTOOTYPOINTNSHOOTY_WIDTH + 2, 1, 0xFFFF);
    }

    if (KEY_DOWN(BUTTON_LEFT, currentButtons) && state.cowboy.col > 0) {
        state.cowboy.col--;
        drawRectDMA((state.cowboy.col) + ROOTYTOOTYPOINTNSHOOTY_WIDTH, state.cowboy.row - 1, 1, ROOTYTOOTYPOINTNSHOOTY_HEIGHT + 2, 0xFFFF);
    }

    if (KEY_DOWN(BUTTON_RIGHT, currentButtons) && state.cowboy.col < WIDTH - ROOTYTOOTYPOINTNSHOOTY_WIDTH) {
        state.cowboy.col++;
        drawRectDMA(state.cowboy.col - 1, state.cowboy.row - 1, 1, ROOTYTOOTYPOINTNSHOOTY_HEIGHT + 2, 0xFFFF);
    }

    if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
        spawnBullet();
    }
}
