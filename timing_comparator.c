#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "globals.h"
#include "globals.c"
#include "functions.h"

// check the timing of the user input with the song's rhythm and update the score
// overall logic:

// check key press
// check timing
// reset key press
// move tiles
// redraw
int timing_comparator() {
    // depending on different key pressed, loop through all corresponding note tile array
    if (q_pressed){
        // loop through array
        for (int idx = 0; idx < 4; idx++){

            // return PERFECT score if it is hit within perfect range
            if (q_lane_note_tiles[idx].y > PERFECT_UPPER && q_lane_note_tiles[idx].y < PERFECT_LOWER){
                return PERFECT;
            }

            // return GREAT score if it is hit within great range
            if (q_lane_note_tiles[idx].y > GREAT_UPPER && q_lane_note_tiles[idx].y < GREAT_LOWER){
                return GREAT;
            }
        }

    } else if (w_pressed){
        for (int idx = 0; idx < 4; idx++){
            if (w_lane_note_tiles[idx].y > PERFECT_UPPER && w_lane_note_tiles[idx].y < PERFECT_LOWER){
                return PERFECT;
            }

            if (w_lane_note_tiles[idx].y > GREAT_UPPER && w_lane_note_tiles[idx].y < GREAT_LOWER){
                return GREAT;
            }
        }
        
    } else if (o_pressed){
        for (int idx = 0; idx < 4; idx++){
            if (o_lane_note_tiles[idx].y > PERFECT_UPPER && o_lane_note_tiles[idx].y < PERFECT_LOWER){
                return PERFECT;
            }

            if (o_lane_note_tiles[idx].y > GREAT_UPPER && o_lane_note_tiles[idx].y < GREAT_LOWER){
                return GREAT;
            }
        }

    } else if (p_pressed){
        for (int idx = 0; idx < 4; idx++){
            if (p_lane_note_tiles[idx].y > PERFECT_UPPER && p_lane_note_tiles[idx].y < PERFECT_LOWER){
                return PERFECT;
            }

            if (p_lane_note_tiles[idx].y > GREAT_UPPER && p_lane_note_tiles[idx].y < GREAT_LOWER){
                return GREAT;
            }
        }
    }

    // if no tiles is around the hit box, then return nothing
    return MISS;
}
