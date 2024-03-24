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

// take 
void level_generator() {

}

// update location of keys (rectangles) based on the song
void graphics_controller() {

}

void check_keypress() {
  //unsigned char byte1 = 0;
	//unsigned char byte2 = 0;

	unsigned char make_code;
  int PS2_data, RVALID;
  bool q_pressed, w_pressed, o_pressed, p_pressed;
  
  // initialze pointer to PS/2 base
  volatile int * PS2_ptr = (int *) PS2_BASE;

  // read the Data register in the PS/2 port
  PS2_data = *(PS2_ptr);	

  // check RVALID for the data
  RVALID = (PS2_data & 0x8000);	

  if (RVALID != 0){
    // byte1 = byte2;
    // byte2 = byte3;

    // extracts the make_code 
    make_code = PS2_data & 0xFF;

    // check if note keys are pressed
    switch (make_code) {
      case (0x15):
        q_pressed = true;
        break;
      
      case (0x1D):
        w_pressed = true;
        break;
      
      case (0x44):
        o_pressed = true;
        break;
      
      case (0x4D):
        p_pressed = true;
        break;

      default:
        break;
    }
  }	
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

	*one_pixel_address = line_color;
}

void clear_screen() { // perform using memcpy

}

void draw_rect(int, int, short int) {

}

void wait_for_vsync() {
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;
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