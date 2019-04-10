///////////////////////////////////////////////////////////////////////////////
// sfx.c
///////////////////////////////////////////////////////////////////////////////

#include "gba.h"
#include "sfx.h"

// init_sfx_system - sets the registers for enabling the sound hardware and
//                   Direct Sound
// PARAMETERS:  none
// RETURNS:     none
void init_sfx_system(void)
{
    // turn on the sound chip
    REG_SOUNDCNT_X = SND_ENABLED;

    // make sure sound channels 1-4 are turned off
    REG_SOUNDCNT_L = 0;

    // set the direct sound output control register
    REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 | // 100% sound output
                     DSA_OUTPUT_RATIO_100 | // 100% direct sound A output
                     DSA_OUTPUT_TO_BOTH |   // output Direct Sound A to both right and left speakers
                     DSA_TIMER0 |           // use timer 0 to determine the playback frequency of Direct Sound A
                     DSA_FIFO_RESET;        // reset the FIFO for Direct Sound A
}

// play_sfx - starts the DMA of a sample and waits for it to complete
// PARAMETERS:  pSample - a pointer to the sample we want to play
// RETURNS:     none
void play_sfx(const SAMPLE *pSample)
{
    int i;
    int vblanks;

    // determine the number of vblanks this sample will take to play
    vblanks = pSample->length / SAMPLES_PER_VBLANK;

    // make sure Timer 0 is off
    REG_TM0CNT = 0;

    // make sure DMA channel 1 is turned off
    REG_DMA1CNT = 0;

    // make sure the FIFO is reset
    REG_SOUNDCNT_H |= DSA_FIFO_RESET;   // just set the reset bit and leave the other ones alone

    // start the timer using the appropriate frequency
    REG_TM0D   = TIMER_INTERVAL;
    REG_TM0CNT = TIMER_ENABLED;

    // start the DMA transfer on channel 1
	REG_DMA1SAD = (u32)(pSample->pData);
	REG_DMA1DAD = (u32)REG_FIFO_A;
    REG_DMA1CNT = ENABLE_DMA | START_ON_FIFO_EMPTY | WORD_DMA | DMA_REPEAT;

    // wait for the sample to finish
    for (i = 0; i < vblanks; ++i)
    {
        // wait for scanline 160 (this is the start of the vblank period)
        while (SCANLINE_COUNTER != SCREEN_HEIGHT){}

        // make sure we get past line scanline 160 before waiting for the next vblank
        while (SCANLINE_COUNTER == SCREEN_HEIGHT){}
    }

    // halt the dma now that the sample is done
    REG_DMA1CNT = 0;
}
