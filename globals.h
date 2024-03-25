#ifndef GLOBALS_H
#define GLOBALS_H

// global variables
// extern int bpm;
// extern int score;
// extern bool q_pressed;
// extern bool w_pressed;
// extern bool o_pressed;
// extern bool p_pressed;
// extern NoteTile note_tiles[4];

//      for graphics
extern volatile int pixel_buffer_start;
extern short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
extern short int Buffer2[240][512];

// user-defined classes
struct NoteTile {
    int x;
    int y;
    int dx;
    int dy;
};

typedef struct NoteTile NoteTile;

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

// constants (using preprocessor directives i.e. #define)
//      parallel port addresses
#define AUDIO_BASE      0xFF203040
#define LED_BASE        0xFF200000
#define BUTTON_BASE     0xFF200050
#define HEX_BASE        0xFF200020
#define SWITCH_BASE     0xFF200040
#define GRAPHICS_BASE   0xFF203020
#define PS2_BASE        0xFF200100

//      note frequencies
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

#endif