//
// Created by Drake Witt on 2019-04-10.
//

#include "introcutscene.h"
#include "../gba.h"
#include "../myLib.h"

void drawTextSequence(void) {
    fillScreenDMA(0x0000);
    drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_ONE_L1, 0xFFFF);
    drawCenteredString(0, 10, WIDTH, HEIGHT, SCR_ONE_L2, 0xFFFF);
    delay(20);
    fillScreenDMA(0x0000);
    drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_TWO, 0xFFFF);
    delay(20);
    fillScreenDMA(0x0000);
    drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_THREE, 0xFFFF);
    delay(20);
    fillScreenDMA(0x0000);
    drawCenteredString(0, 0, WIDTH, HEIGHT, SCR_FOUR, 0xFFFF);
    delay(20);
}

void startIntroCutscene(void) {
    drawTextSequence();
}