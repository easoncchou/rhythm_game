#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

// helper functions 

// 	   for NoteTile class
// create a new NoteTile and add it to the linked list
NoteTile* createNoteTile(){
	NoteTile* newTile = (NoteTile*)malloc(sizeof(NoteTile));
	if (newTile == NULL) {
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	newTile->x = rand() % 4 * 70 + 30; // 30, 100, 170, 240
	newTile->y = -TILE_HEIGHT;
	newTile->dy = 1;
	newTile->color = color[rand() % 10]; 
	// insert into a linked list based on assigned lane
	switch (newTile->x) {
	case 30:
		newTile->next = q_head;
		q_head = newTile;
		break;
	case 100:
		newTile->next = w_head;
		w_head = newTile;
		break;
	case 170:
		newTile->next = o_head;
		o_head = newTile;
		break;
	case 240:
		newTile->next = p_head;
		p_head = newTile;
		break;
	default:
		break;
	}
}

//     general purpose
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

//     graphics related
void graphics_initial_setup(){
	// Clear both buffers to black
  	*(pixel_ctrl_ptr + 1) = (int)&Buffer1;
  	draw_background();
  	wait_for_vsync();

  	/* set back pixel buffer to Buffer 2 */
  	*(pixel_ctrl_ptr + 1) = (int)&Buffer2;
	draw_background();
}

// Clears screen to black
void clear_screen() {
  // Device
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;
  // get buffer address
  int *back_buffer = *(pixel_ctrl_ptr + 1);
  // Copy the black buffer into the current buffer
  memcpy(back_buffer, BlackBuffer, sizeof(BlackBuffer));
}

void plot_pixel(int x, int y, short int color) {
  if (y < 0 || y > 239) return; // check y-bounds
  // Device
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;
  // get buffer address
  int back_buffer = *(pixel_ctrl_ptr + 1);
  // get address for pixel at (x, y)
  short int *pixel = back_buffer + (y << 10) + (x << 1);
  *pixel = color;
}

void draw_background() { // perform using memcpy
	// Device
  	volatile int *pixel_ctrl_ptr = (int *)0xff203020;
  	// get buffer address
  	int *back_buffer = *(pixel_ctrl_ptr + 1);
  	// Copy the black buffer into the current buffer
  	memcpy(back_buffer, BackgroundBuffer, sizeof(BackgroundBuffer));
}	

void draw_line(int x, int y, short int color) {
	for (int i = 0; i < TILE_WIDTH; i++) {
		plot_pixel(x + i, y, color);
	}
}

void draw_tile(int x, int y, short int color) {
	for (int i = 0; i < TILE_WIDTH; i++) {
		for (int j = 0; j < TILE_HEIGHT; j++) {
			plot_pixel(x + i, y + j, color);
		}
	}
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
void audio_initial_setup() {
  // prepare audio port for input
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	
	// prepare the hardware timer with 0.25s (first note is a quarter note)
	timerp->control = 0x8; // STOP TIMER
	int length = tracing_that_dream[song_progress][1] / 4; // divide by 4 for cpulator
	timerp->start_low = (length & 0xFFFF); // startlow
	timerp->start_high = (length >> 16); // starthigh
	timerp->control = 0x4; // START = 1 in control reg.
}

bool update_note() {
	// printf("%d\n", song_progress);
	if ((timerp->status & 1) == 0) {
		return false;
	} else {
		timerp->status = 0; // set TO bit to 0
		song_progress += 1;
		int length = tracing_that_dream[song_progress][1] / 4; // divide by 6 for cpulator
		timerp->start_low = (length & 0xFFFF); // startlow
		timerp->start_high = (length >> 16); // starthigh
		timerp->control = 0x4; // START = 1 in control reg.
		createNoteTile();
		return true;
	}
}