#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

// helper functions 

// 	   for NoteTile class
// create a new NoteTile and add it to the linked list
NoteTile *createNoteTile() {
  NoteTile *newTile = (NoteTile *)malloc(sizeof(NoteTile));
  if (newTile == NULL) {
    printf("Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newTile->x = rand() % 4 * 70 + 30;  // 30, 100, 170, 240
  newTile->y = -1 * TILE_HEIGHT;
  newTile->dy = 1;
  newTile->color = color[rand() % 10];
  newTile->scored = false;
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
  return newTile;
}

//     general purpose
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

//     graphics related
void graphics_initial_setup() {
  // prepare the hardware timer with 0.25s (first note is a quarter note)
  timer2p->control = 0x8;  // STOP TIMER
  int length =
      tracing_that_dream[audio_progress][1] / 4;  // divide by 4 for cpulator
  timer2p->start_low = (length & 0xFFFF);         // startlow
  timer2p->start_high = (length >> 16);           // starthigh
  timer2p->control = 0x4;                         // START = 1 in control reg.
	
  // Clear both buffers to black
  *(pixel_ctrl_ptr + 1) = (int)&Buffer1;
  draw_background();
  wait_for_vsync();

  /* set back pixel buffer to Buffer 2 */
  *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
  draw_background();
}

bool update_note_video() {
  // printf("video is at %d\n", song_progress);
  if ((timer2p->status & 1) == 0) {
    return false;
  } else {
    timer2p->status = 0;  // set TO bit to 0
    video_progress += 1;
    int length =
        tracing_that_dream[video_progress][1] / 4;  // divide by 6 for cpulator
    timer2p->start_low = (length & 0xFFFF);         // startlow
    timer2p->start_high = (length >> 16);           // starthigh
    timer2p->control = 0x4;                         // START = 1 in control reg.
    if (tracing_that_dream[video_progress][0] != R) createNoteTile();
    return true;
  }
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
  if (y < 0 || y > 239) return;  // check y-bounds
  // Device
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;
  // get buffer address
  int back_buffer = *(pixel_ctrl_ptr + 1);
  // get address for pixel at (x, y)
  short int *pixel = back_buffer + (y << 10) + (x << 1);
  *pixel = color;
}

void draw_background() {  // perform using memcpy
                          // Device
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;
  // get buffer address
  int *back_buffer = *(pixel_ctrl_ptr + 1);
  // Copy the black buffer into the current buffer
  memcpy(back_buffer, BackgroundBuffer, sizeof(BackgroundBuffer));
}

void draw_startscreen() {  // perform using memcpy
                          // Device
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;
  // get buffer address
  int *back_buffer = *(pixel_ctrl_ptr + 1);
  // Copy the black buffer into the current buffer
  memcpy(back_buffer, StartScreenBuffer, sizeof(StartScreenBuffer));
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

void highlight_tile() {
  if (q_pressed) draw_border(30, 173, 0x07e0);
  if (w_pressed) draw_border(100, 173, 0x07e0);
  if (o_pressed) draw_border(170, 173, 0x07e0);
  if (p_pressed) draw_border(240, 173, 0x07e0);
}

void draw_border(int x, int y, short int color) {
  for (int i = 0; i < TILE_WIDTH; i++) plot_pixel(x + i, y, color);  // top edge
  for (int i = 0; i < TILE_WIDTH; i++)
    plot_pixel(x + i, y + TILE_HEIGHT, color);  // bottom edge
  for (int i = 0; i < TILE_HEIGHT; i++)
    plot_pixel(x, y + i, color);  // left edge
  for (int i = 0; i < TILE_HEIGHT; i++)
    plot_pixel(x + TILE_WIDTH, y + i, color);  // right edge
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
  audiop->control = 0x8;  // clear the output FIFOs
  audiop->control = 0x0;  // resume input conversion

  // prepare the hardware timer with 0.25s (first note is a quarter note)
  timerp->control = 0x8;  // STOP TIMER
  int length =
      tracing_that_dream[audio_progress][1] / 4;  // divide by 4 for cpulator
  timerp->start_low = (length & 0xFFFF);         // startlow
  timerp->start_high = (length >> 16);           // starthigh
  timerp->control = 0x4;                         // START = 1 in control reg.
}

bool update_note_audio() {
  // printf("audio is at %d\n", audio_progress);
  if ((timerp->status & 1) == 0) {
    return false;
  } else if (audio_delayed == false) {
	audio_delayed = true;
	timerp->status = 0;  // set TO bit to 0
    int length =
        AUDIO_DELAY;  // divide by 6 for cpulator
    timerp->start_low = (length & 0xFFFF);         // startlow
    timerp->start_high = (length >> 16);           // starthigh
    timerp->control = 0x4;                         // START = 1 in control reg.
    return true;
  } else {
    timerp->status = 0;  // set TO bit to 0
    audio_progress += 1;
    int length =
        tracing_that_dream[audio_progress][1] / 4;  // divide by 6 for cpulator
    timerp->start_low = (length & 0xFFFF);         // startlow
    timerp->start_high = (length >> 16);           // starthigh
    timerp->control = 0x4;                         // START = 1 in control reg.
    return true;
  }
}