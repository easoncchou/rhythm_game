#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// global variables
// extern int bpm;
// extern int score;
// extern bool q_pressed;
// extern bool w_pressed;
// extern bool o_pressed;
// extern bool p_pressed;
// extern NoteTile note_tiles[4];

//      for interfacing hardware
// The LED pit is at this base address
extern struct ParaPort *const ledp;
// The BUTTONS pit is at this base address
extern struct ParaPort *const buttonp;
// The Swicthes PIT
extern struct ParaPort *const swp;
//  audio device port
struct audio_t *const audiop;
//  hardware timer port
struct TimerPort *const timerp;
//      for graphics
extern volatile int pixel_buffer_start;
extern short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
extern short int Buffer2[240][512];

//      for audio
extern double tracing_that_dream[][2];
extern int song_progress;

// user-defined classes
struct NoteTile {
    int x;
    int y;
    int dx;
    int dy;
};

typedef struct NoteTile NoteTile;

// global variables
extern int bpm;
extern int score;
extern bool q_pressed;
extern bool w_pressed;
extern bool o_pressed;
extern bool p_pressed;
extern NoteTile note_tiles[4];
extern NoteTile q_lane_note_tiles[4];
extern NoteTile w_lane_note_tiles[4];
extern NoteTile o_lane_note_tiles[4];
extern NoteTile p_lane_note_tiles[4];

//      for graphics
extern volatile int pixel_buffer_start;
extern short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
extern short int Buffer2[240][512];

//      utility classes for hardware interfacing
struct ParaPort {
        volatile unsigned int data;
        volatile unsigned int direction;
        volatile unsigned int mask;
        volatile unsigned int edge;
        };

struct audio_t {
    volatile unsigned int control;  // The control/status register
    volatile unsigned char rarc;	// the 8 bit RARC register
    volatile unsigned char ralc;	// the 8 bit RALC register
    volatile unsigned char wsrc;	// the 8 bit WSRC register
    volatile unsigned char wslc;	// the 8 bit WSLC register
    volatile unsigned int ldata;	// the 32 bit (really 24) left data register
    volatile unsigned int rdata;	// the 32 bit (really 24) right data register
};

struct TimerPort {
	volatile unsigned int status;
	volatile unsigned int control;
	volatile unsigned int start_low;
	volatile unsigned int start_high;
	volatile unsigned int snapshot_low;
	volatile unsigned int snapshot_high;
};

// constants (using preprocessor directives i.e. #define)
//      parallel port addresses
#define AUDIO_BASE      0xFF203040
#define TIMER_BASE      0XFF202000
#define LED_BASE        0xFF200000
#define BUTTON_BASE     0xFF200050
#define HEX_BASE        0xFF200020
#define SWITCH_BASE     0xFF200040
#define GRAPHICS_BASE   0xFF203020
#define PS2_BASE        0xFF200100

// note lengths
#define WHOLE      1000000000
#define HALF       500000000
#define QUARTER    250000000
#define EIGTH      125000000
#define SIXTEENTH  62500000
#define TRIPLET    83333333
#define QUARTERDOT 375000000

//      note frequencies
#define R       0

#define C3      130.81
#define CS3     138.59
#define DB3     138.59
#define D3      146.83 
#define DS3     155.56
#define EB3     155.56
#define E3      164.81
#define F3      174.61
#define FS3     185.00
#define GB3     185.00
#define G3      196.00
#define GS3     207.65
#define AB3     207.65
#define A3      220.00
#define AS3     233.08
#define BB3     233.08
#define B3      246.94

#define C4      261.63
#define CS4     277.18
#define DB4     277.18
#define D4      293.36 
#define DS4     311.13
#define EB4     311.13
#define E4      329.63
#define F4      349.23
#define FS4     369.99
#define GB4     369.99
#define G4      392.00
#define GS4     415.30
#define AB4     415.30
#define A4      440.00
#define AS4     466.16
#define BB4     466.16
#define B4      493.88

#define C5      523.25
#define CS5     554.37
#define DB5     554.37
#define D5      587.33
#define DS5     622.25
#define EB5     622.25
#define E5      659.26
/*
Each Hit Box is 24x50 big

Location for each lane (LEFT X BOUNDARY, RIGHT X BOUNDARY)
Q - (30, 80)
W - (100, 150) 
O - (170, 220)
P - (240, 290)

*/

// timing comparator
#define PERFECT 2
#define GREAT 1
#define MISS 0

// hit box top-left corner at y = 173
#define PERFECT_UPPER 167
#define PERFECT_LOWER 179

#define GREAT_UPPER 149
#define GREAT_LOWER 197

#endif