#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"

// fetch song data from global variable and play on the DE1-SoC audio controller
void song_decoder() {
    int frequency = (int) tracing_that_dream[song_progress][0];
		int num_samples = 8192 / frequency; // number of samples in one cycle of the square wave
		// fill the samples array
		int i = 0;
		int sample; // array of samples to place in input FIFO
		while(i < num_samples) {
			if (update_note()) break;
			if (i < (num_samples / 2) ) {
				sample = 0x7FFFFE; // max is2147483647
			} else {
				sample = 0x0;
			}
			if (audiop->wsrc) {
				audiop->ldata = sample;
				audiop->rdata = sample;
				i++;
			}
		}
}