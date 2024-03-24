#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// functions to modularize project components (parallel "while 1" operation)
//      fetch song data from global variable and play on the DE1-SoC audio controller
void song_decoder();
// 
int timing_comparator();
//      fetch song data from global variable and update NoteTiles location data
void level_generator();
//      update location of NoteTiles (rectangles) based on the song
void graphics_controller();

// helper functions 
//     general purpose
void swap(int*, int*);
//     graphics related
void plot_pixel(); // plot a pixel on the screen IF within bounds
void clear_screen(); // perform using memcpy
void draw_rect(int, int, short int);
void wait_for_vsync();
//     audio related
void play_note(); 

// checking key presses on the PS/2 keyboard
void check_keypress();

#endif

