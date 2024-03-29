#include "gba.h"
#include "logic.h"
#include "draw.h"
#include "myLib.h"
#include "audio/ramranch_audio.h"
#include "images/ramranch.h"
#include "scenes/titlescreen.h"
#include "scenes/introcutscene.h"
#include "scenes/mainlevel.h"
#include "images/loser.h"
#include "images/apesoft.h"
#include "audio/ape_sound.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(void) {
    // TA-TODO: Manipulate REG_DISPCNT here to set Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    //*sound_control = 0;

    play_sound(ape_sound_data, ramranch_length, 'A');

    GBAState gameState = SPLASH_SCREEN;

    // We store the "previous" and "current" states.
    //AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    int localVblankCounter = 0;

    while (1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            gameState = TITLE_SCREEN;
        }

        switch(gameState) {
            case SPLASH_SCREEN:
                // Wait for VBlank
                waitForVBlank();
                drawImageDMA(0,0, WIDTH, HEIGHT, apesoft);
                localVblankCounter++;
                // DRAW SPLASH SCREEN
                // WAIT FOR 3 SECONDS
                // TODO: INSERT DELAY
                if (localVblankCounter > 180) {
                    gameState = TITLE_SCREEN;
                }

                break;
            case TITLE_SCREEN:
                // DRAW TITLE SCREEN
                waitForVBlank();
                drawTitleScreen();
                startAudio();

                gameState = TITLE_SCREEN_NODRAW;
                break;
            case TITLE_SCREEN_NODRAW:
                // LISTEN FOR BUTTON PRESS
                // IF START PRESSED
                waitForVBlank();
                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    flashText = 0;
                    gameState = INTRO_CUTSCENE;
                }
                break;
            case INTRO_CUTSCENE:
                // DRAW INTRO CUTSCENE
                waitForVBlank();
                startIntroCutscene();
                if(goToNext == 1) {
                    gameState = MAIN_LEVEL_INIT;
                }
                break;
            case MAIN_LEVEL_INIT:
                // Initialize the app. Switch to the APP state.
                //initializeAppState(&currentAppState);

                // Draw the initial state of the app
                //fullDrawAppState(&currentAppState);
                initMainLevel();

                gameState = MAIN_LEVEL;
                break;
            case MAIN_LEVEL:
                // Process the app for one frame, store the next state
                // nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

                mainLevelEventListener(currentButtons, previousButtons);

                redrawScene();

                // Wait for VBlank before we do any drawing.
                waitForVBlank();

                // mainLevelEventListener(currentButtons, previousButtons);
                // redrawScene(row, col);

                // Undraw the previous state
                // undrawAppState(&currentAppState);

                // Draw the current state
                // rawAppState(&nextAppState);

                // Now set the current state as the next state for the next iter.
                // currentAppState = nextAppState;

                // Check if the app is exiting. If it is, then go to the exit state.
                gameState = state.nextState;

                break;
            case GAME_OVER:
                // Wait for VBlank
                waitForVBlank();

                drawImageDMA(0, 0, 240, 160, LOSER);


                gameState = GAME_OVER_NODRAW;
                break;
            case GAME_OVER_NODRAW:
                // TA-TODO: Check for a button press here to go back to the start screen

                break;
        }

        // Store the current state of the buttons
        previousButtons = currentButtons;
    }

    return 0;
}
