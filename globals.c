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
NoteTile note_tiles[4];

// graphics
volatile int pixel_buffer_start;
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];