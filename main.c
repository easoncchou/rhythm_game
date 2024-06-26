#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

int main() {
  // seed random
  srand(time(NULL));
  // clear and prime the audio port and hardware timer for audio purposes
  poll_start();
  while (1) {   
    // play the song, breaks out if song_progress needs to be updated timely
    int frequency = (int)tracing_that_dream[audio_progress][0];
    if (frequency == END) poll_start();
    int num_samples =
        8192 / frequency;  // number of samples in one cycle of the square wave
    // fill the samples array
    int samples_array[num_samples];
    int i = 0;
    while (i < num_samples / 2) {
	  update_note_video();
      if (update_note_audio()) break;
      samples_array[i] = 0xFFFFFF;
      i++;
    }
    while (i < num_samples) {
	  update_note_video();
      if (update_note_audio()) break;
      samples_array[i] = 0x0;
      i++;
    }
    int j = 0;
    // fill the hardware buffer until its full
    while (audiop->wsrc) {
      audiop->ldata = samples_array[j % num_samples];
      audiop->rdata = samples_array[j % num_samples];
      j++;
    }
    check_keypress();
    graphics_controller();
    highlight_tile();
    wait_for_vsync();
    score_display();
  }
}


