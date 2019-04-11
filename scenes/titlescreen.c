#include "titlescreen.h"
#include "../gba.h"
#include "../images/ramranch.h"

void drawTitleScreen(void) {
    drawImageDMA(0, 0, 240, 160, ramranch);
    // startTextFlash();
}

void startTextFlash(void) {
    int flashText = 1;
    int vblankTime = 0;
    while(flashText == 1) {
        waitForVBlank();
        if (vblankTime == 0) {
            drawImageDMA(0, 0, 240, 160, ramranch);
        } else if (vblankTime == 500) {
            drawString(10, 20, "RAM RANCH IS UNDER SIEGE", 0x0000);
        } else if (vblankTime > 1000) {
            vblankTime = -1;
        }
        vblankTime++;
    }
}