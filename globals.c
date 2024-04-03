#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"

int bpm = 60;
int score = 0;
bool q_pressed;
bool w_pressed;
bool o_pressed;
bool p_pressed;
int keypress_window = 20;
NoteTile q_lane_note_tiles[4];
NoteTile w_lane_note_tiles[4];
NoteTile o_lane_note_tiles[4];
NoteTile p_lane_note_tiles[4];


// graphics
volatile int pixel_buffer_start;
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

// audio
//  song is a 2D array, first column = pitch, second column = duration as a fraction/decimal
//  note pitches are #define'd in globals.h, first letter = note, last letter = octave,
//  middle letter is S for sharp or B for flat if it's there
song_tracing_a_dream[][2] = {
    {F3, 0.25},
    {F4, 0.25}
};