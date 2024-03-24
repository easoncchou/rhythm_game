#ifndef GLOBALS_H
#define GLOBALS_H

// global variables
extern int bpm;
extern int score;
extern bool q_pressed;
extern bool w_pressed;
extern bool o_pressed;
extern bool p_pressed;
extern NoteTile note_tiles[4];

//      for graphics
extern volatile int pixel_buffer_start;
extern short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
extern short int Buffer2[240][512];

// user-defined classes
struct Note {
    int pitch;
    int duration;
};

typedef struct Note Note;

struct NoteTile {
    int x;
    int y;
    int dx = 0;
    int dy = 0;
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
#define AUDIO_BASE      0xFF203040
#define LED_BASE        0xFF200000
#define BUTTON_BASE     0xFF200050
#define HEX_BASE        0xFF200020
#define SWITCH_BASE     0xFF200040
#define GRAPHICS_BASE   0xFF203020

#endif