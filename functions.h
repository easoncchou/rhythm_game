#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// functions to modularize project components (parallel "while 1" operation)
//      fetch song data from global variable and play on the DE1-SoC audio controller
//      time user inputs to the note tile locations
int timing_comparator();
//      update location of NoteTiles (rectangles) based on the song
void graphics_controller();

// helper functions 
//     general purpose
void swap(int*, int*);
//     noteTile functions
NoteTile* createNoteTile();

//     graphics related
void graphics_initial_setup();
void clear_screen();
void plot_pixel(int x, int y, short int line_color); // plot a pixel on the screen IF within bounds
void draw_line(int x, int y, short int color); // draw a line TILE_WIDTH long at x y
void draw_tile(int x, int y, short int color);
void draw_border(int x, int y, short int color);
void highlight_tile();
void draw_background(); // perform using memcpy
void wait_for_vsync();
//     audio related
void audio_initial_setup();
bool update_note();
//		keyboard related
// checking key presses on the PS/2 keyboard
void check_keypress();

#endif

