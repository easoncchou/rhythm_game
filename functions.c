#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

// functions to modularize project components (parallel "while 1" operation)

// fetch song data from global variable and play on the DE1-SoC audio controller
void song_decoder() {

}

// 
int timing_comparator() {
    return 0;
}


// update location of keys (rectangles) based on the song
void graphics_controller() {

}

// helper functions 

//     general purpose
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

//     graphics related
void plot_pixel(int x, int y, short int line_color) // plot a pixel on the screen IF within bounds
{
  volatile short int *one_pixel_address;

	one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);

  if (x >= 0 && x < 240 && y >= 0 && y < 319) {
	  *one_pixel_address = line_color;
  }
}

void clear_screen() { // perform using memcpy

}

void draw_rect(int x, int y, short int colour) {

}

void wait_for_vsync() {
  volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
  int status;
  // Start synchronization by writing one to buffer
  *pixel_ctrl_ptr = 1;
  // get status reg
  status = *(pixel_ctrl_ptr + 3);
  // Continue polling until buffer ready to write to
  while ((status & 0x1) != 0) {
    // update
    status = *(pixel_ctrl_ptr + 3);
  }
}

//     audio related
void play_note() {

}