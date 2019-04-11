#include "mainlevel.h"
#include "../images/rootytootypointnshooty.h"

int row = 0;
int col = 0;
int showBullet = 0;

void initMainLevel(void) {
    fillScreenDMA(0xFFFF); // Fill screen with white
    // TODO: Howdy yall
    drawImageDMA(10, 40, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
}


void redrawCowboy(void) {
    drawImageDMA(col, row, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
}

void redrawScene(void) {
    fillScreenDMA(0xFFFF); // Fill screen with black
    redrawCowboy();
    // drawGhost(row, col, ROOTYTOOTYPOINTNSHOOTY_WIDTH, ROOTYTOOTYPOINTNSHOOTY_HEIGHT, rootytootypointnshooty);
}

void mainLevelEventListener(u32 currentButtons, u32 previousButtons) {
    UNUSED(previousButtons);
    if (KEY_DOWN(BUTTON_UP, currentButtons)) {
        row--;
    }

    if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
        row++;
    }

    if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
        col--;
    }

    if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
        col++;
    }

    if (KEY_DOWN(BUTTON_A, currentButtons)) {
        showBullet = 1;
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