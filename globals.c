#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"

// game globals
int bpm = 60;
int score = 0;
bool q_pressed = false;
bool w_pressed = false;
bool o_pressed = false;
bool p_pressed = false;
int keypress_window = 20;
NoteTile q_lane_note_tiles[4];
NoteTile w_lane_note_tiles[4];
NoteTile o_lane_note_tiles[4];
NoteTile p_lane_note_tiles[4];

// hardware
// The LED pit is at this base address
struct ParaPort *const ledp = ((struct ParaPort *) 0xFF200000);
// The BUTTONS pit is at this base address
struct ParaPort *const buttonp = ((struct ParaPort *) 0xFF200050);
// The HEX digits 0 through 3 PIT
struct ParaPort *const hex03p = ((struct ParaPort *)0xFF200020);
// The Swicthes PIT
struct ParaPort *const swp = ((struct ParaPort *)0xFF200040);
// audio device port
struct audio_t *const audiop = ((struct audio_t *) AUDIO_BASE);
// hardware timer port
struct TimerPort *const timerp = ((struct TimerPort *) TIMER_BASE);

// graphics
volatile int pixel_buffer_start;
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

// audio
//  song progress: what note of the array we are at
int song_progress = 0;

//  song is a 2D array, first column = pitch, second column = duration as a fraction/decimal
//  note pitches are #define'd in globals.h, first letter = note, last letter = octave,
//  middle letter is S for sharp or B for flat if it's there
double tracing_that_dream[][2] = {
	{R, WHOLE},
	
    {AB3, QUARTER},
    {AB4, QUARTER},
    {G4, QUARTER},
    {AB4, QUARTER},
    
    {G4, QUARTER},
    {F4, QUARTER},
    {EB4, QUARTER},
    {F4, QUARTER},

    {EB4, QUARTER},
    {R, EIGTH},
    {BB3, EIGTH},
    {DB4, QUARTER},
    {C4, EIGTH},
    {BB3, EIGTH},
    
    {C4, QUARTER},
    {R, QUARTER},
    {AB3, QUARTER},
    {BB3, QUARTER},

    {C4, QUARTER},
    {DB4, QUARTER},
    {C4, QUARTER},
    {DB4, QUARTER},

    {EB4, QUARTER},
    {AB3, QUARTER},
    {R, QUARTER},
    {AB3, EIGTH},
    {AB3, EIGTH},

    {DB4, QUARTER},
    {C4, QUARTER},
    {DB4, QUARTER},
    {EB4, QUARTER},

    {C4, QUARTERDOT},
    {BB3, EIGTH},
    {BB3, QUARTER},
    {R, QUARTER},

    {AB3, QUARTER},
    {AB4, QUARTER},
    {G4, QUARTER},
    {AB4, QUARTER},

    {G4, QUARTER},
    {F4, QUARTER},
    {EB4, QUARTER},
    {F4, QUARTER},

    {EB4, QUARTER},
    {F4, QUARTER},
    {G4, QUARTER},
    {C4, QUARTER},

    {AB4, HALF},
    {G4, QUARTER},
    {F4, QUARTER},

    {EB4, QUARTER},
    {F4, EIGTH},
    {AB3, EIGTH},
    {R, EIGTH},
    {F3, EIGTH},
    {F3, EIGTH},
    {AB3, EIGTH},

    {DB4, QUARTER},
    {C4, EIGTH},
    {BB3, EIGTH},
    {R, EIGTH},
    {AB3, EIGTH},
    {AB3, QUARTER},

    {C5, EIGTH},	// goes high here
    {F4, EIGTH},
    {C5, EIGTH},
    {BB4, EIGTH},
    {R, EIGTH},
    {F4, EIGTH},
    {R, EIGTH},
    {AB4, QUARTER}, // TIE

    {G4, TRIPLET/2}, // BAR 16
    {AB4, TRIPLET/2},
    {G4, TRIPLET/2},
    {F4, EIGTH},
    {EB4, EIGTH},
    {C4, EIGTH},
    {BB3, EIGTH},
    {EB4, EIGTH},
    {C4, QUARTER}, // TIE

    {F3, EIGTH},
    {AB3, EIGTH},
    {BB3, EIGTH},
    {C4, EIGTH},
    {F4, EIGTH},
    {AB4, EIGTH},
    {G4, EIGTH},
    
    {R, EIGTH},
    {AB4, EIGTH},
    {DB4, EIGTH},
    {BB4, EIGTH},
    {R, EIGTH},
    {C3, EIGTH},
    {EB3, EIGTH},
    {F3, QUARTER}, // TIE

    {G3, EIGTH},
    {AB3, EIGTH},
    {BB3, QUARTER},
    {AB3, EIGTH},
    {BB3, EIGTH},
    {F4, EIGTH},

    {EB4, EIGTH},
    {C4, EIGTH},
	{BB3, EIGTH},
    {AB3, QUARTER},
    {G3, EIGTH},
    {C3, EIGTH},
    {EB3, EIGTH},

    {F3, EIGTH}, // BAR 21
    {G3, EIGTH},
    {AB3, EIGTH},
    {BB3, QUARTER},
    {G3, EIGTH},
    {EB3, EIGTH},
    {D3, EIGTH},

    {C4, QUARTER},
    {DB4, QUARTER},
    {EB4, QUARTER},
    {GB4, QUARTER},

    {F4, EIGTH},
    {DB4, EIGTH},
    {AB4, EIGTH},
    {G4, QUARTER},
    {BB4, EIGTH},
    {DB5, EIGTH},
    {C5, EIGTH},

    {BB4, EIGTH},
    {BB3, EIGTH},
    {DB4, EIGTH},
    {C4, QUARTER},
    {EB4, EIGTH},
    {AB4, EIGTH},
    {GB4, EIGTH},

    {F4, EIGTH},
    {F3, EIGTH},
    {C4, EIGTH},
    {BB3, QUARTER},
    {EB3, EIGTH},
    {DB3, EIGTH},
    {BB3, EIGTH},

    {AB3, QUARTERDOT},
    {C4, SIXTEENTH},
    {EB4, SIXTEENTH},
    {AB4, HALF},
	
	{AB3, QUARTER}, // BAR 27
	{AB4, QUARTER},
	{G4, QUARTER},
	{AB4, QUARTER},
	
	{G4, QUARTER},
	{F4, QUARTER},
	{EB4, QUARTER},
	{F4, QUARTER},
	
	{EB4, QUARTER},
	{R, EIGTH},
	{BB3, EIGTH},
	{DB4, QUARTER},
	{C4, EIGTH},
	{BB3, EIGTH},
	
	{C4, QUARTER},
	{R, QUARTER},
	{AB3, QUARTER},
	{BB3, QUARTER},
	
	{C4, QUARTER},
	{DB4, QUARTER},
	{C4, QUARTER},
	{DB4, QUARTER},
	
	{EB4, QUARTER},
	{C4, QUARTER},
	{R, QUARTER},
	{F3, EIGTH},
	{AB3, EIGTH},
	
	{DB4, QUARTER},
	{C4, QUARTER},
	{DB4, QUARTER},
	{EB4, QUARTER},
	
	{C4, QUARTERDOT},
	{BB3, EIGTH},
	{BB3, HALF},
	
	{AB3, QUARTER}, // BAR 35
	{AB4, QUARTER},
	{G4, QUARTER},
	{AB4, QUARTER},
	
	{G4, QUARTER},
	{F4, QUARTER},
	{EB4, QUARTER},
	{F4, QUARTER},
	
	{EB4, QUARTER},
	{F4, QUARTER},
	{G4, QUARTER},
	{C4, QUARTER},
	
	{AB4, QUARTER},
	{R, QUARTER},
	{G4, QUARTER},
	{F4, QUARTER},
	
	{EB4, QUARTER},
	{F4, EIGTH},
	{AB3, EIGTH},
	{R, QUARTER},
	{F3, EIGTH},
	{AB3, EIGTH},
	
	{DB4, QUARTER},
	{C4, EIGTH},
	{BB3, QUARTER},
	{AB3, EIGTH},
	{AB3, QUARTER}
};