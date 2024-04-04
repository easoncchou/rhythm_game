#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "functions.h"


int main() {
    // prepare audio port for input
	audiop->control = 0x8; // clear the output FIFOs
	audiop->control = 0x0; // resume input conversion
	
	// prepare the hardware timer with 0.25s (first note is a quarter note)
	timerp->control = 0x8; // STOP TIMER
	int length = tracing_that_dream[song_progress][1] / 4; // divide by 4 for cpulator
	timerp->start_low = (length & 0xFFFF); // startlow
	timerp->start_high = (length >> 16); // starthigh
	timerp->control = 0x4; // START = 1 in control reg.

    return 0;
}

