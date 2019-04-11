#include "gba.h"
#include "logic.h"
#include "draw.h"
#include "myLib.h"
#include "audio/ramranch_audio.h"
#include "images/ramranch.h"
#include "scenes/titlescreen.h"
#include "scenes/introcutscene.h"
#include "scenes/mainlevel.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(void) {
    // TA-TODO: Manipulate REG_DISPCNT here to set Mode 3.
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    *sound_control = 0;

    play_sound(ramranch_data, ramranch_length, 8000, 'A');

    GBAState state = TITLE_SCREEN;

    // We store the "previous" and "current" states.
    AppState currentAppState, nextAppState;

    // We store the current and previous values of the button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    while (1) {
        // Load the current state of the buttons
        currentButtons = BUTTONS;

        switch(state) {
            case SPLASH_SCREEN:
                // Wait for VBlank
                waitForVBlank();
                // DRAW SPLASH SCREEN
                // WAIT FOR 3 SECONDS
                // TODO: INSERT DELAY
                state = TITLE_SCREEN;
                break;
            case TITLE_SCREEN:
                // DRAW TITLE SCREEN
                waitForVBlank();
                drawTitleScreen();

                state = TITLE_SCREEN_NODRAW;
                break;
            case TITLE_SCREEN_NODRAW:
                // LISTEN FOR BUTTON PRESS
                // IF START PRESSED

                if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    // flashText = 0;
                    state = INTRO_CUTSCENE;
                }
                break;
            case INTRO_CUTSCENE:
                // DRAW INTRO CUTSCENE
                startIntroCutscene();
                state = MAIN_LEVEL_INIT;
                break;
            case MAIN_LEVEL_INIT:
                // Initialize the app. Switch to the APP state.
                initializeAppState(&currentAppState);

                // Draw the initial state of the app
                fullDrawAppState(&currentAppState);
                initMainLevel();

                state = MAIN_LEVEL;
                break;
            case MAIN_LEVEL:
                // Process the app for one frame, store the next state
                // nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

                mainLevelEventListener(currentButtons, previousButtons);

                // Wait for VBlank before we do any drawing.
                waitForVBlank();

                redrawScene();
                // mainLevelEventListener(currentButtons, previousButtons);
                // redrawScene(row, col);

                // Undraw the previous state
                // undrawAppState(&currentAppState);

                // Draw the current state
                // rawAppState(&nextAppState);

                // Now set the current state as the next state for the next iter.
                // currentAppState = nextAppState;

                // Check if the app is exiting. If it is, then go to the exit state.
                if (nextAppState.state) {
                    // state = GAME_OVER;
                }

                break;
            case GAME_OVER:
                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the exit / gameover screen

                state = GAME_OVER_NODRAW;
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
