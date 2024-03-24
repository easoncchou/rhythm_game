#ifndef GLOBALS_H
#define GLOBALS_H

// functions to modularize project components (parallel "while 1" operation)

// fetch song data from global variable and play on the DE1-SoC audio controller
void song_decoder();

// 
int timing_comparator();

// take 
void level_generator();

// update location of keys (rectangles) based on the song
void graphics_controller();

// helper functions 

//     general purpose
void swap(int*, int*);

//     graphics related
void plot_pixel(); // plot a pixel on the screen IF within bounds
void clear_screen(); // perform using memcpy
void draw_rect(int, int, short int);

//     audio related
void play_note(); // play a note based on 

// global variables
extern int bpm;
extern int score;
extern bool q_pressed;
extern bool w_pressed;
extern bool o_pressed;
extern bool p_pressed;
extern NoteTile noteTiles[10];

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