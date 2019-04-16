//
// Created by Drake Witt on 2019-04-10.
//

#include "introcutscene.h"
#include "../gba.h"
#include "../myLib.h"

int vBlanksUntilNext = 1;
int textScene = 0;
int goToNext = 0;

void drawTextSequence(void) {
    vBlanksUntilNext--;
    if (vBlanksUntilNext == 0 && textScene == 0) {
        fillScreenDMA(0x0000);
        drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_ONE_L1, 0xFFFF);
        drawCenteredString(0, 10, WIDTH, HEIGHT, SCR_ONE_L2, 0xFFFF);
        textScene++;
        vBlanksUntilNext = 600;
    } else if (vBlanksUntilNext == 0 && textScene == 1) {
        fillScreenDMA(0x0000);
        drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_TWO, 0xFFFF);
        textScene++;
        vBlanksUntilNext = 600;
    } else if (vBlanksUntilNext == 0 && textScene == 2) {
        fillScreenDMA(0x0000);
        drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_THREE, 0xFFFF);
        textScene++;
        vBlanksUntilNext = 600;
    } else if (vBlanksUntilNext == 0 && textScene == 3) {
        fillScreenDMA(0x0000);
        drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_FOUR, 0xFFFF);
        textScene++;
        vBlanksUntilNext = 600;
    } else if (vBlanksUntilNext == 0 && textScene == 4) {
        goToNext = 1;
    }
}

void startIntroCutscene(void) {
    drawTextSequence();
}