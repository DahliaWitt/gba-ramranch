/* make defines for the bit positions of the control register */
#define TIMER_FREQ_1 0x0
#define TIMER_FREQ_64 0x2
#define TIMER_FREQ_256 0x3
#define TIMER_FREQ_1024 0x4
#define TIMER_ENABLE 0x80

/* the GBA clock speed is fixed at this rate */
#define CLOCK 16777216
#define CYCLES_PER_BLANK 280806

/* turn DMA on for different sizes */
#define DMA_ENABLE 0x80000000

/* this causes the DMA destination to be the same each time rather than increment */
#define DMA_DEST_FIXED 0x400000

/* this causes the DMA repeat interval to be synced with timer 0 */
#define DMA_SYNC_TO_TIMER 0x30000000

/* the interrupts are identified by number, we only care about this one */
#define INTERRUPT_VBLANK 0x1

/* allows turning on and off sound for the GBA altogether */
#define SOUND_MASTER_ENABLE 0x80
#define SOUND_MASTER_DISABLE 0x00

/* has various bits for controlling the direct sound channels */

/* bit patterns for the sound control register */
#define SOUND_A_RIGHT_CHANNEL 0x100
#define SOUND_A_LEFT_CHANNEL 0x200
#define SOUND_A_FIFO_RESET 0x800
#define SOUND_B_RIGHT_CHANNEL 0x1000
#define SOUND_B_LEFT_CHANNEL 0x2000
#define SOUND_B_FIFO_RESET 0x8000

extern volatile unsigned int* interrupt_callback;
extern volatile unsigned short* interrupt_selection;
extern volatile unsigned short* display_interrupts;
extern volatile unsigned short* interrupt_enable;
extern volatile unsigned short* sound_control;

void play_sound(const signed char* sound, int total_samples, int sample_rate, char channel);
void on_vblank(void);
void delay(int);
